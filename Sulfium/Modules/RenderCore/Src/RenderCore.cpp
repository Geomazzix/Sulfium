#include "RenderCore.h"

namespace SFM
{
	RenderCore::RenderCore() :
		m_activeGraphicsAPI(EGraphicsAPI::COUNT),
		m_graphicsAPI(nullptr)
	{

	}

	void RenderCore::Initialize(EGraphicsAPI api)
	{
		LoadGraphicsAPI(api);
	}

	void RenderCore::Terminate()
	{
		m_graphicsAPI->Terminate();
		m_graphicsAPILoader.UnloadGraphicsAPI(m_graphicsAPI->GetName());
	}

	void RenderCore::LoadGraphicsAPI(EGraphicsAPI api)
	{
		if (m_activeGraphicsAPI == api)
		{
			printf("WARNING: Trying to reload a graphics API that is already active!\n");
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
			m_graphicsAPI = m_graphicsAPILoader.LoadGraphicsAPI("VulkanRenderer/VulkanRenderer").Handle;
			break;
		case EGraphicsAPI::DX12:
			printf("ERROR: Currently no DX12 support has been written!\n");
			break;
		case EGraphicsAPI::OPENGL:
			printf("ERROR: Currently no OpenGL support has been written!\n");
			break;
		default:
			printf("ERROR: Unknown Graphics API!\n");
			break;
		}

		m_graphicsAPI->Initialize();
	}
}