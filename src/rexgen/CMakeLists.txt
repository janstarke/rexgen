set(rexgen_exename rexgen)
set(rexgen_sources rexgen.cpp)
add_executable(${rexgen_exename} ${rexgen_sources})
target_link_libraries(${rexgen_exename} ${librexgen_libname})

install(TARGETS ${rexgen_exename} RUNTIME DESTINATION bin)