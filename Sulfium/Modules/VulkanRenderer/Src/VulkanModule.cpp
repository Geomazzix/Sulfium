#include "VulkanModule.h"
#include "DLLDefines.h"
#include <cstdio>

namespace SFM
{
	void VulkanModule::Initialize()
	{
		printf("Vulkan successfully initialized!\n");
		m_GraphicsAPI_Name = "VulkanRenderer";
	}

	void VulkanModule::Terminate()
	{
		printf("Vulkan successfully terminated!\n");
	}
}

extern "C" MODULE_EXPORT SFM::IGraphicsAPI* __cdecl CreateModule()
{
	return new SFM::VulkanModule();
}