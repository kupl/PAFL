#ifndef __NORMALIZER_H__
#define __NORMALIZER_H__

#include "utility.h"
#include "testsuite/testsuite.h"


namespace PAFL
{
class Normalizer
{
public:
    virtual void normalize(TestSuite* suite) const = 0;
};


class LinearNormalizer : public Normalizer
{
public:
    void normalize(TestSuite* suite) const override {
        suite->normalizeSus(Normalization::Linear);
    }
};


class SqrtNormalizer : public Normalizer
{
public:
    void normalize(TestSuite* suite) const override {
        suite->normalizeSus(Normalization::Sqrt);
    }
};


class CbrtNormalizer : public Normalizer
{
public:
    void normalize(TestSuite* suite) const override {
        suite->normalizeSus(Normalization::Cbrt);
    }
};


class QdrtNormalizer : public Normalizer
{
public:
    void normalize(TestSuite* suite) const override {
        suite->normalizeSus(Normalization::Qdrt);
    }
};
}
#endif
