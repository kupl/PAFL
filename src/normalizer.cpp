#include "normalizer.h"

namespace PAFL
{
void LinearNormalizer::normalize(TestSuite* suite) const
{
    suite->normalizeBaseSus(Normalization::Default);
    suite->assignBaseSus();
}



void SqrtNormalizer::normalize(TestSuite* suite) const
{
    suite->normalizeBaseSus(Normalization::Sqrt);
    suite->assignBaseSus();
}



void CbrtNormalizer::normalize(TestSuite* suite) const
{
    suite->normalizeBaseSus(Normalization::Cbrt);
    suite->assignBaseSus();
}



void QdrtNormalizer::normalize(TestSuite* suite) const
{
    suite->normalizeBaseSus(Normalization::Qdrt);
    suite->assignBaseSus();
}
}

