enable_testing()

file(GLOB_RECURSE code_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h" ".c" "*.cpp")

#foreach(code_file ${code_files})
#  add_test( NAME "cpplint:${code_file}"
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#            COMMAND python "${PROJECT_SOURCE_DIR}/cmake/cpplint.py" "--filter=-build/header_guard" ${code_file})
#endforeach()

# idea from http://www.cmake.org/pipermail/cmake/2007-May/014222.html
FILE(READ "${PROJECT_SOURCE_DIR}/test/testcases.txt" testcases)
STRING(REGEX REPLACE ";" "\\\\;" testcases "${testcases}")
STRING(REGEX REPLACE "\n" ";" testcases "${testcases}")

if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --output-on-failure 
        --build-config "$<CONFIGURATION>")
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --output-on-failure)
endif()

foreach(testcase ${testcases})
  STRING(REGEX REPLACE "^([^:]+):(.+):([0-9]+)\$" "\\1" test_name  ${testcase})
  STRING(REGEX REPLACE "^([^:]+):(.+):([0-9]+)\$" "\\2" test_regex ${testcase})
  STRING(REGEX REPLACE "^([^:]+):(.+):([0-9]+)\$" "\\3" test_count ${testcase})

  add_test( NAME "${test_name}"
            COMMAND ${CMAKE_COMMAND}
						-DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
            -DTEST_PROG=$<TARGET_FILE:rexgen>
            -DREGEX='${test_regex}'
						-DCOUNT=${test_count}
            -P "${PROJECT_SOURCE_DIR}/test/singletest.cmake" )
  
  # add_test( NAME "valgrind:${test_regex}"
  #            COMMAND 
  
endforeach()
