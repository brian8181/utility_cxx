// File Name:  logger.cpp
// Build Date: Thu Oct 31 01:46:28 PM CDT 2024
// Version:    0.0.1

#include <iostream>
#include <string>
#include <fstream>
#include "logger.hpp"

using std::string;
using std::fstream;
using std::endl;

logger* logger::_instance = 0;

const static string BEGIN = "************ Begin Log **************";
const static string END   = "************ End Log ****************";


logger::logger()
{

}

logger::~logger()
{
    strm.close();
    delete _instance;
}

logger* logger::instance()
{
    if(logger::_instance != 0)
    {
        return logger::_instance;
    }

    logger::_instance = new logger();
    return logger::_instance;
}

void logger::open(const string& log_file)
{
    strm.open (log_file, std::fstream::in | std::fstream::out | std::fstream::app);
}

void logger::log(const string& msg)
{
    strm << msg << endl;
}

void logger::log(const string& msg, const string& src)
{
    log(msg);
}

void logger::log(const string& msg, long line_n)
{
    log(msg);
}

logger& logger::operator<<(string msg)
{
    strm << msg;
    return *this;
}

logger& logger::operator<<(int n)
{
    strm << n;
    return *this;
}

void logger::log(const string& msg, const string& src, long line_n)
{
    log(msg);
    // strm << "LINE: " << __LINE__ << " OF FILE: " << __FILE__ << " " << __TIME__ << " " << __DATE__ << std::endl;
    // strm << msg << " line: " << line_n << " src: " << " \"" + src + "\" " << std::endl;
}

fstream& operator<<(fstream& os, const logger& log)
{
    os << "testing";
    return os;
}

