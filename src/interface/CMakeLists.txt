cmake_minimum_required(VERSION 3.10)

# set the project name
project(moe-container-manager-interface LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_COMPILER "g++")

# add cxx standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("-Wno-unused-result")
add_compile_options("-O2")
add_compile_options("-std=c++17")
add_compile_options("-pipe")
add_compile_options("-D_FORTIFY_SOURCE=3 -enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang -fstack-protector-all")

option(DUBUG_MODE)

if (DEFINED DUBUG_MODE)
    message(WARNING "Warning: debug mode is enabled.")
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_options("-Wpedantic")
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

# add the executable
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)
add_executable(interface ${SOURCES})

#add strip step after building
add_custom_command(
    TARGET interface
    POST_BUILD
    COMMAND strip interface
    VERBATIM
    )

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
set(CMAKE_EXE_LINKER_FLAGS "-ffunction-sections -fdata-sections -z now -z noexecstack -fPIE -Wall -Wextra -pedantic -flto")
install (TARGETS interface DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../out)
