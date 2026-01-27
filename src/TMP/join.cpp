// File Name:  join.cpp
// Build Date: Sun Mar  9 00:05:18 CST 2025
// Version:    0.0.1

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <getopt.h>
#include <fmt/color.h>
#include "bash_color.h"
#include "fileio.hpp"
#include "format.hpp"

using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

const string VERSION_STRING = "0.0.1";
const int DEFAULT_ARGC = 2;
const unsigned short VERBOSE          = 0x01;
const unsigned short DEFAULTS         = 0x00;
const unsigned short FIELDS           = 0x02;
unsigned short options = DEFAULTS;
char DELIMITER = ',';

typedef string line_t;
typedef vector<line_t> lines_t;
typedef string field_t;
typedef vector<field_t> record_t;
typedef vector<record_t> table_t;

static struct option long_options[] =
{
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'r'},
};

unsigned short OPTION_FLAGS = DEFAULTS;

void print_version()
{
	cout << VERSION_STRING << endl;
}

void print_help()
{
	cout	<< endl
			<< FMT_BOLD << FMT_FG_GREEN << "Usage: "            << FMT_RESET << endl
			<< FMT_BOLD << FMT_FG_BLUE  << "split"              << FMT_RESET << " "
			<< FMT_FG_BLUE              << "[-hvr][...]"        << FMT_RESET << " "
			                            << "FILE [FILE2 ... ]" << FMT_RESET << " "
																<<  endl << endl;
}

int parse_options(int argc, char* argv[])
{
	int opt = 0;
	int option_index = 0;
	optind = 0;
	while ((opt = getopt_long(argc, argv, "hvfd:", long_options, &option_index)) != -1)
	{
		switch (opt)
		{
			case 'h':
				print_help();
			case 'v':
				print_version();
				return 0;
			case 'f':
				options |= FIELDS;
			case 'd':
				DELIMITER=optarg[0];
		}
	}

	if (argc < DEFAULT_ARGC) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help" << endl;
		return -1;
	}

	string path = argv[optind]; // get file path
	table_t table;
	record_t field_names;
	split(path, table);

	if(options & FIELDS)
	{
		record_t field_names = table[0];
		// remove header from table
		table.erase(table.begin());
	}

	int len = table.size();
	for(int i = 0; i < len; ++i)
	{
		record_t record = table[i];
		int record_len = record.size();
		for(int j = 0; j < record_len; ++j)
		{
			field_t field = record[j];
			stringstream ss;
			printfmt(field, fmt::color::green);
			ss << field_names[i] << "[" << i << "][" << j << "]" << " | ";
			cout << ss.str();
		}
		cout << endl;
	}
	return 0;
}
