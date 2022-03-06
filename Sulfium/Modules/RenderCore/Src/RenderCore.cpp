#include "RenderCore/RenderCore.h"
#include "Core/Printer/Printer.h"

namespace SFM
{
	RenderCore::RenderCore() :
		m_activeGraphicsAPI(EGraphicsAPI::UNIDENTIFIED),
		m_graphicsAPI(nullptr),
		m_engine()
	{}

	void RenderCore::Initialize(std::weak_ptr<Engine> engine, Window& window, EGraphicsAPI api)
	{
		m_engine = engine;
		m_window = &window;

		LoadGraphicsAPI(api);
		SFM_LOGINFO("Successfully loaded the requested graphics API!");
	}

	void RenderCore::Terminate()
	{
		m_window = nullptr;
		m_graphicsAPI->Terminate();
		m_graphicsAPILoader.UnloadGraphicsAPI(m_graphicsAPI->GetName());
		SFM_LOGINFO("Successfully terminated the graphics API!");
	}

	void RenderCore::LoadGraphicsAPI(EGraphicsAPI api)
	{
		if (m_activeGraphicsAPI == api)
		{
			SFM_LOGWARNING("Trying to reload a graphics API that is already active!");
			return;
		}

		if (m_graphicsAPI != nullptr)
		{
			m_graphicsAPI->Terminate();
			m_graphicsAPILoader.UnloadGraphicsAPI(m_graphicsAPI->GetName());
		}
		
		switch (api)
		{
		case EGraphicsAPI::VULKAN:
#if defined(VULKAN_BACKEND)
			m_graphicsAPI = m_graphicsAPILoader.LoadGraphicsAPI("VulkanRenderer").Handle;
			m_activeGraphicsAPI = EGraphicsAPI::VULKAN;
#else
			SFM_LOGERROR("Trying to load in a backend that hasn't been build!\n Make sure to set BUILD_VULKAN_BACKEND to ON during the CMake build process!");
#endif
			break;
		case EGraphicsAPI::DX12:
			SFM_LOGERROR("Currently no DX12 support has been written!");
			break;
		case EGraphicsAPI::OPENGL:
			SFM_LOGERROR("Currently no OpenGL support has been written!");
			break;
		default:
			SFM_LOGERROR("Unknown Graphics API!");
			m_activeGraphicsAPI = EGraphicsAPI::UNIDENTIFIED;
			break;
		}

		if (m_activeGraphicsAPI != EGraphicsAPI::UNIDENTIFIED)
		{
			GraphicsAPICreateInfo createInfo =
			{
				m_engine,
				m_window->GetWindowHandle(),
				m_window->GetWindowWidth(),
				m_window->GetWindowHeight()
			};

			m_graphicsAPI->Initialize(std::move(createInfo));
		
			//Since the graphics APIs don't have access to the engine: create the events here.
			m_engine.lock()->GetEventSystem().GetEventDispatcher("Window").sink<SFM::WindowResizeEventArgs>().connect<&IGraphicsAPI::OnFrameBufferResize>(m_graphicsAPI);
		}
	}
}