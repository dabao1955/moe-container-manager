cmake_minimum_required(VERSION 3.10)

project(ruri_test LANGUAGES CXX)

add_executable(ruri_test main.cpp)

enable_testing()

add_test(NAME ${PROJECT_NAME} COMMAND sudo bash test-root.sh)

set(CTEST_OUTPUT_ON_FAILURE ON)
set_tests_properties(${PROJECT_NAME} PROPERTIES
    PASS_REGULAR_EXPRESSION ".*"
    ENVIRONMENT "CTEST_OUTPUT_ON_FAILURE=1"
)
