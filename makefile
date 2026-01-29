# @name     utility_cxx
# @file:    makefile
# @date:    Mon Jan 26 14:02:32 CST 2026
# @version: version 0.0.1

# g++ warnings
#-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror -Wundef
#-fsanitize=undefined,address -Wfloat-equal -Wformat-nonliteral
#-Wformat-security -Wformat-y2k -Wformat=2 -Wimport -Winvalid-pch
#-Wlogical-op -Wmissing-declarations -Wmissing-field-initializers
#-Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn
#-Wnested-externs -Wpacked -Wpointer-arith -Wredundant-decls
#-Wstack-protector -Wstrict-null-sentinel -Wswitch-enum -Wwrite-strings

SHELL:=bash

APP=utility_cxx
CXX=g++
CXXFLAGS=-Wall -std=c++20 -fPIC
CXXEXTRA=-Wno-template-body
CXXCPP?=
LDFLAGS?=
LIBS?=

SRC = src
BLD = build
OBJ = build
TST = build

# lib settings
LIBS=-L/usr/lib -L/usr/lib64 -L/usr/local/lib -L/usr/local/lib64
INCLUDES=-I/usr/local/include/cppunit/
LDFLAGS=$(INCLUDES) $(LIBS)

ifndef RELEASE
	CXXFLAGS +=-g -DDEBUG
endif

ifdef CYGWIN
	CXXFLAGS +=-DCYGWIN
	LDFLAGS += -lfmt -lcppunit.dll
else
	LDFLAGS += -lfmt -lcppunit
endif

LIB_SOURCES=$(SRC)/fileio.cpp $(SRC)/utest.cpp $(SRC)/logger.cpp $(SRC)/singleton.cpp $(SRC)/utility.cpp
SOURCES=$(SRC)/$(APP).cpp $(SRC)/main.cpp $(LIB_SOURCES)

all: $(BLD)/utility_cxx $(BLD)/libutility_cxx.so $(BLD)/libutility_cxx.a

$(BLD)/utility_cxx: $(SOURCES)
	 $(CXX) $(CXXFLAGS) $^ -o $@

# $(BLD)/utility_cxx: $(OBJ)/main.o $(OBJ)/utility_cxx.o
# 	 $(CXX) $(CXXFLAGS) $(OBJ)/main.o $(OBJ)/utility_cxx.o -o $(BLD)/utility_cxx

$(BLD)/libutility_cxx.so: $(LIB_SOURCES)
	$(CXX) $(CXXFLAGS) $(CXXEXTRA) --shared $^ -o $@
	-chmod 755 $@

$(BLD)/libutility_cxx.a: $(LIB_SOURCES)
	-ar rvs $@ $^
	-chmod 755 $@

$(OBJ)/utility_cxx.o: $(SRC)/utility_cxx.cpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRA) -c $(SRC)/utility_cxx.cpp -o $(OBJ)/utility_cxx.o

$(BLD)/utility_cxx_test: $(SRC)/utility_cxx_test.cpp $(BLD)/libutility_cxx.a
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

# copy header to build dir
$(BLD)/%.hpp: $(SRC)/%.hpp
	-cp $^ $@

$(OBJ)/%.o: ./$(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: all clean install unintsall rebuild help

rebuild: clean all

install:
	cp ./$(BLD)/utility_cxx ./$(prefix)/bin/utility_cxx
uninstall:
	-rm ./$(prefix)/bin/utility_cxx
clean:
	@ECHO "removing files ..."
	-rm -f $(OBJ)/*
	-rm -f $(BLD)/*

help:
	@echo
	@echo  'Project: utility_cxx : version 0.0.1 : Mon Jan 26 14:02:32 CST 2026 simple "utility_cxx" framework.'
	@echo
	@echo  '    make [-f] [target]'
	@echo
	@echo  '   -Make Targets ...'
	@echo
	@echo  '        * all                         - build all'
	@echo  '        * $(BLD)/utility_cxx:          - re/build utility_cxx'
	@echo  '        * $(BLD)/utility_cxx_utest:    - re/build utility_cxx_utest, unit testing'
	@echo  '        * clean                       - remove most generated files but keep the config'
	@echo
