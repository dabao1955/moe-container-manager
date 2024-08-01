if(${CMAKE_VERSION} VERSION_GREATER "3.14.99" AND NOT DEFINED CMAKE_MSVC_RUNTIME_LIBRARY)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    cmake_policy(SET CMP0091 NEW)
endif()

include(CheckCXXCompilerFlag)
set(FLAGS_TO_CHECK
    "-enable-trivial-auto-var-init-zero-knowing-it-will-be-removed-from-clang"
    "-fdata-sections"
    "-ffunction-sections"
    "-fstack-clash-protection"
    "-fstack-protector-all"
    )

set(UNSUPPORTED_FLAGS "")

foreach(FLAG ${FLAGS_TO_CHECK})
    string(REPLACE "-" "_" FLAG_VAR "CXXFLAG_CHECK_${FLAG}")
    check_cxx_compiler_flag(${FLAG} ${FLAG_VAR})
    if(NOT ${FLAG_VAR})
        list(APPEND UNSUPPORTED_FLAGS ${FLAG})
    endif()
endforeach()

if(UNSUPPORTED_FLAGS)
    message(FATAL_ERROR "ERROR: The following CXX flags are not supported: ${UNSUPPORTED_FLAGS}")
endif()

