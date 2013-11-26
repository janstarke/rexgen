#include(cmake/cpplint.cmake)
#include(cmake/cppcheck.cmake)

find_package(BISON)
set(bison_required_version 2.5)
IF(${BISON_VERSION} VERSION_LESS ${bison_required_version})
  MESSAGE(FATAL_ERROR "${librexgen_libname} requires at least bison ${bison_required_version}")
ENDIF (${BISON_VERSION} VERSION_LESS ${bison_required_version})

find_package(FLEX)
set(flex_required_version 2.5)
IF(${FLEX_VERSION} VERSION_LESS ${flex_required_version}) 
  MESSAGE(FATAL_ERROR "${librexgen_libname} requires at least flex ${flex_required_version}")
ENDIF(${FLEX_VERSION} VERSION_LESS ${flex_required_version})

if(MSVC)
else()
  SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
    PROPERTIES 
    COMPILE_FLAGS "-Wno-unused-parameter")
endif(MSVC)

IF(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
ELSE()
  ADD_DEFINITIONS("--std=c++0x -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ENDIF(MSVC)

BISON_TARGET(regexparser parser/regex_parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "")
FLEX_TARGET(regexlexer parser/regex_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp PROPERTIES GENERATED 1)

ADD_FLEX_BISON_DEPENDENCY(regexlexer regexparser)

if(USE_LUA)
  set(lua_sources api/lua/librexgen_lua.cpp)
else()
  set(lua_sources "")
endif(USE_LUA)

set(librexgen_sources
  ${lua_sources}
  debug.cpp 
  "${CMAKE_CURRENT_BINARY_DIR}/version_cmake.cpp"
  regex/compoundregex.cpp
  regex/regexalternatives.cpp
  regex/classregex.cpp
  regex/regex.cpp
  regex/terminalregex.cpp
  regex/groupreference.cpp
  iterator/iterator.cpp
  iterator/iteratorpermuter.cpp
  iterator/regexalternativesiterator.cpp
  iterator/compoundregexiterator.cpp
  iterator/groupreferenceiterator.cpp
  iterator/classregexiterator.cpp
  unicode/uchar.cpp

	simplestring.cpp

  parser/rexgenparsercontext.cpp

	api/cxx/librexgen.cpp
	api/c/librexgen.cpp
)
set(parser_sources
  ${BISON_regexparser_OUTPUTS}
  ${FLEX_regexlexer_OUTPUTS}
)
set(CPPCHECK_SUPPRESS ${parser_sources})

if(COMMAND add_cpplint)
 add_cpplint(${librexgen_filename} ${librexgen_sources})
 add_dependencies(${librexgen_filename} ${librexgen_libname}_CPPLINT)
endif(COMMAND add_cpplint)

if(COMMAND add_cppcheck)
 add_cppcheck(${librexgen_filename} ${librexgen_sources} ${parser_sources})
 add_dependencies(${librexgen_filename} ${librexgen_libname}_CPPCHECK)
endif(COMMAND add_cppcheck)

add_library(${librexgen_filename} SHARED ${librexgen_sources} ${parser_sources})

if (USE_LUA)
  target_link_libraries(${librexgen_filename} "lua${LUA_VERSION}" )
endif(USE_LUA)

if(MSVC)
else()
	target_link_libraries(${librexgen_filename} "stdc++")
endif(MSVC)

set_target_properties(${librexgen_filename} PROPERTIES
	PREFIX ""
	SOVERSION "${librexgen_major}.${librexgen_minor}"
	VERSION ${librexgen_version})

configure_file( "version.cpp" "${CMAKE_CURRENT_BINARY_DIR}/version_cmake.cpp" )
if(MSVC)
	set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES COMPILE_FLAGS "/wd4065" )
	set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp PROPERTIES COMPILE_FLAGS "/wd4005" )
endif(MSVC)

install(TARGETS ${librexgen_filename}
		RUNTIME DESTINATION "bin"
		LIBRARY DESTINATION "lib"
		ARCHIVE DESTINATION "lib"
		)

file(GLOB librexgen_headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${librexgen_headers} DESTINATION include/librexgen )
file(GLOB regex_headers "${CMAKE_CURRENT_SOURCE_DIR}/regex/*.h")
install(FILES ${regex_headers} DESTINATION include/librexgen/regex )
file(GLOB iterator_headers "${CMAKE_CURRENT_SOURCE_DIR}/iterator/*.h")
install(FILES ${iterator_headers} DESTINATION include/librexgen/iterator )
file(GLOB parser_headers "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.h")
install(FILES ${parser_headers} DESTINATION include/librexgen/parser )
file(GLOB unicode_headers "${CMAKE_CURRENT_SOURCE_DIR}/unicode/*.h")
install(FILES ${unicode_headers} DESTINATION include/librexgen/unicode )

if (USE_LUA)
  if (MSVC)
    set(LUA_BINARY "$ENV{LUA_DEV}\\lua.exe")
  else()
    execute_process(COMMAND "/usr/bin/which" "lua${LUA_VERSION}"
                    ERROR_VARIABLE LUA_ERROR
                    OUTPUT_VARIABLE LUA_BINARY)
  endif(MSVC)
  MESSAGE(STATUS "LUA_BINARY = ${LUA_BINARY}")
  if(DEFINED ${LUA_ERROR})
    MESSAGE(FATAL_ERROR "lua${LUA_VERSION} is missing")
  else()
    configure_file("${PROJECT_SOURCE_DIR}/rexgen_lua/rexgen_tmpl.lua" "${PROJECT_SOURCE_DIR}/rexgen_lua/rexgen.lua")
    install(PROGRAMS "${PROJECT_SOURCE_DIR}/rexgen_lua/rexgen.lua" DESTINATION bin)
  endif(DEFINED ${LUA_ERROR})
endif(USE_LUA)
