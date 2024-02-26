#ifndef __METHOD_H__
#define __METHOD_H__

#include <fstream>
#include <sstream>
#include <iostream>

#include "utility.h"
#include "testsuite/testsuite.h"


namespace PAFL
{
class Method
{
public:
    Method(const std::string& name) : _name(name)   {}
    const std::string& getName() const              { return _name; }
    virtual void setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const = 0;

private:
    std::string _name;

};
}



namespace PAFL
{
class Tarantula : public Method
{
public:
    Tarantula(const std::string& name) : Method(name) {}
    void setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const override;
};



class Ochiai : public Method
{
public:
    Ochiai(const std::string& name) : Method(name) {}
    void setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const override;
};



class Dstar : public Method
{
public:
    Dstar(const std::string& name) : Method(name) {}
    void setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const override;
};



class Barinel : public Method
{
public:
    Barinel(const std::string& name) : Method(name) {}
    void setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const override;
};



class Ones : public Method
{
public:
    Ones(const std::string& name) : Method(name) {}
    void setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const override;
};



class CusmtomMethod : public Method
{
public:
    class Token
    {
    public:
        enum class Type { STRING, PROJ, VER, ITER };
        Token(Type ttype, const std::string& str);

        const std::string& operator()(const std::string& proj, const std::string& ver, const std::string& iter) const   { return (this->*_func)(proj, ver, iter); }

    private:
        const std::string& _STR(const std::string&, const std::string&, const std::string&) const                       { return _str; }
        const std::string& _PROJ(const std::string& proj, const std::string&, const std::string&) const                 { return proj; }
        const std::string& _VER(const std::string&, const std::string& ver, const std::string&) const                   { return ver; }
        const std::string& _ITER(const std::string&, const std::string&, const std::string& iter) const                 { return iter; }

        std::string _str;
        decltype(&CusmtomMethod::Token::operator()) _func;
    };


public:
    class Line : public std::list<Token>
    {
        public: std::string operator()(const std::string& proj, const std::string& ver, const std::string& iter) const
        {
            std::string ret;
            for (auto& tok : *this)
                ret.append(tok(proj, ver, iter));
            return ret;
        }
    };


public:
    CusmtomMethod(const std::string& name, const fs::path& path);
    void setBaseSus(TestSuite* suite, const std::string& proj, const std::string& ver, const std::string& iter) const override;

private:
    void _throwInvalidMethod(const std::string& msg) const                                                  { std::cerr << "Exception while read 'method'\n"; throw std::invalid_argument(msg); }
    void _assert(bool condition, const std::string& msg) const                                              { if (!condition) _throwInvalidMethod(msg); }

private:
    Line FILE_PATH;
};
}
/*
CNN-1 = "/ROOTDIR/CNN/CNN-1/" PROJ "/" ITER ".txt"
aeneas-ochiai = "/ROOTDIR/aeneas-ochiai/" PROJ "/" ITER ".txt"
*/
#endif
