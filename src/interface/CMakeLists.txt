cmake_minimum_required(VERSION 3.10)

# set the project name
project(moe-container-manager-interface)
set(CMAKE_C_COMPILER "clang")

# add cxx standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("-Wno-unused-result")
add_compile_options("-O2")
add_compile_options("-std=c++17")

# add the executable
add_executable(interface main.cpp log.cpp)

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
set(CMAKE_EXE_LINKER_FLAGS "-ffunction-sections -fdata-sections -z now -z noexecstack -fPIE -Wall -Wextra -pedantic -fuse-ld=lld")
install (TARGETS interface DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../out)
