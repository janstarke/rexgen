cmake_minimum_required(VERSION 3.0)

set(CMAKE_CONFIGURATION_TYPES "DEBUG" "RELEASE" "libFuzzer")

if(TEST_ENABLED)
    enable_testing()
endif()

add_subdirectory("src")