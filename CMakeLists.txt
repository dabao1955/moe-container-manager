# Warning: do not use this in dpkg build ci

cmake_minimum_required(VERSION 3.10)

# set the project name
project(moe-container-manager VERSION 0.0.1 LANGUAGES NONE)

include(tools/cmake/platform.cmake)
include(tools/cmake/folder.cmake)
add_custom_target(
    doc
    COMMAND make -C docs
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go fmt
)

add_custom_target(
    distclean
    COMMAND perl tools/clean.pl
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go fmt
)

#add_subdirectory(src)

add_custom_target(
    build
    COMMAND cd src && cd o && cmake .. -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` && make -j$(nproc --all)
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go fmt
)

add_custom_target(
    installbin
    COMMAND cp -r src/out/* out/bin/ && cp src/share/*.sh out/share/moe-container-manager/ && cp LICENSE out/share/doc/moe-container-manager/ && tar -xf src/share/proc.tar.xz -C out/share/moe-container-manager/proc && cp out/bin/* /usr/bin/ && cp out/share/moe-container-manager/ /usr/share/
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go fmt
    DEPENDS build
)
