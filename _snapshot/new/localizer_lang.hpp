namespace PAFL
{
class Localizer::Lang
{
public:
    class Logger;
    using Node = std::unordered_set<std::string>;
    using iterator = std::list<Node>::iterator;
    using const_iterator = std::list<Node>::const_iterator;
    struct HashFunction
    {
        size_t operator()(const Lang& lang) const
        {
            size_t elem1 = std::hash<size_t>()(lang._parent.size() * lang._token_size[0]);
            size_t elem2 = std::hash<size_t>()(lang._target.size() * lang._token_size[1]);
            size_t elem3 = std::hash<size_t>()(lang._child.size() * lang._token_size[2]);
            return elem1 ^ elem2 ^ elem3;
        }
    };


    Lang() : _size(0), _token_size{0, 0, 0}, _parent{Node()}, _target{Node()}, _child{Node()} {}
    Lang(const Token& tok, TestSuite& suite, index_t index, const TokenTree::Vector& ttvec, const std::list<line_t>& buggy_lines);


    float similarity(const Token& tok) const;
    void computeSus(TestSuite& suite, const TokenTree::Vector& ttvec);

    Lang operator|(const Lang& rhs) const;
    const Lang& operator|=(const Lang& rhs);
    bool operator==(const Lang& rhs) const;

    const std::list<Node>& getPredecessor() const
        { return _parent; }
    const std::list<Node>& getTarget() const
        { return _target; }
    const std::list<Node>& getSuccessor() const
        { return _child; }
    bool isTop() const
        { return _parent.size() == 1 && _target.size() == 1 && _child.size() == 1; }

    void setLogger(std::shared_ptr<BaseLogger> logger);
    

private:
    std::list<Node> _target;
    std::list<Node> _parent;
    std::list<Node> _child;
    std::list<Node> _predecessor;
    std::list<Node> _successor;

    size_t _size;
    size_t _token_size[3];

    std::shared_ptr<Logger> _logger;
};

bool _isIntersectionNode(const Localizer::Lang::Node& lhs, const Localizer::Lang::Node& rhs);
}






namespace PAFL
{
class Localizer::Lang::Logger : public BaseLogger
{
    void logNodeList(std::ofstream& os, const std::list<Node>& obj)
    {
        if (!obj.size()) {

            os << " Empty\n";
            return;
        }

        for (auto& node : obj) {

            os << " -> { ";
            auto future = node.cbegin();
            future++;
            for (auto iter = node.cbegin(); iter != node.cend(); iter++, future++)
                iter != node.cend() ? (os << '"' << *iter << "\" | ") : (os << '"' << *iter << "\" ");
            os << "}\n";
        }
    }
    void log(const void* obj) override
    {
        auto ptr_lang = static_cast<const Lang*>(obj);
        std::ofstream os(_path + '_' + std::to_string(++_counter) + ".txt");

        os << "## Predecessor\n";
        logNodeList(os, ptr_lang->getPredecessor());
        os << "## Target\n";
        logNodeList(os, ptr_lang->getTarget());
        os << "## Successor\n";
        logNodeList(os, ptr_lang->getSuccessor());
    }
public:
    Logger(const std::string& log_path, const std::string& name)
        { BaseLogger::init(log_path, name); }
};



bool _isIntersectionNode(const Localizer::Lang::Node& lhs, const Localizer::Lang::Node& rhs)
{
    const auto& little = lhs.size() < rhs.size() ? lhs : rhs;
    const auto& large = lhs.size() < rhs.size() ? rhs : lhs;

    for (auto& item : little)
        if (large.contains(item))
            return true;
    return false;
}
}






namespace PAFL
{
Localizer::Lang::Lang(const Token& tok, TestSuite& suite, index_t index, const TokenTree::Vector& ttvec, const std::list<line_t>& buggy_lines)
{
    auto sbfl_rankingsum = suite.GetRankingSum(index, buggy_lines);
    std::queue<Lang> queue;
    queue.emplace();
}



float Localizer::Lang::similarity(const Token& tok) const
{
    if (!_size)
        return 1.0f;
    size_t counter = 0;

    if (_parent.size() == 0 && tok.parent == tok.root)
        counter++;
    else
        for (auto& node : _parent) {
            
            if (node.empty())
                break;
            if (_isIntersectionNode(node, *tok.parent->neighbors))
                counter++;
            else
                break;
        }

    for (auto& node : _target) {

        if (node.empty())
            break;
        if (_isIntersectionNode(node, *tok.neighbors))
            counter++;
        else
            break;
    }

    if (_child.size() == 0 && tok.children == nullptr)
        counter++;
    else
        for (auto& node : _parent) {
            
            if (node.empty())
                break;
            if (_isIntersectionNode(node, *tok.children))
                counter++;
            else
                break;
        }

    return counter / _size;
}



void Localizer::Lang::computeSus(TestSuite& suite, const TokenTree::Vector& ttvec)
{
    index_t idx = 0;
    for (auto& file : suite) {

        std::unordered_map<decltype(&*Token::neighbors), float> table;
        table.reserve(256);
        for (auto& line_param : file) {

            auto tklist = ttvec[idx].getTokens(line_param.first);
            auto& ref_sus = line_param.second.ptr_ranking->sus;

            if (tklist)
                for (auto& tok : *tklist) {

                    float computed = 0.0f;
                    if (table.contains(&*tok.neighbors))
                        computed = table.at(&*tok.neighbors);
                    else {

                        computed = similarity(tok);
                        table.emplace(&*tok.neighbors, computed);
                    }

                    ref_sus = ref_sus > computed ? ref_sus : computed;
                }
        }
        idx++;
    }
}



bool Localizer::Lang::operator==(const Lang& rhs) const
{
    if (_size != rhs._size)
        return false;

    {
        if (_token_size[0] != rhs._token_size[0] || _parent.size() != rhs._parent.size())
            return false;
        auto rhs_iter = rhs._parent.cbegin();
        for (auto lhs_iter = _parent.cbegin(); lhs_iter != _parent.cend(); lhs_iter++, rhs_iter++)
            if (!(*lhs_iter == *rhs_iter))
                return false;
    }
    {
        if (_token_size[1] != rhs._token_size[1] || _target.size() != rhs._target.size())
            return false;
        auto rhs_iter = rhs._target.cbegin();
        for (auto lhs_iter = _target.cbegin(); lhs_iter != _target.cend(); lhs_iter++, rhs_iter++)
            if (!(*lhs_iter == *rhs_iter))
                return false;
    }
    {
        if (_token_size[2] != rhs._token_size[2] || _child.size() != rhs._child.size())
            return false;
        auto rhs_iter = rhs._child.cbegin();
        for (auto lhs_iter = _child.cbegin(); lhs_iter != _child.cend(); lhs_iter++, rhs_iter++)
            if (!(*lhs_iter == *rhs_iter))
                return false;
    }

    return true;
}
}
