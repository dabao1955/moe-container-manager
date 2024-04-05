#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <string>
#include <linux/version.h>

#ifndef MAIN_HPP
#define MAIN_HPP

namespace proj {
    #ifndef __linux__
    #error "This program is only for linux."
    #else
    #define _GNU_SOURCE 1
    #endif

    const char* const prog_name = "interface";
    const char* const prog_version = "v0.0.1rc2";
    enum
    {
      BUF_SIZE = (1024 * 1024)
    };

    void get_input(char *buf, int len);
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 14, 0)
#warning "This program has only used to linux version 4.14.0 or later."
#endif

#define MAX_COMMANDS (1024)
#define MAX_ENVS (128 * 2)
#define MAX_MOUNTPOINTS (128 * 2)

#endif
