#include(cmake/cpplint.cmake)
#include(cmake/cppcheck.cmake)

find_package(BISON 2.3)
find_package(FLEX 2.5)

if(MSVC)
else()
  SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp
    PROPERTIES 
    COMPILE_FLAGS "-Wno-unused-parameter")
endif(MSVC)

IF(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
ELSE()
  ADD_DEFINITIONS("-Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ENDIF(MSVC)

FLEX_TARGET(regexscanner parser/regex_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp COMPILE_FLAGS "")
BISON_TARGET(regexparser parser/regex_parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES GENERATED 1)

ADD_FLEX_BISON_DEPENDENCY(regexscanner regexparser)

ADD_CUSTOM_TARGET(parser_target DEPENDS ${BISON_regexparser_OUTPUTS} ${FLEX_regexscanner_OUTPUTS})

if(USE_LUA)
  set(lua_sources api/lua/librexgen_lua.cpp)
else()
  set(lua_sources "")
endif(USE_LUA)

set(librexgen_sources
  ${lua_sources}
  debug.cpp 
  "${CMAKE_CURRENT_BINARY_DIR}/librexgen/version.cpp"
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
  iterator/streamregexiterator.cpp
  iterator/caseiterator.cpp
  state/serializablestate.cpp
  string/uchar.cpp
	string/simplestring.cpp

  parser/rexgenparsercontext.cpp

	api/cxx/librexgen.cpp
	api/c/librexgen.cpp
)
set(parser_sources
  ${BISON_regexparser_OUTPUTS}
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

add_library(${librexgen_filename} SHARED ${parser_sources} ${librexgen_sources})
add_dependencies(${librexgen_filename} parser_target)

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

configure_file( "version/version.cpp" "${CMAKE_CURRENT_BINARY_DIR}/librexgen/version.cpp" )
configure_file( "version/version.h" "${CMAKE_CURRENT_BINARY_DIR}/librexgen/version.h" )
if(MSVC)
	set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES COMPILE_FLAGS "/wd4065" )
	set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp PROPERTIES COMPILE_FLAGS "/wd4005" )
endif(MSVC)

install(TARGETS ${librexgen_filename}
		RUNTIME DESTINATION "bin"
		LIBRARY DESTINATION "lib"
		ARCHIVE DESTINATION "lib"
		)

SET(INSTALL_INCLUDE_DIR "include/librexgen")
file(GLOB librexgen_headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB regex_headers "${CMAKE_CURRENT_SOURCE_DIR}/regex/*.h")
file(GLOB iterator_headers "${CMAKE_CURRENT_SOURCE_DIR}/iterator/*.h")
file(GLOB parser_headers "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.h")
file(GLOB string_headers "${CMAKE_CURRENT_SOURCE_DIR}/string/*.h")
file(GLOB state_headers "${CMAKE_CURRENT_SOURCE_DIR}/state/*.h")
file(GLOB capi_headers "${CMAKE_CURRENT_SOURCE_DIR}/api/c/*.h")
file(GLOB cxxapi_headers "${CMAKE_CURRENT_SOURCE_DIR}/api/cxx/*.h")
file(GLOB luaapi_headers "${CMAKE_CURRENT_SOURCE_DIR}/api/lua/*.h")
file(GLOB generated_headers "${CMAKE_CURRENT_BINARY_DIR}/librexgen/*.h")
install(FILES ${librexgen_headers} DESTINATION ${INSTALL_INCLUDE_DIR} )
install(FILES ${regex_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/regex )
install(FILES ${iterator_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/iterator )
install(FILES ${parser_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/parser )
install(FILES ${string_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/string )
install(FILES ${state_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/state )
install(FILES ${capi_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/api/c )
install(FILES ${cxxapi_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/api/cxx )
install(FILES ${luaapi_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/api/lua )
install(FILES ${generated_headers} DESTINATION ${INSTALL_INCLUDE_DIR} )

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
