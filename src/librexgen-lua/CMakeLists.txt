cmake_minimum_required(VERSION 2.8.12)
cmake_policy(SET CMP0042 OLD)

if(MSVC)
#this is currently not supported
  OPTION (USE_LUA "create API for lua" OFF)
else()
  set(LUA_VERSION "5.2")
  find_library(LIB_LUA liblua${LUA_VERSION} )
  if (${LIB_LUA} STREQUAL "LIB_LUA-NOTFOUND")
    OPTION (USE_LUA "create API for lua" OFF)
  else()
    OPTION (USE_LUA "create API for lua" ON)
  endif (${LIB_LUA} STREQUAL "LIB_LUA-NOTFOUND")
endif(MSVC)

if(LIB_LUA)
if ("${LIB_LUA}" STREQUAL "LIB_LUA-NOTFOUND")
	MESSAGE(FATAL_ERROR "lua${LUA_VERSION} is missing")
endif("${LIB_LUA}" STREQUAL "LIB_LUA-NOTFOUND")
MESSAGE(STATUS "using ${LIB_LUA}" )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

IF(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
ELSE()
  ADD_DEFINITIONS("-std=c++11 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ENDIF(MSVC)

set(lua_sources api/lua/librexgen-lua.cpp)
add_library(${librexgen-lua} SHARED ${lua-sources})
target_link_libraries(${librexgen-lua} ${librexgen_filename} "lua${LUA_VERSION}" )

if(MSVC)
else()
	target_link_libraries(${librexgen-lua} "stdc++")
endif(MSVC)

set_target_properties(${librexgen-lua} PROPERTIES
	PREFIX ""
	SOVERSION "${librexgen_major}.${librexgen_minor}"
	VERSION ${librexgen_version})

install(TARGETS ${librexgen-lua}
		RUNTIME DESTINATION "bin"
		LIBRARY DESTINATION "lib"
		ARCHIVE DESTINATION "lib"
		)

SET(INSTALL_INCLUDE_DIR "include/${librexgen}")
file(GLOB luaapi_headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${luaapi_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/lua )

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

endif(LIB_LUA)
