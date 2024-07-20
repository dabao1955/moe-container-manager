#include "include.hpp"
#include "log.hpp"
// use for signal.cpp on clang 14
#include <csignal>

namespace projsignal {
    static void sighandle(int sig){
            signal(sig, SIG_DFL);
            int clifd = open("/proc/self/cmdline", O_RDONLY | O_CLOEXEC);
            char buf[1024];
            ssize_t bufsize __attribute__((unused)) = read(clifd, buf, sizeof(buf));
            XLOG_ERROR("Fatal error, the program has stopped: {}");
            cout << "Fatal error, the program has stopped.\n";
            exit(127);
    }

    void register_signal(void){
            signal(SIGABRT, sighandle);
            signal(SIGBUS, sighandle);
            signal(SIGFPE, sighandle);
            signal(SIGILL, sighandle);
            signal(SIGQUIT, sighandle);
            signal(SIGSEGV, sighandle);
            signal(SIGSYS, sighandle);
            signal(SIGTRAP, sighandle);
            signal(SIGXCPU, sighandle);
            signal(SIGXFSZ, sighandle);
    }

}

