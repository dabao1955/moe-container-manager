 cmake_minimum_required(VERSION 3.10)

# set the project name
project(ruri VERSION 3.6 LANGUAGES C)

# add cxx standard
add_compile_options("-Wno-unused-result")
add_compile_options("-Wall")
add_compile_options("-pipe")
add_compile_options("-D_FORTIFY_SOURCE=3 -enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang -fstack-protector-all")

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/ruri/src/*.c ${CMAKE_SOURCE_DIR}/ruri/src/easteregg/*.c)

set(RURI_VERSION 3.6)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"  # 源文件路径
  "${CMAKE_CURRENT_SOURCE_DIR}/src/include/version.h"     # 目标文件路径
  @ONLY
)

if (MOE_LIB)
    set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
    add_library(ruri SHARED ${SOURCES})
    install (TARGETS ruri DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../out/lib/)
else ()
# add the executable
    set(CMAKE_POSITION_INDEPENDENT_CODE FALSE)
    add_executable(ruri ${SOURCES})
    add_custom_command(
        TARGET ruri
        POST_BUILD
        COMMAND strip ruri
        VERBATIM
        )
    install (TARGETS ruri DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../out/bin/)
endif()

# on linux clang 14
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_library(LCAP cap)
    find_library(LSECCOMP seccomp)
    target_link_libraries(ruri ${LCAP} ${LSECCOMP})
endif()

add_custom_target(
    tidy ALL
    COMMAND clang-tidy --checks=*,-clang-analyzer-security.insecureAPI.strcpy,-altera-unroll-loops,-cert-err33-c,-concurrency-mt-unsafe,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-readability-function-cognitive-complexity,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-bugprone-easily-swappable-parameters,-cert-err34-c,-misc-include-cleaner,-readability-identifier-length,-bugprone-signal-handler,-cert-msc54-cpp,-cert-sig30-c,-altera-id-dependent-backward-branch,-bugprone-suspicious-realloc-usage,-hicpp-signed-bitwise,-clang-analyzer-security.insecureAPI.UncheckedReturn
    COMMENT "Running tidy"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ruri/src/ # Set correct path where main.go is located
)

# add cxx flags
set(CMAKE_EXE_LINKER_FLAGS "-ffunction-sections -fdata-sections -z noexecstack -fPIE -Wall -flto -fstack-protector-all -fstack-clash-protection -ffunction-sections -fdata-sections -Wl,--gc-sections")
