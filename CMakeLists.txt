# Work in progress do not run it.
cmake_minimum_required(VERSION 3.10)

# set the project name
project(moe-container-manager VERSION 0.0.1 LANGUAGES NONE)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
   message(FATAL_ERROR "Please build it on Linux environment!")
endif()

if(NOT EXISTS src)
   message(FATAL_ERROR "Please execute the cmake command at the root of the project!")
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/out)
   file(MAKE_DIRECTORY out)
else()
    execute_process(COMMAND rm -rf out/*)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/out/bin)
   file(MAKE_DIRECTORY out/bin)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/out/share)
   file(MAKE_DIRECTORY out/share)
endif()
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/out/share/moe-container-manager/)
   file(MAKE_DIRECTORY out/share/moe-container-manager/)
endif()

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

add_custom_target(
    build
    COMMAND cd src && cmake . -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` && make -j$(nproc --all)
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go fmt
)

add_custom_target(
    install
    COMMAND cp -r src/out/* out/bin/ && cp src/share/*.sh out/share/moe-container-manager/ && cp LICENSE out/share/doc/moe-container-manager/ && tar -xf src/share/proc.tar.xz -C out/share/moe-container-manager/proc && cp out/bin/* /usr/bin/ && cp out/share/moe-container-manager/ /usr/share/
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} # Set the working directory for go fmt
    DEPENDS build
)
