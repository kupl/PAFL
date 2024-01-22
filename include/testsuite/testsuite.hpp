#ifndef __TESTSUITE_HPP__
#define __TESTSUITE_HPP__

namespace PAFL
{
template <class Func>
void TestSuite::setBaseSus(Func func)
{
    for (auto& map : _line_param)
        for (auto& item : map) {

            item.second.ptr_ranking->sus = item.second.ptr_ranking->base_sus
            = func(_succ, _fail, item.second.Ncs, item.second.Ncf);
            if (_highest_sus < item.second.ptr_ranking->base_sus) {

                _highest_sus = item.second.ptr_ranking->base_sus;
                if (_highest_sus < std::numeric_limits<float>::infinity())
                    _finite_highest_sus = _highest_sus;
            }
        }
}
}
#endif
