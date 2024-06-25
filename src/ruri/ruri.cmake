 cmake_minimum_required(VERSION 3.10)

# set the project name
project(ruri VERSION 3.3 LANGUAGES C)

# add cxx standard
add_compile_options("-Wno-unused-result")
add_compile_options("-O2")
add_compile_options("-D_FORTIFY_SOURCE=3 -enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang -fstack-protector-all")

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/ruri/src/*.c)

set(RURI_VERSION 3.3)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/ruri/config.h.in"  # 源文件路径
  "${CMAKE_CURRENT_SOURCE_DIR}/ruri/src/include/version.h"     # 目标文件路径
  @ONLY
)

# add the executable
add_executable(ruri ${SOURCES})
add_custom_command(
    TARGET ruri
    POST_BUILD
    COMMAND strip ruri
    VERBATIM
    )

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
set(CMAKE_EXE_LINKER_FLAGS "-ffunction-sections -fdata-sections -z noexecstack -fPIE -Wall -Wextra -pedantic -flto -fstack-protector-all -fstack-clash-protection -ffunction-sections -fdata-sections -Wl,--gc-sections")
install (TARGETS ruri DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../out/bin/)
