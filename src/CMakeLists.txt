project(librexgen)
set(prj rexgen)

cmake_minimum_required(VERSION 2.8)

set(librexgen_major 0)
set(librexgen_minor 1)
set(librexgen_release 0)
set(librexgen_version ${librexgen_major}.${librexgen_minor}.${librexgen_release})
set(librexgen_libname rexgen-${librexgen_version})
set(librexgen_slibname "rexgen-${librexgen_version}s")

set(rexgen_exename "${prj}")

OPTION (USE_LUA "create API for lua" ON)
OPTION (ENABLE_PROFILE "enable profiling" OFF)

if (USE_LUA)
  find_library(log4cpp libunistring liblua5.2)
else()
  find_library(log4cpp libunistring)
endif(USE_LUA)

SET(BUILD_SHARED_LIBS ON)

ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DNDEBUG")
ADD_DEFINITIONS("-fPIC -std=c++0x -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ADD_DEFINITIONS("-I${PROJECT_SOURCE_DIR}")

if(ENABLE_PROFILE)
  ADD_DEFINITIONS("-g -pg")
endif(ENABLE_PROFILE)

add_subdirectory(librexgen)
add_subdirectory(rexgen)