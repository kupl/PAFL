namespace PAFL
{
class Localizer::Lang
{
public:
    class Logger;
    typedef struct { float weight; float future; } Weight;
    using block = std::unordered_map<std::string, Weight>;

    class iterator
    {
    public:
        iterator(block& target, block& parent, block& child, block& pred, block& succ) :
            _transition{ {&target, &parent}, {&parent, &child}, {&child, &pred}, {&pred, &succ} },
            _iter(target.begin()), _ptr(&target), _end(&succ) { _skip(); }

        iterator& operator++()
            { ++_iter; _skip(); return *this; }
        block::value_type& operator*()
            { return *_iter; }
        block::iterator& operator->()
            { return _iter; }
        bool operator==(block::iterator iter)
            { return _iter == iter; }
        bool operator!=(block::iterator iter)
            { return _iter != iter; }

    private:
        void _skip()
            { while (_ptr != _end && _iter == _ptr->end()) _iter = (_ptr = _transition[_ptr])->begin(); }

        block::iterator _iter;
        block* _ptr;
        block* _end;
        std::unordered_map<block*, block*> _transition;
    };


    void insertToken(const Token& token, float base);
    void eraseIf(float threshold);
    void assignFuture();

    float similarity(const Token& token) const;

    decltype(auto) begin()
        { return iterator(_target, _parent, _child, _pred, _succ); }
    decltype(auto) end()
        { return _succ.end(); }

    void setLogger(std::shared_ptr<Logger> logger)
        { _logger = logger; }

    
private:
    void _insert(decltype(Token::neighbors) set_ptr, block& blck, float base);
    float _maxWeight(decltype(Token::neighbors) set_ptr, const block& blck) const;

    block _target;
    block _parent;
    block _child;
    block _pred;
    block _succ;

    std::shared_ptr<Logger> _logger;
};
}






namespace PAFL
{
void Localizer::Lang::insertToken(const Token& token, float base)
{
    _insert(token.neighbors, _target, base);

    if (token.parent != token.root)
        _insert(token.parent->neighbors, _parent, base);
    if (token.children)
        _insert(token.children, _child, base);

    _insert(token.predecessor, _pred, base);
    _insert(token.successor, _succ, base);
}

void Localizer::Lang::eraseIf(float threshold)
{
    std::erase_if(_target, [=](const auto& item){ return item.second.weight <= threshold; });
    std::erase_if(_parent, [=](const auto& item){ return item.second.weight <= threshold; });
    std::erase_if(_child, [=](const auto& item){ return item.second.weight <= threshold; });
    std::erase_if(_pred, [=](const auto& item){ return item.second.weight <= threshold; });
    std::erase_if(_succ, [=](const auto& item){ return item.second.weight <= threshold; });
}



void Localizer::Lang::assignFuture()
{
    for (auto& item : _target) item.second.weight = item.second.future;
    for (auto& item : _parent) item.second.weight = item.second.future;
    for (auto& item : _child) item.second.weight = item.second.future;
    for (auto& item : _pred) item.second.weight = item.second.future;
    for (auto& item : _succ) item.second.weight = item.second.future;
}



float Localizer::Lang::similarity(const Token& token) const
{
    float target_weight = _maxWeight(token.neighbors, _target);

    float parent_weight = 0.0f;
    if (token.parent != token.root)
        parent_weight = _maxWeight(token.parent->neighbors, _parent);
    float child_weight = 0.0f;
    if (token.children)
        child_weight = _maxWeight(token.children, _child);

    float pred_weight = _maxWeight(token.predecessor, _pred);
    float succ_weight = _maxWeight(token.successor, _succ);

    return target_weight + (parent_weight + child_weight + pred_weight + succ_weight) / 4;
}



float Localizer::Lang::_maxWeight(decltype(Token::neighbors) set_ptr, const block& blck) const
{
    float ret = 0.0f;
    for (auto& tok : *set_ptr)
        if (blck.contains(tok)) {

            auto temp = blck.at(tok).weight;
            if (temp > ret)
                ret = temp;
        }

    return ret;
}

void Localizer::Lang::_insert(decltype(Token::neighbors) set_ptr, block& blck, float base)
{
    for (auto& tok : *set_ptr)
        if (!blck.contains(tok))
            blck.emplace(tok, Weight{base, base});
}
}






namespace PAFL
{
class Localizer::Lang::Logger
{
public:
    Logger(const fs::path& path) : _path(path) {}
    void log(const Localizer::Lang* obj) const
    {
        std::ofstream ofs(_path);

        ofs << "\n<Target>\n\n";
        _logBlock(ofs, obj->_target);
        ofs << "\n<Parent>\n\n";
        _logBlock(ofs, obj->_target);
        ofs << "\n<Child>\n\n";
        _logBlock(ofs, obj->_target);
        ofs << "\n<Target>\n\n";
        _logBlock(ofs, obj->_target);
        ofs << "\n<Target>\n\n";
        _logBlock(ofs, obj->_target);
    }

private:
    void _logBlock(std::ofstream& ofs, const block& blck) const
    {
        for (auto& item : blck)
            ofs << " -:\"" << item.first << "\"  ->  " << item.second.weight << '\n';
    }
    const fs::path _path;
};
}
