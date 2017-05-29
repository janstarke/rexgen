cmake_minimum_required(VERSION 2.8.12)
if(CMAKE_MAJOR_VERSION GREATER 2)
cmake_policy(SET CMP0042 OLD)
endif(CMAKE_MAJOR_VERSION GREATER 2)

OPTION (USE_LUA "create API for lua" OFF)

if(USE_LUA)
find_package(lua REQUIRED )
MESSAGE(STATUS "found lua '${LUA_VERSION_STRING}': '${LUA_LIBRARIES}'" )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(LUA_TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/lua")

IF(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
ELSE()
  ADD_DEFINITIONS("-std=c++11 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ENDIF(MSVC)
include_directories(${LUA_INCLUDE_DIR})

set(lua-sources librexgen_lua.cpp)
add_library(${librexgen_lua} SHARED ${lua-sources})
target_link_libraries(${librexgen_lua} ${librexgen} "${LUA_LIBRARIES}" )

if(MSVC)
else()
	target_link_libraries(${librexgen_lua} "stdc++")
endif(MSVC)

set_target_properties(${librexgen_lua} PROPERTIES
	PREFIX ""
	SOVERSION "${librexgen_major}.${librexgen_minor}"
	VERSION ${librexgen_version})

install(TARGETS ${librexgen_lua}
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
configure_file("${PROJECT_SOURCE_DIR}/lua/rexgen.lua" "${LUA_TMP_DIR}/rexgen.lua")
install(PROGRAMS "${LUA_TMP_DIR}/rexgen.lua" DESTINATION bin)

endif(USE_LUA)
