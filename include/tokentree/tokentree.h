#ifndef __TOKENTREE_H__
#define __TOKENTREE_H__

#include <fstream>
#include <memory>
#include <vector>

#include "type.h"
#include "rapidjson.h"
#include "stringeditor.h"


namespace PAFL
{
class Token
{
public:
    using List = std::list<Token*>;
    using Node = std::shared_ptr<List>;

public:
    Token(const std::string& name, line_t loc) : name(name), loc(loc) {}
    void clear() { neighbor.reset(); parent.reset(); child.reset(); pred.reset(); succ.reset(); }
    
public:
    // Token Info
    const std::string name;
    const line_t loc;

    // Token Relation
    std::shared_ptr<Token::List> neighbor;
    std::shared_ptr<Token::List> parent;
    std::shared_ptr<Token::List> child;
    std::shared_ptr<Token::List> pred;
    std::shared_ptr<Token::List> succ;
};



/*
    * TOKEN_ID(0)   = NULL
    * NODE_ID(0)    = NULL
    
    JSON format ->
    {
        "total_tokens": uint64_t,
        "tokens": [
            {
                "lineno": uint32_t,
                "tokens": [
                    [ ID(uint_64t), NAME(str), NEIGH_ID(uint_64t),
                      PARENT_ID(uint_64t), CHILD_ID(uint_64t), PRED_ID(uint_64t), SUCC_ID(uint_64t) ],

                    ...
                ]
            },

            ...
        ],
        "total_nodes": uint64_t,
        "nodes": [
            {
                "id": uint64_t,
                "elems": [ TOKEN_ID(uint64_t), ... ]
            },

            ...
        ]
    }
*/
class TokenTree
{
public:
    using Vector = std::vector<TokenTree*>;

public:
    TokenTree(const fs::path& src_file, const fs::path& bin, const std::string& exe);
    TokenTree() = default;
    TokenTree(TokenTree& rhs) = delete;
    TokenTree& operator=(TokenTree& rhs) = delete;
    TokenTree(TokenTree&& rhs) : _stream(std::move(rhs._stream)), _indexer(std::move(rhs._indexer)), _good(rhs._good) {}

    bool good() const                                       { return _good; }
    const std::list<Token>* getTokens(line_t line) const    { return _indexer.contains(line) ? _indexer.at(line) : nullptr; }
    void save(const fs::path& path) const;
    void load(const fs::path& path);
    std::string log() const;

protected:
    void setIndexer();

protected:
    std::list<std::list<Token>> _stream;
    std::unordered_map<line_t, decltype(_stream)::value_type*> _indexer;
    bool _good = false;


private:
    // range = 1 to inf
    class IdGenerator
    {
    public:
        using id_t = uint64_t;

    public:
        IdGenerator() : id(0) {}
        id_t operator[](const void* ptr);
        decltype(auto) size() const { return id_list.size(); }
        
    private:
        id_t id;
        std::unordered_map<const void*, id_t> id_list;
    };
    using id_t = IdGenerator::id_t;

    enum { ID, NAME, NEIGH, PARENT, CHILD, PRED, SUCC };
};
}
#endif
