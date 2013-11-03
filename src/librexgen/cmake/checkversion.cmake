macro(check_version version_required version_available message)
  string(REGEX MATCHALL "[0-9]+" version_components ${version_available})
  list(GET version_components 0 version_available_major)
  list(GET version_components 1 version_available_minor)

  string(REGEX MATCHALL "[0-9]+" version_components ${version_required})
  list(GET version_components 0 version_required_major)
  list(GET version_components 1 version_required_minor)

  if(${version_available_major} LESS ${version_required_major})
    message(FATAL_ERROR ${message})
  endif(${version_available_major} LESS ${version_required_major})

	if(${version_available_major} EQUAL ${version_required_major})
		if(${version_available_minor} LESS ${version_required_minor})
			message(FATAL_ERROR ${message})
		endif(${version_available_minor} LESS ${version_required_minor})
	endif(${version_available_major} EQUAL ${version_required_major})
endmacro(check_version)
