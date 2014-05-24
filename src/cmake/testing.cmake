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

foreach(testcase ${testcases})
  STRING(REGEX REPLACE ":([A-Fa-f0-9]+) -\$" "\\1" test_hash ${testcase})
  STRING(REGEX REPLACE "^(.*):[A-Fa-f0-9]+ -\$" "\\1" test_regex ${testcase})
  
  SET(test_name "regex:${test_regex}")
  
  add_test( NAME ${test_name}
            COMMAND ${CMAKE_COMMAND}
            -DTEST_PROG=$<TARGET_FILE:rexgen>
            -DREGEX=${test_regex}
            -DHASH=${test_hash}
            -P "${PROJECT_SOURCE_DIR}/test/runtest.cmake" )
  
  # add_test( NAME "valgrind:${test_regex}"
  #            COMMAND 
  
endforeach()