cmake_minimum_required(VERSION 3.10)

# set the project name
project(moe-container-manager-interface LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_BUILD_TYPE Debug)

# add cxx standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("-Wno-unused-result")
add_compile_options("-std=c++17")
add_compile_options("-Wextra")
add_compile_options("-Wpedantic")
add_compile_options("-pedantic")
add_compile_options("-Wall")
add_compile_options("-pipe")

include_directories(${CMAKE_SOURCE_DIR}/include)

# add the executable
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(interface ${SOURCES})

# on linux clang 14
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(fmt REQUIRED)
    target_link_libraries(interface PRIVATE fmt::fmt)
endif()

# Configure CCache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# add cxx flags
install (TARGETS interface DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../out)
