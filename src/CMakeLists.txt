cmake_minimum_required(VERSION 3.0)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(prj rexgen)
file (STRINGS "version.txt" REXGEN_VERSION)
project(rexgen_root VERSION ${REXGEN_VERSION})

include (cmake/packaging.cmake)
include (cmake/doxygen.cmake)
include (cmake/fuzzing.cmake)

string(TOUPPER "${CMAKE_BUILD_TYPE}" uppercase_CMAKE_BUILD_TYPE)

file(READ ${PROJECT_SOURCE_DIR}/version.txt librexgen_version_line)
string(REPLACE "\n" "" librexgen_version ${librexgen_version_line})
string(REPLACE "." ";" version_list ${librexgen_version})
list(GET version_list 0 librexgen_major)
list(GET version_list 1 librexgen_minor)
list(GET version_list 2 librexgen_release)
set(librexgen "lib${prj}" )
set(librexgen_c "lib${prj}-c")
set(librexgen_lua "lib${prj}-lua")

message("creating ${prj} ${librexgen_version}")

ADD_DEFINITIONS("-funsigned-char")
ADD_DEFINITIONS("-D_GNU_SOURCE")

if (uppercase_CMAKE_BUILD_TYPE MATCHES DEBUG)
  enable_debug()
  enable_coverage()
  if(TEST_ENABLED)
    enable_fuzzing()
  endif()
elseif(uppercase_CMAKE_BUILD_TYPE MATCHES PROFILE)
  MESSAGE(STATUS "USING PROFILE MODE")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0" "-DREXGEN_PROFILE=1" "-g" "-pg" )
  SET(CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS_PROFILE} -pg")
  SET(CMAKE_SHARED_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_PROFILE} -pg")
else()
  MESSAGE(STATUS "COMPILING OPTIMIZED VERSION: ${CMAKE_BUILD_TYPE}")
  ADD_DEFINITIONS("-DREXGEN_DEBUG=0 -DNDEBUG -O3")
endif()

if("${CYGWIN}")
  ADD_DEFINITIONS("-D_GNU_SOURCE")
endif("${CYGWIN}")

SET(CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS_PROFILE} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_PROFILE} -pg")

SET(BUILD_SHARED_LIBS ON)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/librexgen" "/usr/local/include/flex")
if(MSVC)
INCLUDE_DIRECTORIES("D:/Tools/GnuWin32/include")
endif(MSVC)

if(TEST_ENABLED)
  enable_testing()
  add_subdirectory(unittest)
endif()

add_subdirectory(librexgen)
add_subdirectory(rexgen)

#include (cmake/ctags.cmake)
