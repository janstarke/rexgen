cmake_minimum_required(VERSION 2.8.12)
if(CMAKE_MAJOR_VERSION GREATER 2)
cmake_policy(SET CMP0042 OLD)
endif(CMAKE_MAJOR_VERSION GREATER 2)
project(${librexgen})

find_package(BISON 2.3)
find_package(FLEX 2.5)
include(CheckIncludeFiles)

check_include_files("xlocale.h" HAVE_XLOCALE_H)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_BINARY_DIR}/..")

IF(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
ELSE()
  ADD_DEFINITIONS("-std=c++11 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ENDIF(MSVC)

ADD_DEFINITIONS("-DUNICODE")

FLEX_TARGET(regexscanner parser/regex_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp COMPILE_FLAGS "")
BISON_TARGET(regexparser parser/regex_parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "")

if(MSVC)
	SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp PROPERTIES GENERATED 1)
	SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES GENERATED 1)
else()
  SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp
    PROPERTIES 
		GENERATED 1
    COMPILE_FLAGS "-w")
	SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
		PROPERTIES
		GENERATED 1
    COMPILE_FLAGS "-w")
endif(MSVC)

ADD_FLEX_BISON_DEPENDENCY(regexscanner regexparser)

ADD_CUSTOM_TARGET(parser_target DEPENDS ${BISON_regexparser_OUTPUTS} ${FLEX_regexscanner_OUTPUTS})

set(librexgen_sources
  debug.cpp 
  "${CMAKE_CURRENT_BINARY_DIR}/${librexgen}/version.cpp"
  regex/compoundregex.cpp
  regex/regexalternatives.cpp
  regex/classregex.cpp
  regex/regex.cpp
  regex/terminalregex.cpp
  regex/groupreference.cpp
  regex/streamregex.cpp
  iterator/iteratorpermuter.cpp
  iterator/regexalternativesiterator.cpp
  iterator/compoundregexiterator.cpp
  iterator/groupreferenceiterator.cpp
  iterator/streamregexiterator.cpp
  iterator/caseiterator.cpp
  state/serializablestate.cpp
  string/simplestring.cpp
        parser/rexgenparsercontext.cpp
  librexgen.cpp
  c/librexgen.cpp
  c/iterator.cpp
  c/simplestring.cpp
)
set(parser_sources
  ${BISON_regexparser_OUTPUTS} )
set(CPPCHECK_SUPPRESS ${parser_sources})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Profile")
	add_library(${librexgen} STATIC ${parser_sources} ${librexgen_sources})
else()
	add_library(${librexgen} SHARED ${parser_sources} ${librexgen_sources})
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Profile")

add_dependencies(${librexgen} parser_target )

if(MSVC)
else()
	target_link_libraries(${librexgen} "stdc++")
endif(MSVC)

set_target_properties(${librexgen} PROPERTIES
	PREFIX ""
	SOVERSION "${librexgen_major}.${librexgen_minor}"
	VERSION ${librexgen_version})

set(librexgen_filename "${librexgen}${CMAKE_SHARED_LIBRARY_SUFFIX}")
configure_file( "version/version.cpp" "${CMAKE_CURRENT_BINARY_DIR}/${librexgen}/version.cpp" )
configure_file( "version/version.h" "${CMAKE_CURRENT_BINARY_DIR}/${librexgen}/version.h" )

if(MSVC)
	set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/parser.cpp PROPERTIES COMPILE_FLAGS "/wd4065" )
	set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp PROPERTIES COMPILE_FLAGS "/wd4005" )
endif(MSVC)

add_subdirectory(lua)
add_subdirectory(python)

install(TARGETS ${librexgen}
		RUNTIME DESTINATION "bin"
		LIBRARY DESTINATION "lib"
		ARCHIVE DESTINATION "lib"
		)

SET(INSTALL_INCLUDE_DIR "include/${librexgen}")
file(GLOB librexgen_headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB regex_headers "${CMAKE_CURRENT_SOURCE_DIR}/regex/*.h")
file(GLOB iterator_headers "${CMAKE_CURRENT_SOURCE_DIR}/iterator/*.h")
file(GLOB common_headers "${CMAKE_CURRENT_SOURCE_DIR}/common/*.h")
file(GLOB parser_headers "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.h")
file(GLOB string_headers "${CMAKE_CURRENT_SOURCE_DIR}/string/*.h")
file(GLOB state_headers "${CMAKE_CURRENT_SOURCE_DIR}/state/*.h")
file(GLOB c_headers "${CMAKE_CURRENT_SOURCE_DIR}/c/*.h")
file(GLOB generated_headers "${CMAKE_CURRENT_BINARY_DIR}/librexgen/*.h")
install(FILES ${librexgen_headers} DESTINATION ${INSTALL_INCLUDE_DIR} )
install(FILES ${regex_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/regex )
install(FILES ${iterator_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/iterator )
install(FILES ${common_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/common )
install(FILES ${parser_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/parser )
install(FILES ${string_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/string )
install(FILES ${state_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/state )
install(FILES ${c_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/c )
install(FILES ${generated_headers} DESTINATION ${INSTALL_INCLUDE_DIR} )

INSTALL(CODE "MESSAGE(\"Please run 'ldconfig' upon successful installation of ${prj}\")")

