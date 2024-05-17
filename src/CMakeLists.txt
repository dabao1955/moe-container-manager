## Work in progress do not run it
cmake_minimum_required(VERSION 3.10)

add_subdirectory(ruri)
#add_subdirectory(yoshinon)
add_subdirectory(interface)
#add_subdirectory(rootfstool)

#include(ruri/ruri.cmake)
include(yoshinon/yoshinon.cmake)
#include(interface/interface.cmake)
include(rootfstool/rootfstool.cmake)

#set_property DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
#    "${CMAKE_BINARY_DIR}/out ${CMAKE_SOURCE_DIR}/ruri/build ${CMAKE_SOURCE_DIR}/yoshinon/build ${CMAKE_SOURCE_DIR}/interface/build"
#)
