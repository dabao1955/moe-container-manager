cmake_minimum_required(VERSION 3.10)

# set the project name
project(pkc)

# add the executable
add_executable(pkc pkc.c)

set(CMAKE_EXE_LINKER_FLAGS "-static")
install (TARGETS pkc DESTINATION bin)
