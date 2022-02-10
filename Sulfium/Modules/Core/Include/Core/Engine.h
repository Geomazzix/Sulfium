#pragma once
#include "Core/Events/EventSystem.h"
#include "Core/Printer/Printer.h"

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

		EventMessenger& GetEventMessenger();

	private:
		EventMessenger m_eventMessenger;
	};
}