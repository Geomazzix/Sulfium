#include "VulkanRenderer/VulkanModule.h"
#include "RenderCore/DLLDefines.h"

namespace SFM
{
	void VulkanModule::Initialize(std::weak_ptr<Engine> engine)
	{
		m_engine = engine;

		SFM_LOGINFO("Vulkan successfully initialized!");
		m_GraphicsAPI_Name = "VulkanRenderer";
	}

	void VulkanModule::Terminate()
	{
		SFM_LOGINFO("Vulkan successfully terminated!");
	}

	void VulkanModule::OnFrameBufferResize(const WindowResizeEventArgs& e)
	{
		SFM_LOGINFO("FRAMEBUFFER RESIZED!\n");
	}
}

extern "C" MODULE_EXPORT SFM::IGraphicsAPI* __cdecl CreateModule()
{
	return new SFM::VulkanModule();
}