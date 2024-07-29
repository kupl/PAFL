#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <limits>
#include <cmath>


namespace PAFL
{
namespace Coef
{
    // Tarantula
    constexpr float Tarantula(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
    {
        return Ncs + Ncf ? Ncf / (Ncf + Nf * Ncs / (float)Ns) : 0.0f;
    }

    // Ochiai
    constexpr float Ochiai(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
    {
        size_t denom = Nf * (Ncf + Ncs);
        return denom ? Ncf / std::sqrt((float)denom) : 0.0f;
    }

    // Dstar2
    constexpr float Dstar(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
    {
        size_t denom = Ncs + Nf - Ncf;
        return denom ? Ncf * Ncf / (float)denom : std::numeric_limits<float>::infinity();
    }

    // Barinel
    constexpr float Barinel(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
    {
        size_t denom = Ncs + Ncf;
        return denom ? Ncf / (float)denom : 0.0f;
    }

    // Jaccard
    constexpr float Jaccard(size_t Ns, size_t Nf, size_t Ncs, size_t Ncf)
    {
        size_t denom = Nf + Ncs;
        return denom ? Ncf / (float)denom : 0.0f;
    }

    // sus = 1
    constexpr float Ones(size_t, size_t, size_t, size_t)
    {
        return 1.0f;
    }
}


namespace Normalization
{
    float Default(float sus, float highest, float finite_highest, float lowest_nonzero, float lower_bound);
    float Linear(float sus, float highest, float finite_highest, float lowest_nonzero);
    float Sqrt(float sus, float highest, float finite_highest, float lowest_nonzero);
    float Cbrt(float sus, float highest, float finite_highest, float lowest_nonzero);
    float Qdrt(float sus, float highest, float finite_highest, float lowest_nonzero);
}
}
#endif
