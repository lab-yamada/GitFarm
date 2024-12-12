#include "logger/logger.hpp"

namespace com::yamadalab::gitfarm
{
	Logger::Logger()
	{

	}

	Logger::~Logger()
	{

	}

	std::string Logger::get_current_time() const
	{
		std::chrono::time_point<> now = std::chrono::system_clock::now();

		auto duration = now.time_since_epoch();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
		auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration) -
						   std::chrono::duration_cast<std::chrono::nanoseconds>(seconds);
	}


	void Logger::log() const
	{

	}

}