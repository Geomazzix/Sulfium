#pragma once

#if defined(WIN32) || defined(WIN64)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/printf.h>
#endif

namespace SFM
{
	/// <summary>
	/// Used to set the log level for the console.
	/// </summary>
	enum class eLogLevel
	{
		Debug = 1,
		Info = 2,
		Warning = 3,
		Error = 4,
		Critical = 5,
		OFF = 6
	};

	/// <summary>
	/// The printer class has the capability of rolling out log files on UNIX systems and printing formatted messages
	/// to the console using Spdlog. WARNING: The messages only get formated when the the platform is UNIX based,
	/// otherwise it prints the message raw.
	/// </summary>
	class Printer
	{
	public:
		Printer();
		~Printer() = default;

		void Initialize(const std::string& filepath, eLogLevel logLevel, eLogLevel fileLogLevel);
		void Terminate();

		void SetGlobalLogLevel(eLogLevel logLevel);
		void SetFileLogLevel(eLogLevel logLevel);
		void SetConsoleLogLevel(eLogLevel logLevel);

		template<typename... Args>
		void LogDebug(const std::string& message, Args&&... arguments);
		template<typename... Args>
		void LogInfo(const std::string& message, Args&&... arguments);
		template<typename... Args>
		void LogWarning(const std::string& message, Args&&... arguments);
		template<typename... Args>
		void LogError(const std::string& message, Args&&... arguments);
		template<typename... Args> 
		void LogCritical(const std::string& message, Args&&... arguments);

	private:
		template <typename ... Args>
		std::string FormatSpdLogMessage(const std::string& message, Args&&... arguments);
		const std::string m_fileLoggerName;

		eLogLevel m_consoleLogLevel;
		eLogLevel m_fileLogLevel;
		
#if defined(WIN32) || defined(WIN64)
		std::shared_ptr<spdlog::logger> m_fileLogger; //for some reason Spdlog enforces the use of a shared pointer...
#endif
	};

	template<typename...Args>
	void Printer::LogDebug(const std::string& message, Args&&... arguments)
	{
		const std::string formattedMessage{ FormatSpdLogMessage(message,std::forward<Args>(arguments)...) };

		if (m_consoleLogLevel <= eLogLevel::Debug)
		{
#if defined(WIN32) || defined (WIN64)
			spdlog::debug(formattedMessage);
#else
			printf("%s\n", formattedMessage);
#endif		
		}

		if (m_fileLogLevel <= eLogLevel::Debug)
		{
#if defined(WIN32) || defined (WIN64)
			m_fileLogger->debug(formattedMessage);
#endif
		}
	}

	template<typename...Args>
	void Printer::LogInfo(const std::string& message, Args&&... arguments)
	{
		const std::string formattedMessage{ FormatSpdLogMessage(message,std::forward<Args>(arguments)...) };

		if (m_consoleLogLevel <= eLogLevel::Info)
		{
#if defined(WIN32) || defined (WIN64)
			spdlog::info(formattedMessage);
#else
			printf("%s\n", formattedMessage);
#endif		
		}

		if (m_fileLogLevel <= eLogLevel::Info)
		{
#if defined(WIN32) || defined (WIN64)
			m_fileLogger->info(formattedMessage);
#endif
		}
	}

	template<typename...Args>
	void Printer::LogWarning(const std::string& message, Args&&... arguments)
	{
		const std::string formattedMessage{ FormatSpdLogMessage(message,std::forward<Args>(arguments)...) };

		if (m_consoleLogLevel <= eLogLevel::Warning)
		{
#if defined(WIN32) || defined (WIN64)
			spdlog::warn(formattedMessage);
#else
			printf("%s\n", formattedMessage);
#endif		
		}

		if (m_fileLogLevel <= eLogLevel::Warning)
		{
#if defined(WIN32) || defined (WIN64)
			m_fileLogger->warn(formattedMessage);
#endif
		}
	}

	template<typename...Args>
	void Printer::LogError(const std::string& message, Args&&... arguments)
	{
		const std::string formattedMessage{ FormatSpdLogMessage(message,std::forward<Args>(arguments)...) };

		if (m_consoleLogLevel <= eLogLevel::Error)
		{
#if defined(WIN32) || defined (WIN64)
			spdlog::error(formattedMessage);
#else
			printf("%s\n", formattedMessage);
#endif		
		}

		if (m_fileLogLevel <= eLogLevel::Error)
		{
#if defined(WIN32) || defined (WIN64)
			m_fileLogger->error(formattedMessage);
#endif
		}
	}

	template<typename...Args>
	void Printer::LogCritical(const std::string& message, Args&&... arguments)
	{
		const std::string formattedMessage{ FormatSpdLogMessage(message,std::forward<Args>(arguments)...) };

		if (m_consoleLogLevel <= eLogLevel::Critical)
		{
#if defined(WIN32) || defined (WIN64)
			spdlog::critical(formattedMessage);
#else
			printf("%s\n", formattedMessage);
#endif		
		}

		if (m_fileLogLevel <= eLogLevel::Critical)
		{
#if defined(WIN32) || defined (WIN64)
			m_fileLogger->critical(formattedMessage);
#endif
		}
	}

	template <typename ... Args>
	std::string Printer::FormatSpdLogMessage(const std::string& message, Args&&... arguments)
	{
#if defined(WIN32) || defined (WIN64)
		return std::string{ fmt::sprintf(message,std::forward<Args>(arguments)...) };
#endif
		//TODO: Add multiple platform specific logging methods.
		return message;
	}
}

#define SFM_LOGDEBUG	spdlog::debug
#define SFM_LOGINFO		spdlog::info
#define SFM_LOGWARNING	spdlog::warn
#define SFM_LOGERROR	spdlog::error
#define SFM_LOGCRITICAL spdlog::critical