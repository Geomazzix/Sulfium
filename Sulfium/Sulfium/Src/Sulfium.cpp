#include "Sulfium.h"
#include <Core/Timer/Stopwatch.h>
#include "Ecs/Systems/TransformSystem.h"

namespace SFM
{
	Sulfium::Sulfium() :
		m_sulfiumRunning(true),
		m_sulfiumPaused(false)
	{}

	void Sulfium::Initialize()
	{
		m_engine = std::make_shared<Engine>();
		m_engine->Initialize();

		//Initialize all subsystems of the engine.
		SFM_LOGINFO("Sulfium booted.");
		SFM_LOGINFO("Starting up modules:");
		SFM_LOGINFO("==========================================");

		//Creating a way out, for when the application is requested to be closed.
		EventDispatcher& dispatcher = m_engine->GetEventSystem().AddDispatcher("Window");
		dispatcher.sink<SFM::WindowTerminationEventArgs>().connect<&Sulfium::TriggerEngineLoopEnd>(this);
		dispatcher.sink<SFM::WindowPauseEventArgs>().connect<&Sulfium::OnWindowPause>(this);

		//Initializing the modules.
		m_threadSystem.Initialize();
		m_appCore.Initialize(m_engine);
		m_renderCore.Initialize(m_engine, EGraphicsAPI::VULKAN);

		//Creating the internal systems.
		m_systemDirector.RegisterSystem(new TransformSystem(m_world.GetEcsWorld()));

		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Modules have been loaded: Sulfium successfully initialized.");
		SFM_LOGINFO("==========================================");
	}

	void Sulfium::Terminate()
	{
		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Terminating all modules");

		m_renderCore.Terminate();
		m_appCore.Terminate();
		m_threadSystem.Terminate();

		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Sulfium successfully shutdown. (the core engine will be shutdown after this messages, which includes the logger");

		m_engine->Terminate();
	}

	void Sulfium::TriggerEngineLoopEnd(const SFM::WindowTerminationEventArgs& e)
	{
		m_sulfiumRunning = e.DoesTerminate;
	}

	void Sulfium::OnWindowPause(const SFM::WindowPauseEventArgs& e)
	{
		m_sulfiumPaused = e.DoesPause;
	}

	void Sulfium::Run()
	{
		SFM_LOGINFO("Entering engine loop...");

		float dt = 0.0f;
		Stopwatch watch;

		watch.Start();
		while (m_sulfiumRunning)
		{
			//Only render if the window is not being resized.
			if (!m_sulfiumPaused)
			{
				//RenderSystem.Render?
				m_systemDirector.Update(dt);
			}

			m_appCore.Update();	//Poll windows events
			m_engine->Update();	//Dispatch all queued events at the end of the frame.
			
			watch.Stop();
			dt = watch.GetTimeInMs();
			watch.Reset(true);
		}

		SFM_LOGINFO("Exiting engine loop...");
	}

	SFM::World& Sulfium::GetWorld()
	{
		return m_world;
	}

	SFM::SystemDirector& Sulfium::GetSystemDirector()
	{
		return m_systemDirector;
	}

}