set(rexgen_exename rexgen)

set(rexgen_sources rexgen.cpp)

add_executable(${rexgen_exename} ${rexgen_sources})
if(ENABLE_PROFILE)
  set_target_properties(${rexgen_exename} PROPERTIES LINK_FLAGS "-static")
  target_link_libraries(${rexgen_exename} ${librexgen_slibname} unistring)
else()
  target_link_libraries(${rexgen_exename} ${librexgen_libname})
endif(ENABLE_PROFILE)

install(TARGETS ${rexgen_exename} RUNTIME DESTINATION bin)