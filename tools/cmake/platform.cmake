if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
   message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()

message(STATUS "CMake target system architecture: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMake host system name: ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "CMake host kernel version: ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "CMake host system architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

