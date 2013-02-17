include(cmake/cpplint.cmake)
include(cmake/cppcheck.cmake)

find_package(BISON)
find_package(FLEX)
ADD_DEFINITIONS("-fPIC -DREXGEN_DEBUG=0 -O2 -std=c++0x -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline ")
ADD_DEFINITIONS("-I${CMAKE_CURRENT_BINARY_DIR}/../../")
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
  PROPERTIES 
  COMPILE_FLAGS "-Wno-unused-parameter")

BISON_TARGET(regexparser parser/regex_parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "")
FLEX_TARGET(regexlexer parser/regex_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp PROPERTIES GENERATED 1)

ADD_FLEX_BISON_DEPENDENCY(regexlexer regexparser)

set(librexgen_sources
  librexgen.cpp
  librexgen_lua.cpp
  debug.cpp 

  regex/compoundregex.cpp
  regex/regexalternatives.cpp
  regex/classregex.cpp
  regex/regex.cpp
  regex/terminalregex.cpp
  regex/groupreference.cpp
  iterator/classregexiterator.cpp
  iterator/terminalregexiterator.cpp
  iterator/regexalternativesiterator.cpp
  iterator/compoundregexiterator.cpp
  iterator/groupreferenceiterator.cpp

  parser/rexgenparsercontext.cpp
)
set(parser_sources
  ${BISON_regexparser_OUTPUTS}
  ${FLEX_regexlexer_OUTPUTS}
)
set(CPPCHECK_SUPPRESS ${parser_sources})

if(COMMAND add_cpplint)
 add_cpplint(${librexgen_libname} ${librexgen_sources})
endif(COMMAND add_cpplint)

if(COMMAND add_cppcheck)
 add_cppcheck(${librexgen_libname} ${librexgen_sources} ${parser_sources})
endif(COMMAND add_cppcheck)

add_library(${librexgen_libname} SHARED ${librexgen_sources} ${parser_sources})
add_dependencies(${librexgen_libname} ${librexgen_libname}_CPPLINT)
add_dependencies(${librexgen_libname} ${librexgen_libname}_CPPCHECK)
target_link_libraries(${librexgen_libname} 
  log4cpp unistring lua5.2)
set_target_properties(${librexgen_libname} PROPERTIES PREFIX "lib")