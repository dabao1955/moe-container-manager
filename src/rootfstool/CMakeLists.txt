cmake_minimum_required(VERSION 3.10)
project(rootfstool LANGUAGES NONE)

add_custom_target(
    format ALL
    COMMAND shfmt -i 2 -w rootfstool
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go mod download
)

add_custom_target(
    rootfstool ALL
    COMMAND cp ${CMAKE_SOURCE_DIR}/rootfstool ${CMAKE_SOURCE_DIR}/../out/
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set correct path where main.go is located
    DEPENDS format
)
