#pragma once
#include <ThreadSystem/ThreadSystem.h>
#include <RenderCore/RenderCore.h>
#include <ApplicationCore/ApplicationCore.h>
#include <Core/Engine.h>

#include "World/World.h"
#include "Ecs/SystemDirector.h"

namespace SFM
{
	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class Sulfium
	{
	public:
		Sulfium();
		~Sulfium() = default;

		Sulfium(const Sulfium& rhs) = delete;
		Sulfium(Sulfium&& rhs) = delete;

		void Initialize();
		void Terminate();
		void Run();

		//Not fully safe, cause people can call Update from the outside, though due to maintenance workload
		//I've decided to leave this in.
		World& GetWorld();
		SystemDirector& GetSystemDirector(); 

	private:
		void TriggerEngineLoopEnd(const SFM::WindowTerminationEventArgs& e);
		void OnWindowPause(const SFM::WindowPauseEventArgs& e);

		std::shared_ptr<Engine> m_engine;

		bool m_sulfiumRunning;
		bool m_sulfiumPaused;

		ApplicationCore m_appCore;
		RenderCore m_renderCore;
		ThreadSystem m_threadSystem;
	
		World m_world;
		SystemDirector m_systemDirector;
	};
}