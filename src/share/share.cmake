# WIP

cmake_minimum_required(VERSION 3.10)
project(share LANGUAGES NONE)

add_custom_target(
    copyright ALL
    COMMAND cp ../LICENSE ${CMAKE_SOURCE_DIR}/../out/share/doc/moe-container-manager/
    COMMENT "Copying LICENSE"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set correct path where main.go is located
)

add_custom_target(
    share ALL
    COMMAND cp share/*.sh ${CMAKE_SOURCE_DIR}/../out/share/moe-container-manager/ && chmod 755 ${CMAKE_SOURCE_DIR}/../out/share/moe-container-manager/*.sh
    COMMENT "Copying necessary shell scripts"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set correct path where main.go is located
    DEPENDS copyright
)

add_custom_target(
    proc ALL
    COMMAND tar -xf share/proc.tar.xz -C ${CMAKE_SOURCE_DIR}/../out/share/moe-container-manager/proc/
    COMMENT "Exacting proc files"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set correct path where main.go is located
    DEPENDS share
)
