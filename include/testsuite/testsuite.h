#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/string.hpp>
#include <stringeditor.h>

#include "rapidjson/document.h"


namespace PAFL
{
class TestSuite
{
public:
    using line_t = uint32_t;
    using index_t = uint16_t;

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
        std::vector<std::pair<index_t, line_t>> lines; bool is_passed;
        template <class Archive> void serialize(Archive& ar)    { ar(lines, is_passed); }
    };

    struct _Hash { size_t operator()(const std::pair<index_t, line_t>& item) const { return std::hash<line_t>()(item.second); } };
    using fault_set_t = std::unordered_set<std::pair<index_t, line_t>, _Hash>;
    using content_t = std::vector<std::unordered_map<line_t, Param>>;
    
    struct Copy
    {
        std::vector<std::unordered_map<line_t, Param>> content;
        std::list<Ranking> ranking;
        Copy(const TestSuite& suite);
        void rank();
        line_t getFirstRanking(const fault_set_t& faults) const;
    };


public:
    TestSuite();
    TestSuite& operator=(const TestSuite&) = delete;
    TestSuite(TestSuite&) = delete;
    TestSuite(TestSuite&& rhs) = delete;

    virtual void addTestCase(const rapidjson::Document& doc, bool is_passed) {}

    // Set the suspiciousness values using formula
    template <class Func>
    void setSus(Func func);
    // Set the suspiciousness values using metadata
    /*
        JSON format
        {
            "lines": [
                {
                    "file": "PATH",
                    "lineno": UINT,
                    "sus": FLOAT
                },

                ...
            
            ]
        }
    */
    void readSus(const rapidjson::Document& doc);
    // Normalize the suspiciousness values
    template <class Func>
    void normalizeSus(Func func);
    // Set the suspiciousness values to original values
    void setSusToBase()                                         { for (auto& info : _ranking) info.sus = info.base_sus; }

    void rank();
    line_t getFirstRanking(const fault_set_t& faults) const;
    float getAverageRanking(const fault_set_t& faults) const;

    content_t& content()                                        { return _content; }
    const std::vector<TestCase>& getTestCases() const           { return _testcase_vec; }
    index_t getIndexFromFile(const std::string& file) const     { return _file2index.contains(file) ? _file2index.at(file) : std::numeric_limits<index_t>::max(); }
    index_t maxIndex() const                                    { return _index2file.size(); }
    const std::string& getFileFromIndex(index_t idx) const      { return _index2file.at(idx); }
    // Return total statements
    size_t size() const                                         { return _ranking.size(); }

    /*
        JSON format
        {
            "locations": [
                {
                    "file": "PATH",
                    "lines": [ INT, ... ]
                },

                ...
            
            ]
        }
    */
    fault_set_t makeFalutSet(const rapidjson::Document& doc) const;

    size_t getNumFail() const                                   { return _fail; }
    size_t getNumPass() const                                   { return _succ; }
    float getBaseSus(index_t idx, line_t line) const            { return _content.at(idx).contains(line) ? _content[idx].at(line).ranking_ptr->base_sus : 0.0f; }
    float getSus(index_t idx, line_t line) const                { return _content.at(idx).contains(line) ? _content[idx].at(line).ranking_ptr->sus : 0.0f; }
    float getHighestBaseSus() const                             { return _highest; }
    float getFiniteHighestBaseSus() const                       { return _finite_highest; }
    float getLowestNonzeroBaseSus() const                       { return _lowest_nonzero; }

    // Make ranking information to JSON format
    std::string toJson() const;
    void saveAsCovMatrix(const std::filesystem::path& dir, const fault_set_t& faults) const;
    template <class Archive>
    void save(Archive& ar) const;
    template <class Archive>
    void load(Archive& ar);


protected:
    size_t _succ;
    size_t _fail;
    float _highest;
    float _finite_highest;
    float _lowest_nonzero;

    std::vector<std::string> _index2file;
    std::unordered_map<std::string, index_t> _file2index;

    // _content [INDEX] [LINE] = Param
    content_t _content;
    std::list<Ranking> _ranking;
    std::vector<TestCase> _testcase_vec;

private:
    void _initBoundary() { constexpr auto inf = std::numeric_limits<float>::infinity(); _highest = -inf; _finite_highest = -inf; _lowest_nonzero = inf; }
};
}
#include "testsuite.hpp"
#endif
