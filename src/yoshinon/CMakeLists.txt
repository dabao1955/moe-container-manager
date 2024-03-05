# CMakeLists.txt for the Go project
cmake_minimum_required(VERSION 3.14)

project(yoshinon LANGUAGES NONE)

find_program(GO_COMPILER go)

if(NOT GO_COMPILER)
    message(FATAL_ERROR "Go compiler not found")
endif()

# Capture the latest commit ID from the git log
execute_process(
    COMMAND git log --oneline
    COMMAND head -1
    COMMAND cut -d " " -f 1
    OUTPUT_VARIABLE COMMIT_ID
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for git command
)

set(LDFLAGS "-s -w -X main.Commit_id=${COMMIT_ID}")

add_custom_target(
    mod_download ALL
    COMMAND ${GO_COMPILER} mod download
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go mod download
)

add_custom_target(
    yoshinon ALL
    COMMAND ${GO_COMPILER} build -ldflags ${LDFLAGS} -o yoshinon main.go
    COMMAND mv ${CMAKE_SOURCE_DIR}/yoshinon ${CMAKE_SOURCE_DIR}/../out/
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set correct path where main.go is located
    DEPENDS mod_download
)

add_custom_target(
    format
    COMMAND ${GO_COMPILER} fmt ./...
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go fmt
)
