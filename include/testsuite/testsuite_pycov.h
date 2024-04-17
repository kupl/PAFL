#ifndef __TESTSUITE_PYCOV_H__
#define __TESTSUITE_PYCOV_H__

#include "testsuite/testsuite.h"


namespace PAFL
{
class TestSuitePycov : public TestSuite
{
public:
    virtual void addTestCase(const rapidjson::Document& doc, bool is_successed, const string_set& extensions) override;
};
}
#endif

