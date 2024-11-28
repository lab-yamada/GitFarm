#ifndef UTILS_LOGGER__HPP
#define UTILS_LOGGER__HPP

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <memory>
#include <cstdarg>
#include <cstdio> 

#define LOG_TAG "[AlgoCPP]"
#define LOG_SEVERITY_INFO "[INFO]"
#define LOG_SEVERITY_WARN "[WARN]"
#define LOG_SEVERITY_DEBUG "[DEBUG]"
#define LOG_SEVERITY_ERROR "[ERROR]"

namespace com
{
    namespace yamadalab
    {
        namespace gitcha
        {
            class Logger
            {
            private:
                std::string get_current_time();
                void log(const std::string &log_severity, const char *format, va_list args);

            public:
                explicit Logger();
                virtual ~Logger();
                void info(const char *format, ...);
                void warn(const char *format, ...);
                void debug(const char *format, ...);
                void error(const char *format, ...);

            public:
                using SharedPtr = std::shared_ptr<Logger>;

            };
        }
    }
}

#endif