#ifndef __FLMODEL_HPP__
#define __FLMODEL_HPP__

namespace PAFL
{
template <class Func>
void normalizeBaseSus(TestSuite& suite, Func func)
{
    auto highest = suite.getHighestBaseSus();
    auto finite_highest = suite.getFiniteHighestBaseSus();

    for (auto& file : suite)
        for (auto& line_param : file) {

            auto& ref = line_param.second.ptr_ranking->base_sus;
            ref = func(ref, highest, finite_highest);
        }
}
}
#endif
