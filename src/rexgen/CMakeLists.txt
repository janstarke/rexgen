set(rexgen_exename rexgen)

set(rexgen_sources rexgen.cpp)
set(rexgen_manpages rexgen.1)

add_executable(${rexgen_exename} ${rexgen_sources})
target_link_libraries(${rexgen_exename} ${librexgen_libname})

install(TARGETS ${rexgen_exename} RUNTIME DESTINATION bin)

add_custom_command(
	OUTPUT rexgen.1.gz
	COMMAND gzip "${CMAKE_CURRENT_SOURCE_DIR}/rexgen.1" -c >rexgen.1.gz)
add_custom_target(man ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/rexgen.1.gz")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/rexgen.1.gz" DESTINATION "man/man1")
