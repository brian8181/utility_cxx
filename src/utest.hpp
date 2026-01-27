#ifndef _utest_HPP
#define _utest_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <fmt/color.h>

using std::string;
using std::cout;
using std::endl;

//namespace fs = std::filesystem;

enum Result
{
    PASS = 0x1,
    FAIL = 0x2,
    INCONCLUSIVE = 0x10,
    IGNORE = 0x20
};

void print_assert(bool assert, string name)
{
    string s = (assert ? "PASSED" : "FAILED");
    s.append(": " + name );
    //fmt::print(fg(assert ? fmt::color::green : fmt::color::red) | fmt::emphasis::bold, s + '\n');
}

template<typename T>
bool ASSERT_IS(T& actual, T& expected)
{
    bool assert = (&actual == &expected);
    print_assert(assert, "ASSERT_IS");
    return assert;
}

template<typename T>
bool ASSERT_EQUAL (T actual, T expected)
{
    bool assert = (actual == expected);
    print_assert(assert, "ASSERT_EQUAL");
    return assert;
}

template<typename T>
bool ASSERT_NOT_EQUAL (T actual, T expected)
{
    bool assert = (&actual == &expected);
    print_assert(assert, "ASSERT_NOT_EQUAL");
    return assert;
}

template<typename T>
bool ASSERT_GREATER_THAN (T actual, T expected)
{
   bool assert = (&actual == &expected);
    print_assert(assert, "ASSERT_GRETER_THAN");
    return assert;
}

template<typename T>
bool ASSERT_LESS_THAN (T actual, T expected)
{
    bool assert = (actual < expected);
    print_assert(assert, "ASSERT_LESS_THAN");
    return assert;
}

template<typename T>
bool ASSERT_NOT_LESS_THAN (T actual, T expected)
{
    bool assert = (!(actual < expected));
    print_assert(assert, "ASSERT_NOT_LESS_THAN");
    return assert;
}

template<typename T>
bool ASSERT_NOT_GREATER_THAN (T actual, T expected)
{
    bool assert = (!(actual > expected));
    print_assert(assert, "ASSERT_NOT_GREATER_THAN");
    return assert;
}

void ASSERT_INCONCLUSIVE ()
{
    print_assert(false, "ASSERT_INCONCLUSIVE");
}

void ASSERT_FAIL()
{
    print_assert(false, "ASSERT_FAIL");
}

void ASSERT_PASS ()
{
    print_assert(true, "ASSERT_PASS");
}

void ASSERT_IGNORE ()
{
    print_assert(true, "ASSERT_INGONED");

}

bool ASSERT_FILE (const string& path)
{
    bool assert = std::filesystem::exists(path);
    print_assert(assert, "ASSERT_FILE");
    return assert;
}

bool ASSERT_DIRECTORY (const string& path)
{
    std::filesystem::directory_entry dir_entry(path);
    bool assert = dir_entry.is_directory();
    print_assert(assert, "ASSERT_DIRECTORY");
    return assert;
}

#endif
