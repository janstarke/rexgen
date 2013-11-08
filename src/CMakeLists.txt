project(rexgen)

set(prj rexgen)

cmake_minimum_required(VERSION 2.8)

set(LUA_VERSION "5.2")

set(librexgen_major 1)
set(librexgen_minor 0)
string(REGEX REPLACE "[^0-9]" "" librexgen_release "$Rev$")
set(librexgen_version ${librexgen_major}.${librexgen_minor}.${librexgen_release})
set(librexgen_libname rexgen-${librexgen_version})
set(librexgen_filename ${CMAKE_SHARED_LIBRARY_PREFIX}${librexgen_libname}${CMAKE_SHARED_LIBRARY_SUFFIX} )

set(rexgen_exename "${prj}")

if(MSVC) 
#this is currently not supported
  OPTION (USE_LUA "create API for lua" OFF)
else()
  OPTION (USE_LUA "create API for lua" OFF)
endif(MSVC)
OPTION (REXGEN_DEBUG_MODE "debug mode" ON)

find_library(LIB_LOG4CPP log4cpp)
if (USE_LUA)
  find_library(LIB_LUA liblua${LUA_VERSION} )
  if ("${LIB_LUA}" STREQUAL "LIB_LUA-NOTFOUND")
    MESSAGE(FATAL_ERROR "lua${LUA_VERSION} is missing")
  endif("${LIB_LUA}" STREQUAL "LIB_LUA-NOTFOUND")
  MESSAGE(STATUS "using ${LIB_LUA}" )
endif(USE_LUA)

if (REXGEN_DEBUG_MODE)
  MESSAGE(STATUS "USING DEBUG MODE")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DDEBUG")
  SET(CMAKE_BUILD_TYPE DEBUG)
else()
  MESSAGE(STATUS "COMPILING OPTIMIZED VERSION")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DNDEBUG -O3")
endif(REXGEN_DEBUG_MODE)

SET(BUILD_SHARED_LIBS ON)

ADD_DEFINITIONS("-I${PROJECT_SOURCE_DIR}")

add_subdirectory(librexgen)
add_subdirectory(rexgen)
