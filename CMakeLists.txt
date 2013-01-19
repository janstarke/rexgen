project(librexgen)

cmake_minimum_required(VERSION 2.8)

set(librexgen_major 0)
set(librexgen_minor 1)
set(librexgen_release 0)
set(librexgen_version ${librexgen_major}.${librexgen_minor}.${librexgen_release})
set(librexgen_libname rexgen-${librexgen_version})
set(rexgen_exename "rexgen")

find_package(BISON)
find_package(FLEX)

find_library(log4cpp liblog4cpp5 libunistring)

BISON_TARGET(regexparser regex_parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "--debug --verbose")
FLEX_TARGET(regexlexer regex_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS "-d")

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp PROPERTIES GENERATED 1)

ADD_FLEX_BISON_DEPENDENCY(regexlexer regexparser)

SET(BUILD_SHARED_LIBS ON)
ADD_DEFINITIONS("-g -DREXGEN_DEBUG=0 -DYYDEBUG=1 -std=c++0x -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline ")
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
  PROPERTIES 
  COMPILE_FLAGS "-Wno-unused-parameter")

set(librexgen_sources iteratorpermuter.cpp classregexiterator.cpp terminalregexiterator.cpp
  regexalternativesiterator.cpp
  librexgen.cpp
  rexgenparsercontext.cpp
  compoundregex.cpp
  compoundregexiterator.cpp
  regexalternatives.cpp
  classregex.cpp
  Regex.cpp
  TerminalRegex.cpp 
  debug.cpp
  ${BISON_regexparser_OUTPUTS}
  ${FLEX_regexlexer_OUTPUTS})

set(rexgen_sources rexgen.cpp)

add_library(${librexgen_libname} SHARED ${librexgen_sources})
target_link_libraries(${librexgen_libname} log4cpp unistring)
set_target_properties(${librexgen_libname} PROPERTIES PREFIX "lib")
add_executable(${rexgen_exename} ${rexgen_sources})
target_link_libraries(${rexgen_exename} ${librexgen_libname} log4cpp unistring)
