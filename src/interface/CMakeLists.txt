cmake_minimum_required(VERSION 3.10)

# set the project name
project(moe-container-manager-interface)
set(CMAKE_C_COMPILER "clang")

# add the executable
add_executable(interface main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")
install (TARGETS interface DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../out)
