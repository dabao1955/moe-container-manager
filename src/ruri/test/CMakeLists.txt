cmake_minimum_required(VERSION 3.10)

project(ruri_test LANGUAGES CXX)

add_executable(ruri_test main.cpp)

enable_testing()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

set_tests_properties(${PROJECT_NAME} PROPERTIES
    PASS_REGULAR_EXPRESSION ".*"
)
