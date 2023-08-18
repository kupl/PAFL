namespace PAFL
{
class Localizer::Lang
{
public:
    class Logger;

    Lang() :
        _list(1, true), _target(_list.begin()), _marker_size(1) {}
    Lang(const Lang& rhs);

    const Lang& operator=(const Lang& rhs);
    bool operator==(const Lang& rhs) const;
    bool operator!=(const Lang& rhs) const
        { return !(*this == rhs); }

    void CalculateSus(TokenTree& tkt, TestSuite& cov, index_t index, Option opt);
    bool Step(TokenTree::Vector& tkt_vec, TestSuite& cov, index_t index, const std::list<line_t>& buggy_lines);

    bool Empty() const
        { return _marker_size == 0; }
    bool IsBase() const
        { return _list.size() == 1 && _marker_size == 1; }
    size_t Size() const
        { return _list.size(); }

    void Log(std::ostream& os);


private:
    std::list<bool>::iterator begin()
        { return _list.begin(); }
    std::list<bool>::iterator end()
        { return _list.end(); }
    std::list<bool>::iterator rbegin()
        { auto ret = _list.end(); return --ret; }
    std::list<bool>::iterator rend()
        { auto ret = _list.begin(); return --ret; }

    std::list<bool>::const_iterator cbegin() const
        { return _list.cbegin(); }
    std::list<bool>::const_iterator cend() const
        { return _list.cend(); }
    std::list<bool>::const_iterator crbegin() const
        { auto ret = _list.cend(); return --ret; }
    std::list<bool>::const_iterator crend() const
        { auto ret = _list.cbegin(); return --ret; }
    
    void _Optimize();

    std::list<bool> _list;
    std::list<bool>::iterator _target;
    size_t _marker_size;

    std::unique_ptr<BaseLogger> _logger;
};
}






namespace PAFL
{
class Localizer::Lang::Logger : public BaseLogger
{
    void log(const void* obj) override
    {
        std::ofstream os(_path + '_' + std::to_string(++_counter) + ".txt");
    }
public:
    Logger(const std::string& log_path, const std::string& name)
        { BaseLogger::init(log_path, name); }
};
}






