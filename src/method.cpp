#include "method.h"

namespace PAFL
{
void Tarantula::setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const
{
    suite->setBaseSus(Coef::Tarantula);
}



void Ochiai::setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const
{
    suite->setBaseSus(Coef::Ochiai);
}



void Dstar::setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const
{
    suite->setBaseSus(Coef::Dstar);
}



void Barinel::setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const
{
    suite->setBaseSus(Coef::Barinel);
}



void Ones::setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const
{
    suite->setBaseSus(Coef::Ones);
}



void CusmtomMethod::setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const
{
    suite->loadBaseSus(FILE_PATH(proj, ver, iter));
}



CusmtomMethod::CusmtomMethod(const std::string& name, const fs::path& path) :
    Method(name)
{
    // Check existence of method configuration
    if (!fs::exists(path / "methods"))
        _throwInvalidMethod("File 'methods' is missing.");

    std::ifstream ifs(path / "methods");
    ifs.seekg(0, std::ios::end);
    auto size = ifs.tellg();
    std::string buf(size, ' ');
    ifs.seekg(0);
    ifs.read(&buf[0], size); 
    
    // Find the line starts with {name}
    auto pos = buf.find(name);
    _assert(pos != std::string::npos, std::string("Method \"") + name + "\" is not exist.");
    auto line = buf.substr(pos, buf.find('\n', pos));
    std::cout << line << '\n';
    
    // Read file
    std::istringstream iss(buf);
    std::string token;
    iss >> token;
    iss >> token;
    _assert(token == "=", "'=' is missing");

    while (iss >> token) {
                
        if (token[0] == '"' && token[token.size() - 1] == '"')
            FILE_PATH.emplace_back(Token::Type::STRING, token.substr(1, token.size() - 2));
        else if (token == "PROJ")
            FILE_PATH.emplace_back(Token::Type::PROJ, "PROJ");
        else if (token == "VER")
            FILE_PATH.emplace_back(Token::Type::VER, "VER");
        else if (token == "ITER")
            FILE_PATH.emplace_back(Token::Type::ITER, "ITER");
        else
            _throwInvalidMethod(std::string("Invalid token. Valid tokens are { PROJ | VER | ITER | \"string\" }") + ", but " + token);
    }
}



CusmtomMethod::Token::Token(CusmtomMethod::Token::Type ttype, const std::string& str) :
    _str(str)
{
    switch (ttype) {

    case CusmtomMethod::Token::Type::STRING: _func = &CusmtomMethod::Token::_STR; break;
    case CusmtomMethod::Token::Type::PROJ: _func = &CusmtomMethod::Token::_PROJ; break;
    case CusmtomMethod::Token::Type::VER: _func = &CusmtomMethod::Token::_VER; break;
    case CusmtomMethod::Token::Type::ITER: _func = &CusmtomMethod::Token::_ITER;
    }
}
}
