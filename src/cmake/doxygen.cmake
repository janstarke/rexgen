# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../docs/Doxyfile.in")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
  endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../docs/Doxyfile.in")
endif(DOXYGEN_FOUND)
