#pragma once
#include "Core/Printer/Printer.h"
#include "Core/Events/EventSystem.h"
#include "spdlog/spdlog.h"

namespace SFM
{
	/// <summary>
	/// The class that maintains the lifetime and accessibility to the lowest level of systems. All classes should have
	/// access to the engine, as long as it is running.
	/// </summary>
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		void Initialize();
		void Terminate();

		template<typename... Args>
		void PrintAndLog(const std::string& message, eLogLevel severity, Args&&... arguments);

		void Update();

		EventSystem& GetEventSystem();

	private:
		EventSystem m_eventSystem;
		Printer m_printer;
	};


	template<typename... Args>
	void SFM::Engine::PrintAndLog(const std::string& message, eLogLevel severity, Args&&... arguments)
	{
		switch (severity)
		{
		case eLogLevel::Debug:		m_printer.LogDebug(message, std::forward<Args>(arguments)...);			break;
		case eLogLevel::Info:		m_printer.LogInfo(message, std::forward<Args>(arguments)...);			break;
		case eLogLevel::Warning:	m_printer.LogWarning(message, std::forward<Args>(arguments)...);		break;
		case eLogLevel::Error:		m_printer.LogError(message, std::forward<Args>(arguments)...);			break;
		case eLogLevel::Critical:	m_printer.LogCritical(message, std::forward<Args>(arguments)...);		break;
		case eLogLevel::OFF:		return;											//no logging :).
		default:
			m_printer.LogError("Unidentified log severity: %i", static_cast<int>(severity));
			break;
		}
	}
}