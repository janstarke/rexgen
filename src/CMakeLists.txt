project(rexgen)

set(prj rexgen)

cmake_minimum_required(VERSION 2.8)

set(LUA_VERSION "5.2")

set(librexgen_major 1)
set(librexgen_minor 0)

find_program(svnversion "svnversion")
execute_process( COMMAND svnversion
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	OUTPUT_VARIABLE librexgen_build_tmp 
	OUTPUT_STRIP_TRAILING_WHITESPACE )
string(REPLACE ":" "-" librexgen_build ${librexgen_build_tmp} )
if (${librexgen_build} MATCHES " ")
  set(librexgen_build "DEV")
  set(librexgen_version "${librexgen_major}.${librexgen_minor}.DEV")
else()
  set(librexgen_version "${librexgen_major}.${librexgen_minor}.${librexgen_build}")
endif(${librexgen_build} MATCHES " ")

set(librexgen_libname librexgen-${librexgen_version})
set(librexgen_filename "lib${prj}" )
#set(librexgen_filename "${prj}${CMAKE_SHARED_LIBRARY_SUFFIX}.${librexgen_version}" )

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

if ("${CMAKE_BUILD_TYPE}" EQUAL "Debug")
  MESSAGE(STATUS "USING DEBUG MODE")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DDEBUG")
else()
  MESSAGE(STATUS "COMPILING OPTIMIZED VERSION")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DNDEBUG -O3")
endif("${CMAKE_BUILD_TYPE}" EQUAL "Debug")

SET(BUILD_SHARED_LIBS ON)

ADD_DEFINITIONS("-I${PROJECT_SOURCE_DIR}")

add_subdirectory(librexgen)
add_subdirectory(rexgen)
