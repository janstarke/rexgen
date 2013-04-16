#include(cmake/cpplint.cmake)
#include(cmake/cppcheck.cmake)
include(cmake/checkversion.cmake)

find_package(BISON)
set(bison_required_version 2.5)
check_version(${bison_required_version} ${BISON_VERSION}
  "${librexgen_libname} requires at least bison ${bison_required_version}")

find_package(FLEX)
set(flex_required_version 2.5)
check_version(${flex_required_version} ${FLEX_VERSION}
  "${librexgen_libname} requires at least flex ${flex_required_version}")

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
  PROPERTIES 
  COMPILE_FLAGS "-Wno-unused-parameter")

BISON_TARGET(regexparser parser/regex_parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "")
FLEX_TARGET(regexlexer parser/regex_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp PROPERTIES GENERATED 1)

ADD_FLEX_BISON_DEPENDENCY(regexlexer regexparser)

if(USE_LUA)
  set(lua_sources librexgen_lua.cpp)
else()
  set(lua_sources "")
endif(USE_LUA)

set(librexgen_sources
  librexgen.cpp
  ${lua_sources}
  debug.cpp 

  regex/compoundregex.cpp
  regex/regexalternatives.cpp
  regex/classregex.cpp
  regex/regex.cpp
  regex/terminalregex.cpp
  regex/groupreference.cpp
  iterator/iteratorpermuter.cpp
  iterator/regexalternativesiterator.cpp
  iterator/compoundregexiterator.cpp
  iterator/groupreferenceiterator.cpp
  iterator/classregexiterator.cpp
  unicode/uchar.cpp

  parser/rexgenparsercontext.cpp
)
set(parser_sources
  ${BISON_regexparser_OUTPUTS}
  ${FLEX_regexlexer_OUTPUTS}
)
set(CPPCHECK_SUPPRESS ${parser_sources})

if(COMMAND add_cpplint)
 add_cpplint(${librexgen_libname} ${librexgen_sources})
 add_dependencies(${librexgen_libname} ${librexgen_libname}_CPPLINT)
endif(COMMAND add_cpplint)

if(COMMAND add_cppcheck)
 add_cppcheck(${librexgen_libname} ${librexgen_sources} ${parser_sources})
 add_dependencies(${librexgen_libname} ${librexgen_libname}_CPPCHECK)
endif(COMMAND add_cppcheck)

#add_library(${librexgen_libname} SHARED ${librexgen_sources} ${parser_sources})
add_library(${librexgen_slibname} STATIC ${librexgen_sources} ${parser_sources})

#if (USE_LUA)
#  target_link_libraries(${librexgen_libname} unistring lua5.2)
#else()
#  target_link_libraries(${librexgen_libname} unistring)
#endif(USE_LUA)

#set_target_properties(${librexgen_libname} PROPERTIES PREFIX "lib")
set_target_properties(${librexgen_slibname} PROPERTIES PREFIX "lib")
set_target_properties(${librexgen_slibname} PROPERTIES LINK_FLAGS "-static")
if(ENABLE_PROFILE)
  set_target_properties(${librexgen_slibname} PROPERTIES LINK_FLAGS "-pg -static")
endif(ENABLE_PROFILE)

#install(TARGETS ${librexgen_libname} LIBRARY DESTINATION lib)
install(TARGETS ${librexgen_slibname} ARCHIVE DESTINATION lib)

if (USE_LUA)
  configure_file("${PROJECT_SOURCE_DIR}/rexgen_lua/rexgen_tmpl.lua" "${PROJECT_SOURCE_DIR}/rexgen_lua/rexgen.lua")
  install(PROGRAMS "${PROJECT_SOURCE_DIR}/rexgen_lua/rexgen.lua" DESTINATION bin)
endif(USE_LUA)