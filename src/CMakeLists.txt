project(rexgen)

set(prj rexgen)

cmake_minimum_required(VERSION 2.8)
if(MSVC)
	set(CPACK_GENERATOR "ZIP")
elseif(APPLE)
	set(CPACK_GENERATOR "TGZ")
else()
	set(CPACK_GENERATOR "DEB;RPM")
endif(MSVC)

set(LUA_VERSION "5.2")

set(librexgen_major 1)
set(librexgen_minor 1)

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

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "rexgen - a tool to create words based on regular expressions")
SET(CPACK_PACKAGE_VENDOR "Jan Starke <rexgen@outofbed.org>")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_VENDOR})
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/gpl.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR ${librexgen_major})
SET(CPACK_PACKAGE_VERSION_MINOR ${librexgen_minor})
SET(CPACK_PACKAGE_VERSION_PATCH ${librexgen_build})
SET(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../bin/${CMAKE_SYSTEM_NAME}")
SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/build/" ".*\\\\.sh")
SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
include(CPack)

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

add_subdirectory(librexgen)
add_subdirectory(rexgen)
