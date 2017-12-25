project(${prj})

cmake_minimum_required(VERSION 3.9.1)
set(testrexgen_exename tests)
set(CMAKE_MACOSX_RPATH 1)
include(CodeCoverage.cmake)
APPEND_COVERAGE_COMPILER_FLAGS()
include(GoogleTest)
add_subdirectory("${PROJECT_SOURCE_DIR}/googletest")
add_subdirectory("pcre")

check_include_files("xlocale.h" HAVE_XLOCALE_H)
if(HAVE_XLOCALE_H)
	ADD_DEFINITIONS("-DHAVE_XLOCALE_H")
endif(HAVE_XLOCALE_H)

file(GLOB_RECURSE testrexgen_sources "testcases/test*.cpp")

add_executable(${testrexgen_exename} "main.cpp" ${testrexgen_sources} utils.cpp)

GTEST_ADD_TESTS(${testrexgen_exename} "" ${testrexgen_sources})

target_link_libraries(${testrexgen_exename} ${librexgen})
set (GTEST_FOUND 1)
set (GTEST_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/googletest/googletest/include")
set (GTEST_LIBRARIES "libgtestd")
set (GTEST_MAIN_LIBRARIES "gtest_maind")
set (GTEST_BOTH_LIBRARIES "${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES}")
set (BUILD_GTEST ON CACHE BOOL "Builds the googletest subproject" FORCE )
include_directories(${GTEST_INCLUDE_DIRS})

include_directories("${PROJECT_SOURCE_DIR}/pcre")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/pcre")
include_directories("${PROJECT_SOURCE_DIR}")

target_link_libraries(${testrexgen_exename} "gtest")
target_link_libraries(${testrexgen_exename} "gtest_main")
target_link_libraries(${testrexgen_exename} "pcrecpp")

# set compiler flags
if(MSVC)
	ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
else()
	ADD_DEFINITIONS("-std=c++11 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
endif(MSVC)
