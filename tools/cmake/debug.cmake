option(DEBUG_MODE "Enable debugging" ON)
option(MOE_LIB "Build ruri and interface with a systen library" OFF)

if (DEBUG_MODE)
    message(WARNING "Warning: debug mode is enabled.")
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_options(
        -Wpedantic -pedantic
        -Wextra
        -Wredundant-decls -Wlogical-op
        -Wstrict-overflow=5 -Winit-self
        -Wuninitialized -Wsign-conversion
        -Wcast-qual
    )
else()
    set(CMAKE_BUILD_TYPE Release)
    add_compile_options(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_REENTRANT)
endif()
