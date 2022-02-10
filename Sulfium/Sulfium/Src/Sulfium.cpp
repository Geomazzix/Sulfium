#include "Sulfium.h"

namespace SFM
{
	Sulfium::Sulfium() :
		m_engineRunning(true)
	{}

	void Sulfium::Initialize()
	{
		m_engine = std::make_shared<Engine>();
		m_engine->Initialize();

		//Initialize all subsystems of the engine.
		SFM_LOGINFO("Sulfium booted.");
		SFM_LOGINFO("Starting up modules:");
		SFM_LOGINFO("==========================================");

		m_threadSystem.Initialize();
		m_appCore.Initialize(m_engine);
		m_renderCore.Initialize(m_engine, EGraphicsAPI::VULKAN);

		//Creating a way out, for when the application is requested to be closed.
		m_engine->GetEventMessenger().AddMessenger("OnAppClose");
		m_engine->GetEventMessenger().ConnectListener("OnAppClose", &Sulfium::TriggerEngineLoopEnd, this);

		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Modules have been loaded: Sulfium successfully initialized.");
		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Entering engine loop:");

		//Enter the engine loop.
		EngineLoop();
	}

	void Sulfium::Terminate()
	{
		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Exiting engine loop, starting to terminate all modules");

		m_renderCore.Terminate();
		m_appCore.Terminate();
		m_threadSystem.Terminate();

		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Sulfium successfully shutdown. (the core engine will be shutdown after this messages, which includes the logger");

		m_engine->Terminate();
	}

	void Sulfium::TriggerEngineLoopEnd()
	{
		m_engineRunning = false; //Make sure to exit the application loop.
	}

	SFM::EventMessenger& Sulfium::GetEventMessenger()
	{
		return m_engine->GetEventMessenger();
	}

	std::weak_ptr<SFM::Input> Sulfium::GetInput()
	{
		return m_appCore.GetInput();
	}

	void Sulfium::EngineLoop()
	{
		while (m_engineRunning)
		{
			m_appCore.Update();
		}
	}
}