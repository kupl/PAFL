#include "config.h"

namespace PAFL
{
void Config::configure(PrgLang pl, const fs::path& path)
{
    // Generate default config
    if (!fs::exists(path / "config")) {

        std::ofstream config(path / "config");
        config << "#begin CPP\n\n" <<

                "PROJECT_LOC = \"buggy-\" VER\n" <<
                "TESTCASE_LOC = PROJ \"-buggy-\" VER \"-\" CASE\n\n" <<

                "COVERAGE_NAME = \"summary.json\"\n\n" <<

                "TEST_NAME = CASE \".test\"\n" <<
                "TEST_PASS = \"passed\"\n\n" <<

                "#end\n\n" <<
                
                "#begin PYTHON\n\n" <<

                "PROJECT_LOC = PROJ \"-\" VER \"/\" PROJ\n" <<
                "TESTCASE_LOC = PROJ \"-\" VER \"/\" PROJ \"/coverage/\" CASE\n\n" <<

                "COVERAGE_NAME = \"summary.json\"\n\n" <<

                "TEST_NAME = CASE \".test\"\n" <<
                "TEST_PASS = \"passed\"\n\n" <<

                "#end\n\n";
    }

    
    enum class State { ROOT, CONTENT, OTHERWISE };
    State state = State::ROOT;
    const std::unordered_map<std::string, PrgLang> lang_map{{"ALL", pl}, {"CPP", PrgLang::CPP}, {"C", PrgLang::CPP}, {"PYTHON", PrgLang::PYTHON}, {"JAVA", PrgLang::JAVA}};

    const std::unordered_map<std::string, Line*> var_map = {
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
            _assert(buf == "#begin", "'#begin' is missing");
            iss >> buf;
            _assert(lang_map.contains(buf), "Invalid language. Valid languages are { ALL | CPP | C | PYTHON | JAVA }");
            state = lang_map.at(buf) == pl ? State::CONTENT : State::OTHERWISE;
        }

        else if (state == State::CONTENT) {

            iss >> buf;
            if (buf.empty())
                continue;
            if (buf == "#end") {

                state = State::ROOT;
                continue;
            }
            if (!var_map.contains(buf))
                _throwInvalidConfig("Invalid variable. Valid variables are { PROJECT_LOC | TESTCASE_LOC | COVERAGE_NAME | TEST_NAME | TEST_PASS }");

            std::string equal;
            iss >> equal;
            if (equal != "=")
                _throwInvalidConfig("'=' after varialbe is missing");
            auto line_ptr = var_map.at(buf);

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
                    _throwInvalidConfig("Invalid token. Valid tokens are { PROJ | VER | CASE | \"string\" }");
            }
        }

        else { // State::OTHERWISE

            iss >> buf;
            if (buf == "#end")
                state = State::ROOT;
        }
    }

    if (state != State::ROOT)
        _throwInvalidConfig("'#end' is missing");
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
