#ifndef __TESTSUITE_HPP__
#define __TESTSUITE_HPP__

namespace PAFL
{
template <class Func>
void TestSuite::setBaseSus(Func func)
{
    _initBoundary();
    for (auto& map : _line_param)
        for (auto& item : map) {
            
            auto sus = func(_succ, _fail, item.second.Ncs, item.second.Ncf);
            item.second.ptr_ranking->base_sus = sus;

            if (_highest_sus < sus)
                _highest_sus = sus;
            if (_finite_highest_sus < sus && sus < std::numeric_limits<float>::infinity())
                _finite_highest_sus = sus;
            if (sus > 0.0f && sus < _lowest_nonzero_sus)
                _lowest_nonzero_sus = sus;
        }
}



template <class Func>
void TestSuite::normalizeBaseSus(Func func)
{
    for (auto& file : _line_param)
        for (auto& item : file) {

            auto& ref = item.second.ptr_ranking->base_sus;
            ref = func(ref, _highest_sus, _finite_highest_sus, _lowest_nonzero_sus);
        }
}
}
#endif
