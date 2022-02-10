#include "Core/Engine.h"

namespace SFM
{
	void Engine::Initialize()
	{
		Printer::Get().Initialize("Logs/SulfiumLogs.txt", eLogLevel::Info, eLogLevel::Info);
	}

	void Engine::Terminate()
	{
		Printer::Get().Terminate();
	}

	EventMessenger& Engine::GetEventMessenger()
	{
		return m_eventMessenger;
	}
}