/**
 * @file    utility_cxx_test.hpp
 * @version 0.0.1
 * @date    Mon, 26 Jan 2026 20:02:33 +0000
 * @info    ...
 */
#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>
#include "utility_cxx_test_test.hpp"
#include <string.h>

using namespace CppUnit;
using namespace std;

//HACK!
int parse_options(int argc, char* argv[]);

void TEST_utility_cxx_test::setUp()
{
}

void TEST_utility_cxx_test::tearDown()
{
}

void TEST_utility_cxx_test::testNoOptions()
{
    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void TEST_utility_cxx_test::testOptionHelp()
{
    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void TEST_utility_cxx_test::testOptionHelpLong()
{
    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void TEST_utility_cxx_test::testOptionVerbose()
{
    CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void TEST_utility_cxx_test::testOptionVerboseLong()
{
   CPPUNIT_ASSERT(parse_options(m_argc, m_argv) == 0);
}

void TEST_utility_cxx_test::execute()
{
    // on head
    char** pstr = new char*;
    *pstr = (char*)"test";    // on the heap

    char** argv = new char*[1] {*pstr};
    //argv[0] = *pstr;

    execute(1, argv);

    delete pstr;
    delete [] argv;

    // on stack
    //char* argv_[3] {(char*)"./App", (char*)"abc", (char*)"abc"};
}

void TEST_utility_cxx_test::execute(int argc, char* argv[])
{

}

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_utility_cxx_test );

int main(int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output resint* pn = new int;ults in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("cppTEST_utility_cxx_testResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}
