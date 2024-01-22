#ifndef __TESTSUITE_GCOV_H__
#define __TESTSUITE_GCOV_H__

#include "testsuite/testsuite.h"


namespace PAFL
{
class TestSuiteGcov : public TestSuite
{
public:
    virtual void addTestCase(const rapidjson::Document& d, bool is_successed, const string_set& extensions) override;
};
}
#endif
