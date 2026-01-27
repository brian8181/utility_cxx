#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unistd.h>         /* for STDIN_FILENO */
#include <sys/select.h>     /* for pselect   */
#include <string>
#include <getopt.h>
#include "bash_color.hpp"
#include "fileio.hpp"

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

int main(int argc, char* argv[]);

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
			<< FMT_BOLD	<< FMT_FG_GREEN << "Usage: "			<< FMT_RESET << endl
			<< FMT_BOLD	<< FMT_FG_BLUE  << "selectfd"			<< FMT_RESET << " "
			<< FMT_FG_BLUE              << "[-hvd:][...]"		<< FMT_RESET << " "
										<< "FILE [FILE2 ... ]"	<< FMT_RESET << " "
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
				exit(0);
			case 'v':
				print_version();
				exit(0);
			case 'f':
				options |= FIELDS;
				break;
			case 'd':
				DELIMITER=optarg[0];
			case '?':
				cout << "Invalid option" << endl;
				print_help();
				exit(1);
		}
	}

	if (argc < DEFAULT_ARGC) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help" << endl;
		return -1;
	}

	std::stringstream ss;
	int argc_ = (argc-optind);
	int offset = optind;
	std::ifstream strms[argc_];

	for(int i = 0; i < argc_; ++i)
		strms[i].open(argv[i+offset], std::ios::out);

	string line;
	while(getline(strms[0], line))
	{
		int len = line.size();
		string::iterator beg = line.begin();
		line.erase(beg + len-1);
		ss << line;

		for(int i = 1; i < argc_; ++i)
		{
			getline(strms[i], line);
			// trim new line
			int len = line.size();
			string::iterator beg = line.begin();
			line.erase(beg + len-1);
			ss << DELIMITER << line;
		}
		ss << endl;
	}

	cout << ss.str();
	return 0;
}

int stdin_ready (int filedes)
{
	fd_set set;
	// declare/initialize zero timeout
	//struct timespec timeout = { .tv_sec = 0 };
	struct timeval timeout = { .tv_sec = 0 };
	// initialize the file descriptor set
	FD_ZERO(&set);
	FD_SET(filedes, &set);
	// check stdin_ready is ready on filedes
	//return pselect(filedes + 1, &set, NULL, NULL, &timeout, NULL);
	return select(filedes + 1, &set, NULL, NULL, &timeout);
}

int main(int argc, char* argv[])
{
	try
	{
		if(stdin_ready(STDIN_FILENO))
		{
			std::string buffer;
			std::cin >> buffer;
			// add piped buffer to end of argv
			char* argvtmp[sizeof(char*) * argc+1];
			memcpy(argvtmp, argv, sizeof(char*) * argc);
			argvtmp[argc] = &buffer[0];
			argv = argvtmp;
			++argc;
		}
		return parse_options(argc, argv);
	}
	catch(std::logic_error& ex)
	{
	 	std::cout << ex.what() << std::endl;
	}
}
