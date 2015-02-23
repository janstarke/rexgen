cmake_minimum_required(VERSION 2.8.12)
if(CMAKE_MAJOR_VERSION GREATER 2)
cmake_policy(SET CMP0042 OLD)
endif(CMAKE_MAJOR_VERSION GREATER 2)

OPTION (USE_PYTHON "create Python module" OFF)

if(USE_PYTHON)
find_library(PYTHONLIBS REQUIRED )
MESSAGE(STATUS "found python ${PYTHONLIBS_VERSION_STRING}" )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(PYTHON_TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/python")

configure_file("${PROJECT_SOURCE_DIR}/python/setup.py" "${PYTHON_TMP_DIR}/setup.py")
configure_file("${PROJECT_SOURCE_DIR}/python/rexgen.py" "${PYTHON_TMP_DIR}/rexgen.py")

install(CODE "execute_process(COMMAND python setup.py install -f --prefix=\"${CMAKE_INSTALL_PREFIX}\" WORKING_DIRECTORY \"${PYTHON_TMP_DIR}\")")

endif(USE_PYTHON)
