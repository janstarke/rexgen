enable_testing()

file(GLOB_RECURSE code_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h" ".c" "*.cpp")

foreach(code_file ${code_files})
  add_test( NAME "cpplint:${code_file}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND python "${PROJECT_SOURCE_DIR}/cmake/cpplint.py" "--filter=-build/header_guard" ${code_file})
endforeach()