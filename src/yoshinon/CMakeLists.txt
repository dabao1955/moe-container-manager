# CMakeLists.txt for the Go project
cmake_minimum_required(VERSION 3.10)

project(yoshinon LANGUAGES NONE)

find_program(GO_COMPILER go)

if(GO_COMPILER)
    execute_process(
        COMMAND ${GO_COMPILER} version
        OUTPUT_VARIABLE GO_VERSION_OUTPUT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    string(REGEX MATCH "go version go([0-9]+\\.[0-9]+\\.[0-9]+)" GO_VERSION_MATCH ${GO_VERSION_OUTPUT})
    if (GO_VERSION_MATCH)
        set(GO_VERSION ${CMAKE_MATCH_1})
    else()
        set(GO_VERSION "unknown")
    endif()
    message(STATUS "Found Go Compiler: ${GO_COMPILER} (found version ${GO_VERSION})")
else ()
    message(FATAL_ERROR "Go compiler not found")
endif ()


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
    COMMENT "Downloading GO building dependence"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/yoshinon # Set the working directory for go mod download
)

add_custom_target(
    yoshinon ALL
    COMMAND CGO_ENABLED=1 ${GO_COMPILER} build -ldflags ${LDFLAGS} -o yoshinon main.go
    COMMAND mv ${CMAKE_SOURCE_DIR}/yoshinon/yoshinon ${CMAKE_SOURCE_DIR}/../out/bin/
    COMMENT "Built target yoshinon"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/yoshinon # Set correct path where main.go is located
    DEPENDS mod_download
)

add_custom_target(
    format
    COMMAND ${GO_COMPILER} fmt ./...
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go fmt
)
