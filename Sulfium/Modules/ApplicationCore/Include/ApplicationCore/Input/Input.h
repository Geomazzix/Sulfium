#pragma once
#include "ApplicationCore/Input/InputEventArgs.h"
#include "ApplicationCore/Input/Keycodes.h"
#include "Core/Engine.h"

namespace SFM
{
	/// <summary>
	/// Serves as a monostate class, containing all the input states of the engine.
	/// </summary>
	class Input
	{
	public:
		Input();
		~Input();

		void Initialize(std::weak_ptr<Engine> engine);
		void Terminate();

		bool IsPressed(KeyCode key);
		float GetMouseX() const;
		float GetMouseY() const;
		float GetMouseDeltaX() const;
		float GetMouseDeltaY() const;

		void OnKeyboardStateChanged(KeyEventArgs& e);
		void OnMouseMoveChanged(MouseMotionEventArgs& e);
		void OnMouseButtonChanged(MouseButtonEventArgs& e);
		void OnMouseScrollWheelChanged(MouseWheelEventArgs& e);

	private:
		float m_MouseX;
		float m_MouseY;
		float m_MouseDeltaX;
		float m_MouseDeltaY;

		std::weak_ptr<Engine> m_engine;
		std::unordered_map<KeyCode, bool> m_ButtonMap;
	};
}