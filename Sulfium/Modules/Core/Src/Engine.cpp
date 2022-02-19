#include "Core/Engine.h"

namespace SFM
{
	void Engine::Initialize()
	{
		m_printer.Initialize("Logs/SulfiumLogs.txt", eLogLevel::Info, eLogLevel::Info);
	}

	void Engine::Terminate()
	{
		m_printer.Terminate();
	}

	void Engine::Update()
	{
		m_eventSystem.DispatchEnqueuedEvents();
	}

	SFM::EventSystem& Engine::GetEventSystem()
	{
		return m_eventSystem;
	}
}