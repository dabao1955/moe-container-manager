cmake_minimum_required(VERSION 3.10)

# set the project name
project(runlib LANGUAGES CXX VERSION 0.0.1)

# add cxx standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("-Wno-unused-result")
add_compile_options("-Wall")
add_compile_options("-fstack-clash-protection")
add_compile_options("-fstack-protector-all")
add_compile_options("-std=c++17")
add_compile_options("-pipe")
add_compile_options("-enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang")

# add the executable
add_executable(interface-runlib ${CMAKE_SOURCE_DIR}/runlib/interface.cpp ${CMAKE_SOURCE_DIR}/runlib/runlib.cpp)
add_executable(ruri-runlib ${CMAKE_SOURCE_DIR}/runlib/ruri.cpp ${CMAKE_SOURCE_DIR}/runlib/runlib.cpp)
message(STATUS "Building dynamic libraries file is enabled.")

add_custom_command(
    TARGET interface-runlib
    POST_BUILD
    COMMAND strip interface-runlib
    VERBATIM
    )

add_custom_command(
    TARGET ruri-runlib
    POST_BUILD
    COMMAND strip ruri-runlib
    VERBATIM
    )

# add cxx flags
set(CMAKE_EXE_LINKER_FLAGS "-ffunction-sections -fdata-sections -z now -z noexecstack -fPIE -flto")
install (TARGETS ruri-runlib DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../out/bin)
install (TARGETS interface-runlib DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../out/bin)
