cmake_minimum_required(VERSION 2.8.12)
cmake_policy(SET CMP0042 OLD)

OPTION (USE_LUA "create API for lua" OFF)

if(USE_LUA)
find_library(LIB_LUA REQUIRED )
MESSAGE(STATUS "using ${LUA_VERSION_STRING}" )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

IF(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
ELSE()
  ADD_DEFINITIONS("-std=c++11 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ENDIF(MSVC)

set(lua-sources librexgen_lua.cpp)
add_library(${librexgen-lua} SHARED ${lua-sources})
target_link_libraries(${librexgen-lua} ${librexgen} "lua${LUA_VERSION}" )

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

endif(USE_LUA)
