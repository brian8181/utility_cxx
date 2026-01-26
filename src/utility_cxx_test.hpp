/**
 * @file    utility_cxx_test.hpp
 * @version 0.0.1
 * @date    Mon, 26 Jan 2026 20:02:33 +0000
 * @info    ...
 */
#ifndef _TEST_utility_cxx_test_H
#define _TEST_utility_cxx_test_H

#include <cppunit/Test.h>

class TEST_utility_cxx_test : public CppUnit::TestFixture
{
private:
    CPPUNIT_TEST_SUITE(TEST_utility_cxx_test);
    CPPUNIT_TEST(testNoOptions);
    CPPUNIT_TEST(testOptionHelp);
    CPPUNIT_TEST(testOptionHelpLong);
    CPPUNIT_TEST(testOptionVerbose);
    CPPUNIT_TEST(testOptionVerboseLong);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    // agregate test functions
    void execute();
    void execute(int argc, char* argv[]);

protected:
    void testNoOptions();
    void testOptionHelp();
    void testOptionHelpLong();
    void testOptionVerbose();
    void testOptionVerboseLong();

private:
    int m_argc;
    char* m_argv[10];

};

#endif
