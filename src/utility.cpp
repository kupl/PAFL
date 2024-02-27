#include "utility.h"

namespace PAFL
{
namespace Normalization
{
    float Default(float sus, float highest, float finite_highest)
    {
        if (highest >= std::numeric_limits<float>::infinity())
            highest = finite_highest * 2;
        return sus >= std::numeric_limits<float>::infinity() ? 1.0f : sus / highest;
    }
    
    float Sqrt(float sus, float highest, float finite_highest)
    {
        sus = Default(sus, highest, finite_highest);
        return sus > 0.0f ? std::sqrt(sus) : 0.0f;
    }

    float Cbrt(float sus, float highest, float finite_highest)
    {
        sus = Default(sus, highest, finite_highest);
        return sus > 0.0f ? std::cbrt(sus) : 0.0f;
    }

    float Qdrt(float sus, float highest, float finite_highest)
    {
        sus = Default(sus, highest, finite_highest);
        return sus > 0.0f ? std::sqrt(std::sqrt(sus)) : 0.0f;
    }
}
}
