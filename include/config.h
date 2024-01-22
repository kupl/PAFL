#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "type.h"


namespace PAFL
{
class Config
{
public:
    class Token
    {
    public:
        enum class Type { STRING, PROJ, VER, CASE };
        Token(Type ttype, const std::string& str);

        const std::string& operator()(const std::string& proj, const std::string& ver, const std::string& tc) const { return (this->*_func)(proj, ver, tc); }

    private:
        const std::string& _STR(const std::string&, const std::string&, const std::string&) const                   { return _str; }
        const std::string& _PROJ(const std::string& proj, const std::string&, const std::string&) const             { return proj; }
        const std::string& _VER(const std::string&, const std::string& ver, const std::string&) const               { return ver; }
        const std::string& _CASE(const std::string&, const std::string&, const std::string& tc) const               { return tc; }

        std::string _str;
        decltype(&Config::Token::operator()) _func;
    };

    class Line : public std::list<Token>
    {
        public: std::string operator()(const std::string& proj, const std::string& ver, const std::string& tc) const
        {
            std::string ret;
            for (auto& tok : *this)
                ret.append(tok(proj, ver, tc));
            return ret;
        }
    };



public:
    void configure(PrgLang pl, const fs::path& path);

public:
    Line PROJECT_LOC; Line TESTCASE_LOC; Line COVERAGE_NAME;
    Line TEST_NAME; Line TEST_PASS;

private:
    void _throwInvalidConfig(const std::string& msg) const      { throw std::invalid_argument(msg); }
    void _assert(bool condition, const std::string& msg) const  { if (!condition) _throwInvalidConfig(msg); }
};
}
#endif
