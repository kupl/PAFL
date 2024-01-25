#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include <fstream>
#include <vector>
#include <algorithm>
#include <charconv>
#include <map>

#include "type.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"


namespace PAFL
{
class TestSuite
{
public:
    typedef struct { index_t index; line_t line; float base_sus, sus; line_t ranking; } ranking_info;
    typedef struct { size_t Ncs, Ncf; ranking_info* ptr_ranking; } param;
    typedef struct { std::list<std::pair<index_t, line_t>> lines; bool is_passed; } test_case;
    using test_suite = std::list<test_case>;

public:
    TestSuite() : _is_initialized(false), _fail(0), _highest_sus(-std::numeric_limits<float>::infinity()), _finite_highest_sus(-std::numeric_limits<float>::infinity()) {}
    virtual void addTestCase(const rapidjson::Document& d, bool is_successed, const string_set& extensions) = 0;
    void oversample(size_t iter);

    template <class Func>
    void setBaseSus(Func func);
    void assignBaseSus()                                        { for (auto& info : _ranking) info.sus = info.base_sus; }
    const std::list<ranking_info>& rank();

    index_t getIndexFromFile(const std::string& file) const;
    index_t maxIndex() const                                    { return _index2file.size(); }
    const std::string& getFileFromIndex(index_t idx) const      { return _index2file[idx]; }
    ranking_info* getRankingInfo(index_t idx, line_t line)      { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking : nullptr; }
    line_t getRankingSum(const fault_loc& faults) const;

    float getBaseSus(index_t idx, line_t line) const            { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking->base_sus : 0.0f; }
    float getSus(index_t idx, line_t line) const                { return _line_param[idx].contains(line) ? _line_param[idx].at(line).ptr_ranking->sus : 0.0f; }
    float getHighestBaseSus() const                             { return _highest_sus; }
    float getFiniteHighestBaseSus() const                       { return _finite_highest_sus; }
    size_t getNumFail() const                                   { return _fail; }
    size_t getNumSucc() const                                   { return _succ; }
    const test_suite& getTestSuite() const                      { return _test_suite; }

    void toJson(const fs::path& path) const;
    void caching(const fs::path& path) const;
    int loadCache(const fs::path& path);
    void toCovMatrix(const fs::path& dir, const fault_loc& faults) const;
    int loadBaseSus(const fs::path& path);

    decltype(auto) begin()                                      { return _line_param.begin(); }
    decltype(auto) end()                                        { return _line_param.end(); }
    decltype(auto) cbegin() const                               { return _line_param.cbegin(); }
    decltype(auto) cend() const                                 { return _line_param.cend(); }

private:
    template <class T>
    void _appendAny(std::string& str, T val) const
    {
        char buf[32];
        auto result_ptr = std::to_chars(buf, buf + 32, val).ptr;
        str.append(buf, result_ptr - buf);
    }
    void _appendAny(std::string& str, bool val) const                           { val ? str.push_back('1') : str.push_back('0'); }
    template <class T>
    void _appendAnyChar(std::string& str, T val, char c) const                  { _appendAny(str, val); str.push_back(c); }
    void _appendStrChar(std::string& lhs, const std::string& str, char c) const { lhs.append(str); lhs.push_back(c); }
    static constexpr size_t _MiB(size_t mib)                                    { return mib * 1024 * 1024; }


protected:
    bool _is_initialized;
    size_t _fail;
    size_t _succ;

    std::vector<std::string> _index2file;
    std::unordered_map<std::string, index_t> _file2index;

    std::vector<std::map<line_t, param>> _line_param;
    std::list<ranking_info> _ranking;
    float _highest_sus;
    float _finite_highest_sus;

    test_suite _test_suite;
};
}
#include "testsuite/testsuite.hpp"
#endif
