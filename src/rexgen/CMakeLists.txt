project(${prj})
set(rexgen_exename rexgen)

set(rexgen_sources rexgen.c)
set(rexgen_manpages rexgen.1)

add_executable(${rexgen_exename} ${rexgen_sources})
target_link_libraries(${rexgen_exename} ${librexgen})

# set compiler flags
if(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
else()
  ADD_DEFINITIONS("--std=c89 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
endif(MSVC)

install(TARGETS ${rexgen_exename} RUNTIME DESTINATION bin)

# install manpage
if(MSVC)
else()
	add_custom_command(
		OUTPUT rexgen.1.gz
		COMMAND gzip "${CMAKE_CURRENT_SOURCE_DIR}/rexgen.1" -c >rexgen.1.gz)
	add_custom_target(man ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/rexgen.1.gz")
	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/rexgen.1.gz" DESTINATION "man/man1")
endif(MSVC)
