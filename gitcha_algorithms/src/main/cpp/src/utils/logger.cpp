#include "utils/logger.hpp"

com::yamadalab::gitcha::Logger::Logger()
{
    
}

com::yamadalab::gitcha::Logger::~Logger()
{

}

std::string com::yamadalab::gitcha::Logger::get_current_time()
{
    const std::chrono::system_clock::time_point &now = std::chrono::system_clock::now();
    const std::chrono::system_clock::duration &duration = now.time_since_epoch();

    long seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    long nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() % 1000000000;

    std::ostringstream time_stamp;
    time_stamp << seconds << "." << std::setfill('0') << std::setw(9) << nanoseconds;

    std::string time_str = time_stamp.str();

    return time_str;
}

void com::yamadalab::gitcha::Logger::log(const std::string &log_severity, const char *format, va_list args)
{
    char buffer[1024];
    std::vsnprintf(buffer, sizeof(buffer), format, args);

    std::cout << LOG_TAG << " " << log_severity << " [" << this->get_current_time() << "] " << buffer << '\n';
}

void com::yamadalab::gitcha::Logger::info(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    this->log(LOG_SEVERITY_INFO, format, args);
    va_end(args);
}

void com::yamadalab::gitcha::Logger::warn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    this->log(LOG_SEVERITY_WARN, format, args);
    va_end(args);
}

void com::yamadalab::gitcha::Logger::debug(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    this->log(LOG_SEVERITY_DEBUG, format, args);
    va_end(args);
}

void com::yamadalab::gitcha::Logger::error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    this->log(LOG_SEVERITY_ERROR, format, args);
    va_end(args);
}