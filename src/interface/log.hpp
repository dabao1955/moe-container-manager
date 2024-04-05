#include <iostream>
#include <filesystem>
#include <fstream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#ifndef LOG_HPP
#define LOG_HPP

namespace svlog {
    void basic_logfile();
}

#endif
