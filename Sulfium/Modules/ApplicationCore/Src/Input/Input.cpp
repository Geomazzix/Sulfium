#include "ApplicationCore/Input/Input.h"

namespace SFM
{
	Input::Input() :
		m_MouseDeltaX(0),
		m_MouseDeltaY(0),
		m_MouseX(0),
		m_MouseY(0),
		m_engine()
	{}

	Input::~Input()
	{
		m_ButtonMap.clear();
	}

	void Input::Initialize(std::weak_ptr<Engine> engine)
	{
		m_engine = engine;
		m_engine.lock()->GetEventMessenger().AddMessenger<MouseWheelEventArgs&>("OnMouseScrollWheelChanged");
	}

	void Input::Terminate()
	{
		m_ButtonMap.clear();
	}

	bool Input::IsPressed(KeyCode key)
	{
		return m_ButtonMap[key];
	}

	float Input::GetMouseX() const
	{
		return m_MouseX;
	}

	float Input::GetMouseY() const
	{
		return m_MouseY;
	}

	float Input::GetMouseDeltaX() const
	{
		return m_MouseDeltaX;
	}

	float Input::GetMouseDeltaY() const
	{
		return m_MouseDeltaY;
	}

	void Input::OnKeyboardStateChanged(KeyEventArgs& e)
	{
		switch (e.State)
		{
		case KeyEventArgs::KeyState::Pressed:
		{
			if (e.Alt) m_ButtonMap[KeyCode::AltKey] = true;
			if (e.Shift) m_ButtonMap[KeyCode::ShiftKey] = true;
			if (e.Control) m_ButtonMap[KeyCode::ControlKey] = true;

			m_ButtonMap[e.Key] = true;
			break;
		}
		case KeyEventArgs::KeyState::Released:
		{
			if (e.Alt) m_ButtonMap[KeyCode::AltKey] = false;
			if (e.Shift) m_ButtonMap[KeyCode::ShiftKey] = false;
			if (e.Control) m_ButtonMap[KeyCode::ControlKey] = false;

			m_ButtonMap[e.Key] = false;
			break;
		}
		}
	}

	void Input::OnMouseMoveChanged(MouseMotionEventArgs& e)
	{
		m_MouseX = e.X;
		m_MouseDeltaX = e.RelX;
		m_MouseY = e.Y;
		m_MouseDeltaY = e.RelY;
	}

	void Input::OnMouseButtonChanged(MouseButtonEventArgs& e)
	{
		switch (e.Button)
		{
		case MouseButtonEventArgs::MouseButton::Left:
			m_ButtonMap[KeyCode::LButton] = static_cast<bool>(e.State);
			break;
		case MouseButtonEventArgs::MouseButton::Right:
			m_ButtonMap[KeyCode::RButton] = static_cast<bool>(e.State);
			break;
		case MouseButtonEventArgs::MouseButton::Middle:
			m_ButtonMap[KeyCode::MButton] = static_cast<bool>(e.State);
			break;
		default:
			SFM_LOGWARNING("The mouse button that was pressed is not supported in the input class and will therefor not be processed.\n");
			break;
		}
	}

	void Input::OnMouseScrollWheelChanged(MouseWheelEventArgs& e)
	{
		m_engine.lock()->GetEventMessenger().EvokeMessenger("OnMouseScrollWheelChanged", e);
	}
}