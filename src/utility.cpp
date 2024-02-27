#include "utility.h"

namespace PAFL
{
namespace Normalization
{
    float Default(float sus, float highest, float finite_highest, float lowest_nonzero)
    {
        constexpr float min = 0.6f * 0.6f * 0.6f * 0.6f;
        if (highest >= std::numeric_limits<float>::infinity())
            highest = finite_highest * 2;
        return sus >= std::numeric_limits<float>::infinity() ? 1.0f : (sus / highest) * (1.0f - min) + min ;
    }
    
    float Sqrt(float sus, float highest, float finite_highest, float lowest_nonzero)
    {
        sus = Default(sus, highest, finite_highest, lowest_nonzero);
        return sus > 0.0f ? std::sqrt(sus) : 0.0f;
    }

    float Cbrt(float sus, float highest, float finite_highest, float lowest_nonzero)
    {
        sus = Default(sus, highest, finite_highest, lowest_nonzero);
        return sus > 0.0f ? std::cbrt(sus) : 0.0f;
    }

    float Qdrt(float sus, float highest, float finite_highest, float lowest_nonzero)
    {
        sus = Default(sus, highest, finite_highest, lowest_nonzero);
        return sus > 0.0f ? std::sqrt(std::sqrt(sus)) : 0.0f;
    }
}
}
