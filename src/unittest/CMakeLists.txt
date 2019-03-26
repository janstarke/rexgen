project(unittest)

cmake_minimum_required(VERSION 3.9.3)
set(testrexgen_exename unittest)
set(CMAKE_MACOSX_RPATH 1)
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

add_executable(${testrexgen_exename} "main.cpp" ${testrexgen_sources} utils.cpp)

target_link_libraries(${testrexgen_exename} ${librexgen})
target_link_libraries(${testrexgen_exename} Boost::regex)

# set compiler flags
if(MSVC)
	ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
else()
	ADD_DEFINITIONS("-std=c++11 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
endif(MSVC)

include(CTest)
include(catch2/Catch.cmake)
catch_discover_tests(${testrexgen_exename})