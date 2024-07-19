if(EXISTS ruri)
   message(FATAL_ERROR "Please do not execute the cmake command at the root of the project!")
endif()

cmake_minimum_required(VERSION 3.10)

project(moe-container-manager-src)

#add_subdirectory(ruri)
#add_subdirectory(yoshinon)
#add_subdirectory(interface)
#add_subdirectory(rootfstool)

option(DEBUG_MODE "Enable debugging" ON)

if (DEBUG_MODE)
    message(WARNING "Warning: debug mode is enabled.")
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_options("-Wpedantic")
else()
    set(CMAKE_BUILD_TYPE Release)
    add_compile_options("-Oz")
endif()

include(ruri/ruri.cmake)
include(yoshinon/yoshinon.cmake)
include(interface/interface.cmake)
include(rootfstool/rootfstool.cmake)
include(share/share.cmake)
