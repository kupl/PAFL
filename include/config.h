#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <filesystem>
#include <fstream>
#include <sstream>

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

        const std::string& operator()(const std::string& proj, const std::string& ver, const std::string& tc) const
            { return (this->*_func)(proj, ver, tc); }

    private:
        const std::string& _STR(const std::string&, const std::string&, const std::string&) const
            { return _str; }
        const std::string& _PROJ(const std::string& proj, const std::string&, const std::string&) const
            { return proj; }
        const std::string& _VER(const std::string&, const std::string& ver, const std::string&) const
            { return ver; }
        const std::string& _CASE(const std::string&, const std::string&, const std::string& tc) const
            { return tc; }

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


    void configure(PrgLang pl, const fs::path& path);

    Line PROJECT_LOC; Line TESTCASE_LOC; Line COVERAGE_NAME;
    Line TEST_NAME; Line TEST_PASS;


private:
    void _throwInvalidConfig()
        { throw std::invalid_argument("Invalid config"); }
};
}






namespace PAFL
{
void Config::configure(PrgLang pl, const fs::path& path)
{
    // Generate default config
    if (!fs::exists(path / "config")) {

        std::ofstream config(path / "config");
        config << "#begin ALL\n\n" <<

                "PROJECT_LOC = \"buggy#\" VER\n" <<
                "TESTCASE_LOC = PROJ \"-buggy-\" VER \"-\" CASE\n\n" <<

                "COVERAGE_NAME = \"summary.json\"\n\n" <<

                "TEST_NAME = CASE \".test\"\n" <<
                "TEST_PASS = \"passed\"\n\n" <<

                "#end";    
    }

    
    enum class State { ROOT, CONTENT, OTHERWISE };
    State state = State::ROOT;
    const std::string lang(pl == PrgLang::CPP ? "CPP" : (pl == PrgLang::PYTHON ? "PYTHON" : "JAVA"));

    const std::unordered_map<std::string, Line*> map = {
        { "PROJECT_LOC", &PROJECT_LOC }, { "TESTCASE_LOC", &TESTCASE_LOC }, { "COVERAGE_NAME", &COVERAGE_NAME },
        { "TEST_NAME", &TEST_NAME }, { "TEST_PASS", &TEST_PASS }
    };

    std::ifstream config(path / "config");
    std::string is;
    while (std::getline(config, is)) {

        std::istringstream iss(is);
        std::string buf;

        if (state == State::ROOT) {

            iss >> buf;
            if (buf != "#begin")
                _throwInvalidConfig();
            iss >> buf;
            state = buf == "ALL" || buf == lang ? State::CONTENT : State::OTHERWISE;
        }

        else if (state == State::CONTENT) {

            iss >> buf;
            if (buf.empty())
                continue;
            if (buf == "#end") {

                state = State::ROOT;
                continue;
            }
            if (!map.contains(buf))
                _throwInvalidConfig();

            std::string equal;
            iss >> equal;
            if (equal != "=")
                _throwInvalidConfig();
            auto line_ptr = map.at(buf);

            while (iss >> buf) {
                
                if (buf[0] == '"' && buf[buf.size() - 1] == '"')
                    line_ptr->emplace_back(Token::Type::STRING, buf.substr(1, buf.size() - 2));
                else if (buf == "PROJ")
                    line_ptr->emplace_back(Token::Type::PROJ, "PROJ");
                else if (buf == "VER")
                    line_ptr->emplace_back(Token::Type::VER, "VER");
                else if (buf == "CASE")
                    line_ptr->emplace_back(Token::Type::CASE, "CASE");
                else
                    _throwInvalidConfig();
            }
        }

        else { // State::OTHERWISE

            iss >> buf;
            if (buf == "#end")
                state = State::ROOT;
        }
    }
}



Config::Token::Token(Config::Token::Type ttype, const std::string& str) :
    _str(str)
{
    switch (ttype) {

    case Config::Token::Type::STRING: _func = &Config::Token::_STR; break;
    case Config::Token::Type::PROJ: _func = &Config::Token::_PROJ; break;
    case Config::Token::Type::VER: _func = &Config::Token::_VER; break;
    case Config::Token::Type::CASE: _func = &Config::Token::_CASE;
    }
}
}
#endif
