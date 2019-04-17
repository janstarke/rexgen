project(unittest)

cmake_minimum_required(VERSION 3.9.3)
set(testrexgen_exename unittest)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_STANDARD "17")
enable_testing()

find_package(Boost REQUIRED COMPONENTS regex)
include_directories("${PROJECT_SOURCE_DIR}")
include_directories(${Boost_INCLUDE_DIRS})

include(CheckIncludeFiles)
check_include_files("xlocale.h" HAVE_XLOCALE_H)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(HAVE_XLOCALE_H 1)
	add_definitions("-DHAVE_XLOCALE_H=1")
endif()

file(GLOB_RECURSE testrexgen_sources "testcases/test*.cpp")
set(unittest_sources "main.cpp" ${testrexgen_sources} utils.cpp FuzzerGenerator.cpp)

add_executable(${testrexgen_exename} ${unittest_sources})
target_link_libraries(${testrexgen_exename} ${librexgen} Boost::regex)
target_enable_coverage(${testrexgen_exename} ${unittest_sources})
target_enable_fuzzing(${testrexgen_exename} ${unittest_sources})

# set compiler flags
if(MSVC)
	ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
else()
	ADD_DEFINITIONS("-std=c++17 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
endif(MSVC)

include(CTest)
include(catch2/Catch.cmake)
catch_discover_tests(${testrexgen_exename})