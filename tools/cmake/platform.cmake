if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
   message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif
