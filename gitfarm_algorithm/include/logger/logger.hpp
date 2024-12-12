#ifndef GITFARM_LOGGER_HPP
#define GITFARM_LOGGER_HPP

#include <memory>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

#define SEVERITY_INFO "[INFO]"
#define SEVERITY_WARNING "[WARNING]"
#define SEVERITY_ERROR "[ERROR]"
#define SEVERITY_DEBUG "[DEBUG]"

namespace com::yamadalab::gitfarm
{
	class Logger final
	{
	private:
		std::string get_current_time() const;
		void log() const;

    public:
      	explicit Logger();
        virtual ~Logger();

	public:
		using SharedPtr = std::shared_ptr<Logger>;

	};
}

#endif //GITFARM_LOGGER_HPP
