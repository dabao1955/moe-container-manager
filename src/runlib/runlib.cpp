// runlib.cpp
#include "runlib.hpp"
#include <dlfcn.h>
#include <cstring>

namespace runlib {
    void runlib(const char* libFile, const char* functionName, int argc, char* argv[]) {
        // Open the shared library
        void* handle = dlopen(libFile, RTLD_LAZY);
        if (!handle) {
            std::cerr << "Failed to load library: " << dlerror() << std::endl;
            exit(1);
        }

        // Define function type for main-like functions
        typedef int (*MainFunc_t)(int, char**);

        // Load the specified function
        MainFunc_t function = (MainFunc_t)dlsym(handle, functionName);
        if (!function) {
            std::cerr << "Failed to find function: " << dlerror() << std::endl;
            dlclose(handle);
            exit(2);
        }

        // Call the function with argc and argv
        int result = function(argc, argv);
        std::cout << "Function returned: " << result << std::endl;

        // Close the library
        dlclose(handle);
    }
}

