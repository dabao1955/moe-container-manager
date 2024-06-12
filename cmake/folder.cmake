if(NOT EXISTS ${CMAKE_SOURCE_DIR}/out)
   file(MAKE_DIRECTORY out)
else()
    execute_process(COMMAND rm -rf out/*)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/src/o)
   file(MAKE_DIRECTORY src/o)
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

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/out/share/moe-container-manager/proc)
   file(MAKE_DIRECTORY out/share/moe-container-manager/proc)
endif()
