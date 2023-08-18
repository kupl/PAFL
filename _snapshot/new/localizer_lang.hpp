namespace PAFL
{
class Localizer::Lang
{
public:
    class Logger;
    using Node = std::unordered_set<std::string>;


    Lang() : _size(0), _predecessor{Node()}, _target{Node()}, _successor{Node()} {}
    Lang(const Token& tok, TestSuite& suite);

    float getSimilarity(const Token& tok) const;
    size_t size() const
        { return _size; }

    Lang operator|(const Lang& rhs) const;
    const Lang& operator|=(const Lang& rhs) const;
    bool operator==(const Lang& rhs) const;

    const std::list<Node>& getPredecessor() const
        { return _predecessor; }
    const std::list<Node>& getTarget() const
        { return _target; }
    const std::list<Node>& getSuccessor() const
        { return _successor; }
    bool empty() const
        { return _size == 0; }

    void setLogger(std::shared_ptr<BaseLogger> logger);
    

private:
    std::list<Node> _predecessor;
    std::list<Node> _target;
    std::list<Node> _successor;

    size_t _size;

    std::shared_ptr<Logger> _logger;
};
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
}






namespace PAFL
{
Localizer::Lang::Lang(const Token& tok, TestSuite& suite)
{
    for (auto& file : suite)
        for (auto& line_param : file) {

            
        }
}



float Localizer::Lang::getSimilarity(const Token& tok) const
{
    if (!_size)
        return 1.0f;
    size_t counter = 0;

    if (_predecessor.size() == 0 && tok.parent == tok.root)
        counter++;
    else
        for (auto& node : _predecessor) {
            
            bool breakable = true;
            for (auto& item : *tok.parent->neighbors)
                if (node.contains(item)) {

                    breakable = false;
                    break;
                }

            if (breakable)
                break;
            counter++;
        }

    return counter / _size;
}
}
