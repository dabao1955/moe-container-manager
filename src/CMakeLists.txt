cmake_minimum_required(VERSION 3.10)

project(moe-container-manager 
    VERSION 0.0.1
    DESCRIPTION " This is a container manager for a port of Linux cli environment that cannot run docker and kvm."
    HOMEPAGE_URL "https://github.com/dabao1955/moe-container-manager")

set(PROJECT_LICENSE "Apache 2.0 license")

include(../tools/cmake/debug.cmake)
include(../tools/cmake/findpackage.cmake)
include(ruri/ruri.cmake)
include(yoshinon/yoshinon.cmake)
include(interface/interface.cmake)
include(rootfstool/rootfstool.cmake)
include(share/share.cmake)
include(../tools/cmake/setting.cmake)
include(../tools/cmake/platform.cmake)
include(../tools/cmake/folder.cmake)
