#include <baseheaders.hpp>
#include <log.hpp>
// use for signal.cpp on clang 14
#include <csignal>

#include "signal.hpp"

namespace projsignal {
    static void write_log(const char* msg) {
        std::ofstream logfile("./program_crash.log", std::ios::app);
        if (logfile.is_open()) {
            std::time_t t = std::time(nullptr);
            char timestamp[100];
            std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

            logfile << "[" << timestamp << "] " << msg << std::endl;

            logfile.close();
        }
    }

    static void sighandle(int sig){
        signal(sig, SIG_DFL);
        int clifd = open("/proc/self/cmdline", O_RDONLY | O_CLOEXEC);
        char buf[1024];
        ssize_t bufsize __attribute__((unused)) = read(clifd, buf, sizeof(buf));
        close(clifd);

        std::string errorMsg = "Fatal error (" + std::to_string(sig) + "), the program has been stopped.";
        std::cout << errorMsg << std::endl;
        write_log(errorMsg.c_str());

        #ifdef __GLIBC__
        void *array[10];
        int size = backtrace(array, 10);
        char **stackTrace = backtrace_symbols(array, size);

        if (stackTrace) {
            std::cout << "Stack trace:" << std::endl;
            write_log("Stack trace:");
            for (int i = 0; i < size; i++) {
                std::cout << stackTrace[i] << std::endl;
                write_log(stackTrace[i]);
            }
            free(stackTrace);
        }
        #else
        write_log("Stack trace not available.");
        #endif
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
