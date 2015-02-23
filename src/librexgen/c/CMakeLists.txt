cmake_minimum_required(VERSION 2.8.12)
if(CMAKE_MAJOR_VERSION GREATER 2)
cmake_policy(SET CMP0042 OLD)
endif(CMAKE_MAJOR_VERSION GREATER 2)

project(${librexgen-c})

OPTION (USE_C "create API for C" ON)

if(USE_C)

IF(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
ELSE()
	ADD_DEFINITIONS("-std=c++11 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
ENDIF(MSVC)

set(c_sources librexgen.cpp iterator.cpp)
add_library(${librexgen-c} SHARED ${c_sources})
target_link_libraries(${librexgen-c} ${librexgen} )

if(MSVC)
else()
	target_link_libraries(${librexgen-c} "stdc++")
endif(MSVC)

set_target_properties(${librexgen-c} PROPERTIES
	PREFIX ""
	SOVERSION "${librexgen_major}.${librexgen_minor}"
	VERSION ${librexgen_version})

install(TARGETS ${librexgen-c}
		RUNTIME DESTINATION "bin"
		LIBRARY DESTINATION "lib"
		ARCHIVE DESTINATION "lib"
		)

SET(INSTALL_INCLUDE_DIR "include/${librexgen}")
file(GLOB capi_headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${capi_headers} DESTINATION ${INSTALL_INCLUDE_DIR}/c )

endif(USE_C)
