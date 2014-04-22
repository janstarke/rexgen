set(librexgen_major 1)
set(librexgen_minor 1)

find_program(svnversion "svnversion")
execute_process( COMMAND svnversion
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	OUTPUT_VARIABLE librexgen_build_tmp 
	OUTPUT_STRIP_TRAILING_WHITESPACE )
string(REPLACE ":" "-" librexgen_build ${librexgen_build_tmp} )
if (${librexgen_build} MATCHES " ")
  set(librexgen_build "DEV")
  set(librexgen_version "${librexgen_major}.${librexgen_minor}.DEV")
else()
  set(librexgen_version "${librexgen_major}.${librexgen_minor}.${librexgen_build}")
endif(${librexgen_build} MATCHES " ")

set(librexgen_libname librexgen-${librexgen_version})
set(librexgen_filename "lib${prj}" )