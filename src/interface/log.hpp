#include "include.hpp"
#include <memory>
#include <time.h>
#include <chrono>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no color needed
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

#ifndef LOG_HPP
#define LOG_HPP

static inline int NowDateToInt()
{
	time_t now;
	time(&now);

	tm p;
	localtime_r(&now, &p);
	int now_date = (1900 + p.tm_year) * 10000 + (p.tm_mon + 1) * 100 + p.tm_mday;
	return now_date;
}

static inline int NowTimeToInt()
{
	time_t now;
	time(&now);
	tm p;
	localtime_r(&now, &p);

	int now_int = p.tm_hour * 10000 + p.tm_min * 100 + p.tm_sec;
	return now_int;
}

class XLogger
{
public:
	static XLogger* getInstance()
	{
		static XLogger xlogger;
		return &xlogger;
	}

	shared_ptr<spdlog::logger> getLogger()
	{
		return m_logger;
	}

private:
	// make constructor private to avoid outside instance
	XLogger()
	{
		// hardcode log path
		const string log_dir = "./log"; // should create the folder if not exist
		const string logger_name_prefix = "test_";

		// decide print to console or log file
		bool console = false;

		// decide the log level
		string level = "debug";

		try
		{
			// logger name with timestamp
			int date = NowDateToInt();
			int time = NowTimeToInt();
			const string logger_name = logger_name_prefix + to_string(date) + "_" + to_string(time);

			if (console)
				m_logger = spdlog::stdout_color_st(logger_name); // single thread console output faster
			else
				//m_logger = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>(logger_name, log_dir + "/" + logger_name + ".log"); // only one log file
				m_logger = spdlog::create_async<spdlog::sinks::rotating_file_sink_mt>(logger_name, log_dir + "/" + logger_name + ".log", 500 * 1024 * 1024, 1000); // multi part log files, with every part 500M, max 1000 files

			// custom format
			m_logger->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] [%@] %v"); // with timestamp, thread_id, filename and line number

                        if (level == "trace")
			{
				m_logger->set_level(spdlog::level::trace);
				m_logger->flush_on(spdlog::level::trace);
			}
			else if (level == "debug")
			{
				m_logger->set_level(spdlog::level::debug);
				m_logger->flush_on(spdlog::level::debug);
			}
			else if (level == "info")
			{
				m_logger->set_level(spdlog::level::info);
				m_logger->flush_on(spdlog::level::info);
			}
			else if (level == "warn")
			{
				m_logger->set_level(spdlog::level::warn);
				m_logger->flush_on(spdlog::level::warn);
			}
			else if (level == "error")
			{
				m_logger->set_level(spdlog::level::err);
				m_logger->flush_on(spdlog::level::err);
			}
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			cout << "Log initialization failed: " << ex.what() << endl;
		}
	}

	~XLogger()
	{
		spdlog::drop_all(); // must do this
	}

	void* operator new(size_t size) noexcept{
            return nullptr;
	}

	XLogger(const XLogger&) = delete;
	XLogger& operator=(const XLogger&) = delete;

private:
	shared_ptr<spdlog::logger> m_logger;
};

#define XLOG_TRACE(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::trace, __VA_ARGS__)
#define XLOG_DEBUG(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::debug, __VA_ARGS__)
#define XLOG_INFO(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::info, __VA_ARGS__)
#define XLOG_WARN(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::warn, __VA_ARGS__)
#define XLOG_ERROR(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::err, __VA_ARGS__)

#endif