namespace PAFL
{
Localizer::Lang::Lang(const Lang& rhs) :
    _marker_size(rhs._marker_size)
{
    _list.push_back(*rhs._target);
    _target = begin();

    // Copy predecessor
    auto iter = rhs._target;
    for (iter--; iter != rhs.crend(); iter--)
        _list.push_front(*iter);

    // Copy successor
    iter = rhs._target;
    for (iter++; iter != rhs.cend(); iter++)
        _list.push_back(*iter);
}



const Localizer::Lang& Localizer::Lang::operator=(const Lang& rhs)
{
    _marker_size = rhs._marker_size;
    _list.clear();
    _list.push_back(*rhs._target);
    _target = begin();

    // Copy predecessor
    auto iter = rhs._target;
    for (iter--; iter != rhs.crend(); iter--)
        _list.push_front(*iter);

    // Copy successor
    iter = rhs._target;
    for (iter++; iter != rhs.cend(); iter++)
        _list.push_back(*iter);

    return *this;
}

bool Localizer::Lang::operator==(const Lang& rhs) const
{
    auto lhs_iter = cbegin();
    auto rhs_iter = rhs.cbegin();

    for (;; lhs_iter++, rhs_iter++)
    {
        // If lhs or rhs end
        if (lhs_iter == cend())
            return rhs_iter == rhs.cend();
        else if (rhs_iter == rhs.cend())
            return false;

        // If lhs.cur != rhs.cur
        if ((lhs_iter == _target) != (rhs_iter == rhs._target))
            return false;
        
        if (*lhs_iter != *rhs_iter)
            return false;
    }
}



void Localizer::Lang::Log(std::ostream& os)
{
    size_t i = 0;
    for (auto iter = begin(); iter != _target; iter++, i++);
    os << "{ " << "len: " << _list.size() << ", target: " << i << ", marker: [ ";

    i = 0;
    size_t counter = 0;
    for (auto iter = begin(); iter != end(); iter++, i++)
        if (*iter)
            os << i << (++counter != _marker_size ? ", " : " ], ");

    os << "num_marker: " << _marker_size << " }\n";
}






void Localizer::Lang::CalculateSus(TokenTree& tkt, TestSuite& cov, index_t index, Option opt)
{
    std::unordered_map<Token*, float> pred_map;
    std::unordered_map<Token*, float> succ_map;
    pred_map.reserve(73);
    succ_map.reserve(73);
    pred_map.emplace(tkt.GetRoot(), 0.0f);
    succ_map.emplace(nullptr, 0.0f);

    for (auto iter = cov.cbegin(index); iter != cov.cend(index); iter++) {

        float max_sus = 0.0f;
        auto ptr_tok_list = tkt.GetTokens(iter->first);
        if (!ptr_tok_list) {

            // Assign suspiciousness of line
            if (opt != Option::constant_coverage)
                iter->second.ptr_ranking->sus = iter->second.ptr_ranking->ochiai_sus;
            continue;
        }


        for (auto& tok : *ptr_tok_list) {

            // Search predecessor
            float pred_sus = 0.0f;
            Token* parent = tok.parent;
            if (pred_map.contains(parent))
                pred_sus = pred_map[parent];

            else {

                auto list_iter = _target;
                for (list_iter--; list_iter != rend(); list_iter--) {
                    
                    if (parent == tkt.GetRoot())
                        break;

                    if (*list_iter)
                        pred_sus += parent->ochiai_sus;
                    parent = parent->parent;
                }
                pred_map.emplace(tok.parent, pred_sus);
            }

            // Search successor
            float succ_sus = 0.0f;
            if (succ_map.contains(tok.branch))
                succ_sus = succ_map[tok.branch];

            else {

                // successor queue
                using token_with_score = std::pair<Token*, float>;
                std::list<token_with_score> queue;
                for (auto child : tok.branch->children)
                queue.emplace_back(child, 0.0f);
                queue.emplace_back(nullptr, 0.0f);

                auto list_iter = _target;
                for (list_iter++; list_iter != end(); list_iter++) {
                    
                    if (*list_iter)
                        for (auto& tok_score : queue)
                            if (tok_score.first && succ_sus < (tok_score.second += tok_score.first->ochiai_sus))
                                succ_sus = tok_score.second;

                    // Queueing next sucessor
                    while(true) {

                        token_with_score front = *queue.begin();
                        // If queue.begin() == nullptr, break
                        if (!front.first)
                            break;
                        
                        if (front.first->branch)
                            for (auto child : front.first->branch->children)
                                queue.emplace_back(child, front.second);

                        queue.pop_front();
                    }
                    
                    // Pop nullptr
                    queue.pop_front();
                    if (queue.empty())
                        break;
                    queue.emplace_back(nullptr, 0.0f);
                }

                succ_map.emplace(tok.branch, succ_sus);
            }

            if (_marker_size)
                tok.sus = *_target ? (tok.ochiai_sus + pred_sus + succ_sus) / _marker_size : (pred_sus + succ_sus) / _marker_size;
            else
                tok.sus = 0.0f;
            if (max_sus < tok.sus)
                max_sus = tok.sus;
        }

        // Assign suspiciousness of line
        if (opt == Option::maximize_coverage && max_sus > iter->second.ptr_ranking->sus)
            iter->second.ptr_ranking->sus = max_sus;
        else if (opt == Option::assign_to_coverage)
            iter->second.ptr_ranking->sus = max_sus;
    }
}



bool Localizer::Lang::Step(TokenTree::Vector& tkt_vec, TestSuite& cov, index_t index, const std::list<line_t>& buggy_lines)
{
    bool is_base_exists = false;
    // Log
    static size_t debug = 0;
    std::list<Lang> candidates;
    
    // Add marked predecessor
    {
        candidates.push_front(*this);
        auto ptr_candidate = candidates.begin();
        ptr_candidate->_list.push_front(true);
        ptr_candidate->_marker_size++;
    }

    // Add marked successor
    {
        candidates.push_front(*this);
        auto ptr_candidate = candidates.begin();
        ptr_candidate->_list.push_back(true);
        ptr_candidate->_marker_size++;
    }

    // Extend predecessor
    {
        candidates.push_front(*this);
        auto ptr_candidate = candidates.begin();
        *ptr_candidate->begin() = false;
        ptr_candidate->_list.push_front(true);
    }

    // Extend successor
    {
        candidates.push_front(*this);
        auto ptr_candidate = candidates.begin();
        *ptr_candidate->rbegin() = false;
        ptr_candidate->_list.push_back(true);
    }

    // Add marker
    {
        auto iter = _list.begin();
        for (size_t i = 0; i != _list.size(); i++, iter++)
            if (!*iter) {

                candidates.push_front(*this);
                auto ptr_candidate = candidates.begin();
                auto target = ptr_candidate->begin();
                for (size_t sub_i = 0; sub_i != i; sub_i++)
                    target++;
                *target = true;
                ptr_candidate->_marker_size++;
            }
    }

    // Delete marker
    if (_marker_size > 1) {

        auto iter = _list.begin();
        for (size_t i = 0; i != _list.size(); i++, iter++)
            if (*iter) {

                candidates.push_front(*this);
                auto ptr_candidate = candidates.begin();
                auto target = ptr_candidate->begin();
                for (size_t sub_i = 0; sub_i != i; sub_i++)
                    target++;
                *target = false;
                ptr_candidate->_marker_size--;
                ptr_candidate->_Optimize();

                if (ptr_candidate->Empty() || ptr_candidate->IsBase())
                    candidates.pop_front();
            }
    }

    // Add this
    if (!this->IsBase() && !this->Empty())
        candidates.push_front(*this);

    
    Lang* top_lang = nullptr;
    float max_sus = 0.0f;
    line_t min_ranking_sum = std::numeric_limits<line_t>::max();

    for (auto& lang : candidates) {

        float sus = 0.0f;
        // New ranking
        for (line_t idx = 0; idx != cov.MaxIndex(); idx++)
            lang.CalculateSus(tkt_vec[idx], cov, index, Option::assign_to_coverage);
        cov.Rank();
        line_t ranking_sum = cov.GetRankingSum(index, buggy_lines);
        for (auto line : buggy_lines)
            if (cov.GetSus(index, line) > sus)
                sus = cov.GetSus(index, line);
        
        if (sus > max_sus) {

            top_lang = &lang;
            max_sus = sus;
            min_ranking_sum = ranking_sum;
        }
    }


    if (!top_lang)
        top_lang = this;
    std::ofstream ofs("_log/log_lang_" + std::to_string(++debug));
    top_lang->Log(ofs);
    ofs.close();

    // If Lang is not changed, return false
    if (*top_lang == *this)
        return false;
    // If Lang is changed, return true
    *this = *top_lang;
    return true;
}



void Localizer::Lang::_Optimize()
{
    // Pop predecessor
    for (auto iter = begin(); iter != _target;) {

        if (*iter)
            break;
        iter++;
        _list.pop_front();
    }

    // Pop successor
    for (auto iter = rbegin(); iter != _target;) {

        if (*iter)
            break;
        iter--;
        _list.pop_back();
    }
}
}
