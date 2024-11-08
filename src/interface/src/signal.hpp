#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <fcntl.h> // For open(), O_RDONLY, O_CLOEXEC
#include <unistd.h> // For close() function
#ifdef __GLIBC__
#include <execinfo.h> // For backtrace
#else
#define backtrace(array, size) 0 // for musl
#define backtrace_symbols(array, size) nullptr
#endif
#include <ctime> // For timestamp

#endif
