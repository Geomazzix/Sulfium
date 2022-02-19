#include "Core/Printer/Printer.h"

#if defined(WIN32) || defined(WIN64)
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#endif

namespace SFM
{
	Printer::Printer() :
#if defined(WIN32) || defined(WIN64)
		m_fileLogger(nullptr),
#endif
		m_fileLoggerName("ConsoleLog"),
		m_consoleLogLevel(eLogLevel::Info),
		m_fileLogLevel(eLogLevel::Info)
	{}

	void Printer::Initialize(const std::string& filepath, eLogLevel logLevel, eLogLevel fileLogLevel)
	{
		m_consoleLogLevel = logLevel;
		m_fileLogLevel = fileLogLevel;

#if defined(WIN32) || defined(WIN64)
		spdlog::set_level(static_cast<spdlog::level::level_enum>(logLevel));
		m_fileLogger = spdlog::basic_logger_mt<spdlog::async_factory>("FileLogger", filepath);
		m_fileLogger->set_level(static_cast<spdlog::level::level_enum>(fileLogLevel));
#endif
	}

	void Printer::SetConsoleLogLevel(eLogLevel logLevel)
	{
		m_consoleLogLevel = logLevel;
#if defined(WIN32) || defined(WIN64)
		spdlog::set_level(static_cast<spdlog::level::level_enum>(m_consoleLogLevel));
#endif
	}

	void Printer::SetFileLogLevel(eLogLevel logLevel)
	{
		m_fileLogLevel = logLevel;
#if defined(WIN32) || defined(WIN64)
		m_fileLogger->set_level(static_cast<spdlog::level::level_enum>(m_fileLogLevel));
#endif
	}

	void Printer::Terminate()
	{
#if defined(WIN32) || defined(WIN64)
		m_fileLogger->flush();
		spdlog::shutdown();
#endif
	}
}