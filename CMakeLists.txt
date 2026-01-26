
# @name     utility_cxx
# @file:    CMakeLists.txt
# @date:    Mon, 26 Jan 2026 20:02:33 +0000
# @version: 0.0.1

cmake_minimum_required(VERSION 3.28.3)
project(scanner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(BUILD_SHARED_LIBS YES)

if(CMAKE_SYSTEM_NAME STREQUAL "CYGWIN")
    message(STATUS "Building under Cygwin, defining CYGWIN macro")
    add_definitions(-DCYGWIN)
endif()

add_executable(utility_cxx
    src/utility_cxx.cpp
    src/main.cpp
)


add_library(utility_cxx_a STATIC
    src/utility_cxx.cpp

)

#[=[
    # Add Library
    add_library(targetName [STATIC | SHARED | MODULE]
    [EXCLUDE_FROM_ALL]
    source1 [source2 ...]
)
]=]`

#[=[
install(TARGETS MyApp AlgoRuntime AlgoSDK
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
]=]
