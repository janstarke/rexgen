project(librexgen)

cmake_minimum_required(VERSION 2.8)

set(librexgen_major 0)
set(librexgen_minor 1)
set(librexgen_release 0)
set(librexgen_version ${librexgen_major}.${librexgen_minor}.${librexgen_release})
set(librexgen_libname rexgen-${librexgen_version})
set(rexgen_exename "${prj}")

find_library(log4cpp liblog4cpp5 libunistring liblua5.2)

SET(BUILD_SHARED_LIBS ON)
ADD_DEFINITIONS("-g -DREXGEN_DEBUG=0 -DYYDEBUG=0 -std=c++0x -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline ")

set(rexgen_sources rexgen.cpp)

add_subdirectory(librexgen)

