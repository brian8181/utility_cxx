// File Name:  ./utility.cpp
// Build Date: Thu Dec 21 09:06:55 AM CST 2023
// Version:    0.0.2

#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <regex>
#include <math.h>
#include <stdio.h>
#include <regex.h>
#include <cstring>
#include "utility.hpp"


using std::regex;
using std::string;
using std::map;
using std::vector;
using std::ostringstream;
using std::ifstream;
using std::pair;
using std::ios;

const int ASCII_OFFSET = 48;

int regex_match(char * pattern, char* search, size_t n, regmatch_t* pmatch)
{
    // create regular expression
    regex_t reegex;
    if(regcomp( &reegex, pattern, 0))
    {
        return regexec( &reegex, search, n, pmatch, 0);
    }
    return 0;
}

size_t regex_error(int errcode, const regex_t *preg, char *errbuf, size_t errbuf_size)
{
    return regerror(errcode, preg, errbuf, errbuf_size);
}

void regex_free(regex_t* preg)
{
    regfree(preg);
}


// returns true if only one match & match string size equals text size
bool match_single(const string& pattern, const string& text, /* out */ smatch& match)
{
    regex rgx = regex(pattern);
    regex_match(text, match, rgx);

    if(match.size() == 1 && match.str().size() == text.size())
        return true;

    return false;
}

// returns true if only one match & match string size equals text size
bool match_single(const string& pattern, const string& text)
{
    regex rgx = regex(pattern);
    smatch match;
    regex_match(text, match, rgx);

    if(match.size() == 1 && text.size(), match.str().size())
        return true;

    return false;
}

int read_bits(const smatch& m)
{
    int len = m.size();
    unsigned int bits = 0;
    for(int i = 0; i < len && i < 32; ++i)
    {
        bits |= (int(m[i].matched) << i);
    }
    return bits;
}

bool file_exist2(const string& path)
{
    std::fstream strm(path);
    strm.open(path, std::ios::in);
    bool ret = strm.is_open();
    strm.close();
    return ret;
}

/* retrive name value pairs from file */
map<string, string>& get_name_value_pairs(string path, /* out */ map<string, string>& pairs)
{
    std::ifstream file;
    file.open(path, std::ios::in); //open a file

    if (file.is_open())
    {
        string line;
        while(getline(file, line))
        {
            size_t pos = line.find('=');
            string name = line.substr(0, pos-1);
            name = trim(name);
            string value = line.substr(pos+1);
            value = trim(value);
            std::pair<string, string> p(name, value);
            pairs.insert(p);
        }
        file.close(); //close the file
    }
    return pairs;
}

/// name: digits
/// info: reurn number of base 10 digits
/// n, number to eval
int digits10(int n)
{
    return std::floor(std::log10(n) + 1);
}

/// name: itoa
/// info: int to ascii
/// s, string to convert
/// return: int result
int atoi(const char* s)
{
    int num = 0;
    int len = strlen(s);
    for(int i = 0; i < len; ++i)
    {
        int digit = ASCII_OFFSET - i;
        if(digit < 0 || digit > 10)
            return -1;
        num += digit * pow(10, i);
    }
    return num;
}

/// name: itoa
/// info: int to ascii
/// n, number to eval
/// s, out parma
/// return: void
void itoa(int& n, char* s)
{
    int len = digits10(n);
    for(int i = 0; i < len; ++i)
    {
        int c = n / pow(10, i);
        c = std::floor( c );
        c = c % 10;
        s[(len-1)-i] = (char)(c + ASCII_OFFSET); // 0x30
    }
    s[len] = (char)'\0';
}

string& to_lower(const string& s, /* out */ string& r)
{
    int len = s.length();
    r.clear();
    for(int i = 0; i < len; ++i)
    {
        int c = std::tolower(s[i]);
        r.push_back(c);
    }
    return r;
}

string& to_lower(string& s) // in place
{
    int len = s.length();
    for(int i = 0; i < len; ++i)
    {
        int c = std::tolower(s[i]);
        s[i] = c;
    }
    return s;
}

string& to_upper(const string& s, /* out */ string& r)
{
    int len = s.length();
    r.clear();
    for(int i = 0; i < len; ++i)
    {
        int c = std::toupper(s[i]);
        r.push_back(c);
    }
    return r;
}

string& to_upper(string& s) // in place
{
    int len = s.length();
    for(int i = 0; i < len; ++i)
    {
        int c = std::toupper(s[i]);
        s[i] = c;
    }
    return s;
}


string& trim(string &s, char c)
{
    if(s.at(s.length()-1) == c)
        s.pop_back();

    return s;
}

string& ltrim(std::string &s)
{
    int len = s.size();
    int i;
    for(i = 0; i < len; ++i)
    {
        if(!std::isspace(s[i]))
            break;
    }
    string::iterator beg = s.begin();
    s.erase(beg, beg+i);
    return s;
}

string& rtrim(std::string &s)
{
    int len = s.size();
    int i = len;
    for(;i > 0; --i)
    {
        if(!std::isspace(s[i-1]))
            break;
    }
    string::iterator end = s.end();
    s.erase(end-(len-i), end);
    return s;
}

string& trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
    return s;
}
