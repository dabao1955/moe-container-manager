 cmake_minimum_required(VERSION 3.10)

# set the project name
project(ruri VERSION 3.3 LANGUAGES C)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_BUILD_TYPE Debug)

# add cxx standard
add_compile_options("-Wno-unused-result")
add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-pedantic")
add_compile_options("-Wpedantic")

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

set(RURI_VERSION 3.3)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/include/version.h"
  @ONLY)

# on linux clang 14
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_library(LCAP cap)
    find_library(LSECCOMP seccomp)
    target_link_libraries(ruri ${LCAP} ${LSECCOMP})
endif()

# Configure CCache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# add cxx flags
install (TARGETS ruri DESTINATION /usr/bin/)
