cmake_minimum_required(VERSION 3.10)
project(rootfstool LANGUAGES NONE)

add_custom_target(
    rootfstool ALL
    COMMAND cp ${CMAKE_SOURCE_DIR}/rootfstool/rootfstool ${CMAKE_SOURCE_DIR}/../out/bin/
    COMMENT "Installing rootfstool"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set correct path where main.go is located
)
