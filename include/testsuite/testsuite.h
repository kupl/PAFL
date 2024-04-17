#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include <fstream>
#include <vector>
#include <algorithm>
#include <charconv>
#include <map>

#include <cereal/archives/binary.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/string.hpp>

#include "type.h"
#include "rapidjson.h"
#include "stringeditor.h"


namespace PAFL
{
class TestSuite
{
public:
    struct Ranking
    {
        index_t index; line_t line; float base_sus, sus; line_t ranking;
        template <class Archive> void serialize(Archive& ar)    { ar(index, line, base_sus, sus, ranking); }
    };

    struct Param
    {
        size_t Ncs, Ncf; Ranking* ranking_ptr;
        template <class Archive> void serialize(Archive& ar)    { ar(Ncs, Ncf); }
    };

    struct TestCase
    {
        std::list<std::pair<index_t, line_t>> lines; bool is_passed;
        template <class Archive> void serialize(Archive& ar)    { ar(lines, is_passed); }
    };

    using TotalTestCase = std::list<TestCase>;
    using FaultSet = std::unordered_set<const Param*>;

public:
    TestSuite();
    TestSuite& operator=(const TestSuite&) = delete;
    TestSuite(const TestSuite&) = delete;
    TestSuite(const TestSuite&& rhs) = delete;
    virtual void addTestCase(const rapidjson::Document& doc, bool is_successed, const string_set& extensions) = 0;
    void oversample(size_t iter);

    template <class Func>
    void setBaseSus(Func func);
    template <class Func>
    void normalizeBaseSus(Func func);
    void assignBaseSus()                                        { for (auto& info : _ranking) info.sus = info.base_sus; }
    const std::list<Ranking>& rank();

    index_t getIndexFromFile(const std::string& file) const;
    index_t maxIndex() const                                    { return _index2file.size(); }
    const std::string& getFileFromIndex(index_t idx) const      { return _index2file[idx]; }
    Ranking* getRankingInfo(index_t idx, line_t line)           { return _param_container[idx].contains(line) ? _param_container[idx].at(line).ranking_ptr : nullptr; }
    FaultSet toFaultSet(const fault_loc& faults) const;
    line_t getFirstRanking(const fault_loc& faults) const;
    const TotalTestCase& getTotalTestCase() const               { return _total_test_case; }

    size_t getNumFail() const                                   { return _fail; }
    size_t getNumSucc() const                                   { return _succ; }
    float getBaseSus(index_t idx, line_t line) const            { return _param_container[idx].contains(line) ? _param_container[idx].at(line).ranking_ptr->base_sus : 0.0f; }
    float getSus(index_t idx, line_t line) const                { return _param_container[idx].contains(line) ? _param_container[idx].at(line).ranking_ptr->sus : 0.0f; }
    float getHighestBaseSus() const                             { return _highest; }
    float getFiniteHighestBaseSus() const                       { return _finite_highest; }
    float getLowestNonzeroBaseSus() const                       { return _lowest_nonzero; }

    void caching(const fs::path& path) const;
    int readCache(const fs::path& path);
    void toJson(const fs::path& path) const;
    void toCovMatrix(const fs::path& dir, const fault_loc& faults) const;
    int loadBaseSus(const fs::path& path);

    template <class Archive>
    void save(Archive& ar) const;
    template <class Archive>
    void load(Archive& ar);

    decltype(auto) begin()                                      { return _param_container.begin(); }
    decltype(auto) end()                                        { return _param_container.end(); }
    decltype(auto) cbegin() const                               { return _param_container.cbegin(); }
    decltype(auto) cend() const                                 { return _param_container.cend(); }

protected:
    size_t _succ;
    size_t _fail;
    float _highest;
    float _finite_highest;
    float _lowest_nonzero;

    std::vector<std::string> _index2file;
    std::unordered_map<std::string, index_t> _file2index;

    // _param_container [INDEX] [LINE] = Param
    std::vector<std::map<line_t, Param>> _param_container;
    std::list<Ranking> _ranking;
    TotalTestCase _total_test_case;

private:
    void _initBoundary() { constexpr auto inf = std::numeric_limits<float>::infinity(); _highest = -inf; _finite_highest = -inf; _lowest_nonzero = inf; }
};
}
#include "testsuite.hpp"
#endif
