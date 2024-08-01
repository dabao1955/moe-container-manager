if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
   message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()
