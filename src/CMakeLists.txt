set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(prj rexgen)

cmake_minimum_required(VERSION 2.8.12)

include (cmake/packaging.cmake)
include (cmake/testing.cmake)

file(READ ${PROJECT_SOURCE_DIR}/version.txt librexgen_version_line)
string(REPLACE "\n" "" librexgen_version ${librexgen_version_line})
string(REPLACE "." ";" version_list ${librexgen_version})
list(GET version_list 0 librexgen_major)
list(GET version_list 1 librexgen_minor)
list(GET version_list 2 librexgen_release)
set(librexgen "lib${prj}" )
set(librexgen-c "lib${prj}-c")
set(librexgen-lua "lib${prj}-lua")

message("creating ${prj} ${librexgen_version}")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  MESSAGE(STATUS "USING DEBUG MODE")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DDEBUG -g")
else()
  MESSAGE(STATUS "COMPILING OPTIMIZED VERSION: ${CMAKE_BUILD_TYPE}")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DNDEBUG -O3")
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

SET(BUILD_SHARED_LIBS ON)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/librexgen" "/usr/local/include/flex")
if(MSVC)
INCLUDE_DIRECTORIES("D:/Tools/GnuWin32/include")
endif(MSVC)

add_subdirectory(librexgen)
add_subdirectory(rexgen)

#include (cmake/ctags.cmake)
