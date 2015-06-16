message(STATUS "running: /bin/sh ${PROJECT_SOURCE_DIR}/test/test.sh ${TEST_PROG} '${REGEX}' ${COUNT}")
execute_process(COMMAND "/bin/sh" "${PROJECT_SOURCE_DIR}/test/test.sh" ${TEST_PROG} ${REGEX} ${COUNT}
                RESULT_VARIABLE HAD_ERROR
                OUTPUT_VARIABLE REXGEN_OUT )
if(HAD_ERROR)
    message(FATAL_ERROR "Test failed: ${REXGEN_OUT}")
endif()
