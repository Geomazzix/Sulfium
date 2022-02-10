#pragma once
#include <Core/Engine.h>
#include <ThreadSystem/ThreadSystem.h>
#include <RenderCore/RenderCore.h>
#include <ApplicationCore/ApplicationCore.h>

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

		void TriggerEngineLoopEnd();

		SFM::EventMessenger& GetEventMessenger();
		std::weak_ptr<Input> GetInput();

	private:
		void EngineLoop();

		bool m_engineRunning;

		std::shared_ptr<Engine> m_engine;
		
		ApplicationCore m_appCore;
		RenderCore m_renderCore;
		ThreadSystem m_threadSystem;
	};
}