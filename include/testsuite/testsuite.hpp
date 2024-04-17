namespace PAFL
{
template <class Func>
void TestSuite::setBaseSus(Func func)
{
    _initBoundary();
    for (auto& map : _param_container)
        for (auto& item : map) {
            
            auto sus = func(_succ, _fail, item.second.Ncs, item.second.Ncf);
            item.second.ranking_ptr->base_sus = sus;

            if (_highest < sus)
                _highest = sus;
            if (_finite_highest < sus && sus < std::numeric_limits<float>::infinity())
                _finite_highest = sus;
            if (sus > 0.0f && sus < _lowest_nonzero)
                _lowest_nonzero = sus;
        }
}



template <class Func>
void TestSuite::normalizeBaseSus(Func func)
{
    for (auto& file : _param_container)
        for (auto& item : file) {

            auto& ref = item.second.ranking_ptr->base_sus;
            ref = func(ref, _highest, _finite_highest, _lowest_nonzero);
        }
}



template <class Archive>
void TestSuite::save(Archive& ar) const
{
    ar(_succ, _fail, _highest, _finite_highest, _lowest_nonzero, _index2file, _file2index, _param_container, _ranking, _total_test_case);
}



template <class Archive>
void TestSuite::load(Archive& ar)
{
    ar(_succ, _fail, _highest, _finite_highest, _lowest_nonzero, _index2file, _file2index, _param_container, _ranking, _total_test_case);
    for (auto& ranking : _ranking)
        _param_container.at(ranking.index).at(ranking.line).ranking_ptr = &ranking;
}
}
