set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project(rexgen)
set(prj rexgen)

cmake_minimum_required(VERSION 2.8.12)
set(LUA_VERSION "5.2")

include (cmake/packaging.cmake)
include (cmake/testing.cmake)

file(READ ${PROJECT_SOURCE_DIR}/version.txt librexgen_version_line)
string(REPLACE "\n" "" librexgen_version ${librexgen_version_line})
string(REPLACE "." ";" version_list ${librexgen_version})
list(GET version_list 0 librexgen_major)
list(GET version_list 1 librexgen_minor)
set(librexgen_libname librexgen-${librexgen_version})
set(librexgen_filename "lib${prj}" )

message("creating ${prj} ${librexgen_version}")

if(MSVC) 
#this is currently not supported
  OPTION (USE_LUA "create API for lua" OFF)
else()
  OPTION (USE_LUA "create API for lua" OFF)
endif(MSVC)

find_library(LIB_LOG4CPP log4cpp)
if (USE_LUA)
  find_library(LIB_LUA liblua${LUA_VERSION} )
  if ("${LIB_LUA}" STREQUAL "LIB_LUA-NOTFOUND")
    MESSAGE(FATAL_ERROR "lua${LUA_VERSION} is missing")
  endif("${LIB_LUA}" STREQUAL "LIB_LUA-NOTFOUND")
  MESSAGE(STATUS "using ${LIB_LUA}" )
endif(USE_LUA)

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

add_subdirectory(rexgen)
add_subdirectory(librexgen)

include (cmake/ctags.cmake)
