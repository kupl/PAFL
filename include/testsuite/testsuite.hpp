#ifndef __TESTSUITE_HPP__
#define __TESTSUITE_HPP__

namespace PAFL
{
template <class Func>
void TestSuite::setBaseSus(Func func)
{
    for (auto& map : _line_param)
        for (auto& item : map) {
            
            auto sus = func(_succ, _fail, item.second.Ncs, item.second.Ncf);
            item.second.ptr_ranking->base_sus = sus;

            if (_highest_sus < sus)
                _highest_sus = sus;
            if (_finite_highest_sus < sus && sus < std::numeric_limits<float>::infinity())
                _finite_highest_sus = sus;
        }
}



template <class Func>
void TestSuite::normalizeBaseSus(Func func)
{
    for (auto& file : _line_param)
        for (auto& item : file) {

            auto& ref = item.second.ptr_ranking->base_sus;
            ref = func(ref, this->_highest_sus, this->_finite_highest_sus);
        }
}
}
#endif
