#include "ApplicationCore/ApplicationCore.h"

namespace SFM
{
	ApplicationCore::ApplicationCore() :
		m_engine(),
		m_input(nullptr),
		m_window()
	{}

	void ApplicationCore::Initialize(std::weak_ptr<Engine> engine)
	{
		m_engine = engine;

		m_input = std::make_shared<Input>();
		m_input->Initialize(m_engine);

		m_window = Win32Window();
		m_window.Initialize(m_engine, L"Application window", m_input, 1600, 900, true);

		SFM_LOGINFO("ApplicationCore successfully initialized!");
	}

	void ApplicationCore::Terminate()
	{
		m_window.Destroy();
		SFM_LOGINFO("ApplicationCore successfully terminated!");
	}

	void ApplicationCore::Update()
	{
		m_window.PollEvents();
	
		if (m_window.DoesWindowClose())
		{
			m_engine.lock()->GetEventSystem().GetEventDispatcher("Window").enqueue<SFM::WindowTerminationEventArgs>(false);
		}
	}

	std::weak_ptr<Input> ApplicationCore::GetInput()
	{
		return m_input;
	}

	Window& ApplicationCore::GetWindow()
	{
		return m_window;
	}
}