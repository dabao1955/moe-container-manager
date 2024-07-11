if (CMAKE_SYSTEM_NAME MATCHES "Windows")
   message(FATAL_ERROR "Please build it on Linux environment!")
endif()

if(NOT EXISTS src)
   message(FATAL_ERROR "Please execute the cmake command at the root of the project!")
endif()
