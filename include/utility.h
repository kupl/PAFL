#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <limits>
#include <cmath>


namespace PAFL
{
namespace Coef
{
    float Tarantula(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
        { return Ncs + Ncf ? Ncf / (Ncf + Nf * Ncs / (float)Ns) : 0.0f; }
    float Ochiai(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
        { size_t denom = Nf * (Ncf + Ncs); return denom ? Ncf / std::sqrt((float)denom) : 0.0f; }
    float Dstar(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
        { size_t denom = Ncs + Nf - Ncf; return denom ? Ncf * Ncf / (float)denom : std::numeric_limits<float>::infinity(); }
    float Barinel(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
        { size_t denom = Ncs + Ncf; return denom ? Ncf / (float)denom : 0.0f; }
}

namespace Normalizer
{
    float SqrtOchiai(float sus, float higest) // 2
        { return sus > 0.0f ? std::sqrt(sus / higest) : 0.0f; }
    float CbrtOchiai(float sus, float higest) // 3
        { return sus > 0.0f ? std::cbrt(sus / higest) : 0.0f; }
    float BqrtOchiai(float sus, float higest) // 4
        { return sus > 0.0f ? std::sqrt(std::sqrt(sus / higest)) : 0.0f; }
}
}
#endif
