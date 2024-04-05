#include "log.hpp"

namespace svlog {
    void basic_logfile()
    {
        try
        {
            auto logger = spdlog::basic_logger_mt("basic_logger", "/tmp/mcm.log");
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cout << "Log init failed: " << ex.what() << std::endl;
        }
    }
}
