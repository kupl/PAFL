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
    const std::string& getName() const              { return _name; }
    virtual void setSus(TestSuite* suite) const = 0;

private:
    std::string _name;

};
}


namespace PAFL
{
class Tarantula : public Method
{
public:
    void setSus(TestSuite* suite) const override {
        suite->setSus(Coef::Tarantula);
    }
};


class Ochiai : public Method
{
public:
    void setSus(TestSuite* suite) const override {
        suite->setSus(Coef::Ochiai);
    }
};


class Dstar : public Method
{
public:
    void setSus(TestSuite* suite) const override {
        suite->setSus(Coef::Dstar);
    }
};


class Jaccard : public Method
{
public:
    void setSus(TestSuite* suite) const override {
        suite->setSus(Coef::Jaccard);
    }
};


class Ones : public Method
{
public:
    void setSus(TestSuite* suite) const override {
        suite->setSus(Coef::Ones);
    }
};


class CusmtomMethod : public Method
{
public:
    CusmtomMethod(const std::filesystem::path& metadata) : Method(), _metadata(metadata) {}
    void setSus(TestSuite* suite) const override
    {
        rapidjson::Document doc;
        doc.Parse(StringEditor::read(_metadata.c_str()).c_str());
        suite->readSus(doc);
    }
private:
    std::filesystem::path _metadata;
};
}
#endif
