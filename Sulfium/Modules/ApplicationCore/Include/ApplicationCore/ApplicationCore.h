#pragma once
#include <Core/Engine.h>

#include "ApplicationCore/Window/Window.h"
#include "ApplicationCore/Input/Input.h"

namespace SFM
{
	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class ApplicationCore
	{
	public:
		ApplicationCore();
		~ApplicationCore() = default;

		void Initialize(std::weak_ptr<Engine> engine);
		void Terminate();

		void Update();

		std::weak_ptr<Input> GetInput();
		Window& GetWindow();

	private:
		std::shared_ptr<Input> m_input;
		std::weak_ptr<Engine> m_engine;
		Window m_window;
	};
}