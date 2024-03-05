#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

namespace proj {
    #ifndef __linux__
    #error "This program is only for linux."
    #else
    #define _GNU_SOURCE 1
    #endif

    const char* const prog_name = "interface";
    const char* const prog_version = "v0.0.1rc1";
}
