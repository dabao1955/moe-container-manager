if(EXISTS ruri)
   message(FATAL_ERROR "Please do not execute the cmake command at the root of the project!")
endif()

cmake_minimum_required(VERSION 3.10)

project(moe-container-manager-src)

#add_subdirectory(ruri)
#add_subdirectory(yoshinon)
#add_subdirectory(interface)
#add_subdirectory(rootfstool)

include(ruri/ruri.cmake)
include(yoshinon/yoshinon.cmake)
include(interface/interface.cmake)
include(rootfstool/rootfstool.cmake)
include(share/share.cmake)
