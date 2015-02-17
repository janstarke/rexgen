message(STATUS "running: /bin/sh ${PROJECT_SOURCE_DIR}/test/test.sh ${TEST_PROG} '${REGEX}'")
execute_process(COMMAND "/bin/sh" "${PROJECT_SOURCE_DIR}/test/test.sh" ${TEST_PROG} ${REGEX}
                RESULT_VARIABLE HAD_ERROR
                OUTPUT_VARIABLE REXGEN_OUT )
if(HAD_ERROR)
    message(FATAL_ERROR "Test failed")
endif()

STRING(COMPARE NOTEQUAL "${REXGEN_OUT}" "${COUNT}" DIFFERENT)

if(${DIFFERENT})
	message(FATAL_ERROR "Test failed - some results are missing (${REXGEN_OUT} != ${COUNT}")
endif()
