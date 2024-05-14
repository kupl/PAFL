#ifndef __TESTSUITE_GCOV_H__
#define __TESTSUITE_GCOV_H__

#include "testsuite/testsuite.h"


namespace PAFL
{
class TestSuiteGcov : public TestSuite
{
public:
    TestSuiteGcov() : TestSuite(), _extensions{".c", ".cc", ".cpp", ".h", ".hpp"} {}
    virtual void addTestCase(const rapidjson::Document& doc, bool is_passed) override;

private:
    const std::set<std::string> _extensions;
};
}
#endif
