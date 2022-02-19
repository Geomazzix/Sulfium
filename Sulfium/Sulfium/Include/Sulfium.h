#pragma once
#include <ThreadSystem/ThreadSystem.h>
#include <RenderCore/RenderCore.h>
#include <ApplicationCore/ApplicationCore.h>
#include <Core/Engine.h>

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

		Sulfium& Get();

		void Initialize();
		void Terminate();

		void TriggerEngineLoopEnd(const SFM::WindowTerminationEventArgs& e);
		void OnWindowPause(const SFM::WindowPauseEventArgs& e);

	private:
		void EngineLoop();

		std::shared_ptr<Engine> m_engine;

		bool m_sulfiumRunning;
		bool m_sulfiumPaused;

		ApplicationCore m_appCore;
		RenderCore m_renderCore;
		ThreadSystem m_threadSystem;
	};
}