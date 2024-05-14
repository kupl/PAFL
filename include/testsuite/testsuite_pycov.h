#ifndef __TESTSUITE_PYCOV_H__
#define __TESTSUITE_PYCOV_H__

#include "testsuite/testsuite.h"


namespace PAFL
{
class TestSuitePycov : public TestSuite
{
public:
    TestSuitePycov() : TestSuite(), _extensions{".py"} {}
    virtual void addTestCase(const rapidjson::Document& doc, bool is_passed) override;

private:
    const std::set<std::string> _extensions;
};
}
#endif

