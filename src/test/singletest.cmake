message(STATUS "running: ${TEST_PROG} '${REGEX}'")
execute_process(COMMAND ${TEST_PROG} ${REGEX}
                RESULT_VARIABLE HAD_ERROR
                OUTPUT_VARIABLE REXGEN_OUT )
if(HAD_ERROR)
    message(FATAL_ERROR "Test failed")
endif()

STRING(MD5 REXGEN_HASH ${REXGEN_OUT})
STRING(COMPARE NOTEQUAL "${REXGEN_HASH}" "${HASH}" DIFFERENT)

if(${DIFFERENT})
    message(FATAL_ERROR "Test failed - files differ")
endif()
