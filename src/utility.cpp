#include "utility.h"

namespace PAFL
{
namespace Normalization
{
    float Default(float sus, float highest, float finite_highest, float lowest_nonzero, float lower_bound)
    {
        if (sus < lowest_nonzero)
            return 0.0f;

        if (highest >= std::numeric_limits<float>::infinity())
            highest = finite_highest * 1.5f;
        return sus >= std::numeric_limits<float>::infinity() ? 1.0f : ((sus - lowest_nonzero) / (highest - lowest_nonzero)) * (1.0f - lower_bound) + lower_bound;
    }

    float Linear(float sus, float highest, float finite_highest, float lowest_nonzero)
    {
        constexpr float lb = 0.5f;
        return Default(sus, highest, finite_highest, lowest_nonzero, lb);
    }
    
    float Sqrt(float sus, float highest, float finite_highest, float lowest_nonzero)
    {
        constexpr float lb = 0.5f * 0.5f;
        sus = Default(sus, highest, finite_highest, lowest_nonzero, lb);
        return sus > 0.0f ? std::sqrt(sus) : 0.0f;
    }

    float Cbrt(float sus, float highest, float finite_highest, float lowest_nonzero)
    {
        constexpr float lb = 0.5f * 0.5f * 0.5f;
        sus = Default(sus, highest, finite_highest, lowest_nonzero, lb);
        return sus > 0.0f ? std::cbrt(sus) : 0.0f;
    }

    float Qdrt(float sus, float highest, float finite_highest, float lowest_nonzero)
    {
        constexpr float lb = 0.5f * 0.5f * 0.5f * 0.5f;
        sus = Default(sus, highest, finite_highest, lowest_nonzero, lb);
        return sus > 0.0f ? std::sqrt(std::sqrt(sus)) : 0.0f;
    }
}
}
