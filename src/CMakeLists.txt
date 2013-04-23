project(librexgen)
set(prj rexgen)

cmake_minimum_required(VERSION 2.8)

set(librexgen_major 0)
set(librexgen_minor 1)
set(librexgen_release 0)
set(librexgen_version ${librexgen_major}.${librexgen_minor}.${librexgen_release})
set(librexgen_libname rexgen-${librexgen_version})

set(rexgen_exename "${prj}")

OPTION (USE_LUA "create API for lua" ON)
#OPTION (REXGEN_DEBUG_MODE "debug mode" ON)

if (USE_LUA)
  find_library(log4cpp liblua5.2)
else()
  find_library(log4cpp )
endif(USE_LUA)

if (REXGEN_DEBUG_MODE)
  MESSAGE(STATUS "USING DEBUG MODE")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DDEBUG -g -O0")
else()
  MESSAGE(STATUS "COMPILING OPTIMIZED VERSION")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DNDEBUG -O3")
endif(REXGEN_DEBUG_MODE)

SET(BUILD_SHARED_LIBS ON)

ADD_DEFINITIONS("-O3 --std=c++0x -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ADD_DEFINITIONS("-I${PROJECT_SOURCE_DIR}")

add_subdirectory(librexgen)
add_subdirectory(rexgen)