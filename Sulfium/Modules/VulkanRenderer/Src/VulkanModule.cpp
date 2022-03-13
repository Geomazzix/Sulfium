#include "VulkanRenderer/VulkanModule.h"
#include "RenderCore/DLLDefines.h"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace SFM
{
	VulkanModule::VulkanModule() :
		m_selectedPhysicalDevice(INT_MAX)
	{}

	void VulkanModule::Initialize(GraphicsAPICreateInfo&& info)
	{
		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Vulkan boot info:\n");

		m_engine = info.Engine;
		m_GraphicsAPI_Name = "VulkanRenderer";

		m_ctx.Instance.Initialize(m_requiredValidationLayers);

#if defined(WIN32) || defined(WIN64)
		vk::Win32SurfaceCreateInfoKHR createInfo;
		createInfo.hwnd = info.Window;
		createInfo.hinstance = GetModuleHandle(nullptr);

		m_ctx.Surface = m_ctx.Instance().createWin32SurfaceKHR(createInfo);
#endif

		m_ctx.PhysicalDevice = &m_foundPhysicalDevices[SelectPhysicalDevice(m_ctx.Surface)];
		m_ctx.Device.Initialize(m_foundPhysicalDevices[m_selectedPhysicalDevice], m_requiredDeviceExtentions);

		VulkanSwapchainCreateInfo swapChainCreateInfo =
		{
			*m_ctx.PhysicalDevice,
			m_ctx.Device,
			m_ctx.Surface,
			info.FrameBufferWidth,
			info.FrameBufferHeight,
			nullptr
		};

		//#TODO: Move this part to a separate thread.
		m_ctx.SwapChain.Initialize(std::move(swapChainCreateInfo));
		m_cmdBufferPool.Initialize(m_foundPhysicalDevices[m_selectedPhysicalDevice], m_ctx.Device);
		m_cmdBuffers.push_back(VulkanCommandBuffer(m_cmdBufferPool.AllocateCmdBuffer(vk::CommandBufferLevel::ePrimary)));

		SFM_LOGINFO("==========================================");
		SFM_LOGINFO("Vulkan successfully initialized!");
		SFM_LOGINFO("==========================================");
	}

	void VulkanModule::Terminate()
	{
		m_cmdBuffers.clear();
		m_cmdBufferPool.Terminate();

		m_ctx.SwapChain.Terminate();
		m_ctx.Device.Terminate();
		m_ctx.PhysicalDevice = nullptr;

		for (auto& physDevices : m_foundPhysicalDevices)
		{
			physDevices.Terminate();
		}
		m_foundPhysicalDevices.clear();
		m_selectedPhysicalDevice = INT_MAX;

		m_ctx.Instance.Get().destroySurfaceKHR(m_ctx.Surface);
		m_ctx.Instance.Terminate();

		SFM_LOGINFO("Vulkan successfully terminated!");
	}

	void VulkanModule::OnFrameBufferResize(const WindowResizeEventArgs& e)
	{
		VulkanSwapchainCreateInfo swapChainCreateInfo =
		{
			*m_ctx.PhysicalDevice,
			m_ctx.Device,
			m_ctx.Surface,
			e.Width,
			e.Height,
			nullptr
		};

		m_ctx.SwapChain.Recreate(std::move(swapChainCreateInfo));
	}

	int VulkanModule::SelectPhysicalDevice(vk::SurfaceKHR& surface)
	{
		std::vector<vk::PhysicalDevice> physicalDevices = m_ctx.Instance().enumeratePhysicalDevices();
		if (physicalDevices.size() <= 0)
		{
			SFM_LOGCRITICAL("No vulkan supported physical devices found!");
			return -1;
		}

		//Though Vulkan supports simultaneous GPU processing, I chose to not get into this. Since the API is already hard enough to learn by itself.
		m_foundPhysicalDevices.reserve(physicalDevices.size());
		for (int i = 0; i < physicalDevices.size(); i++)
		{
			m_foundPhysicalDevices.push_back(VulkanPhysicalDevice());
			m_foundPhysicalDevices[i].Initialize(physicalDevices[i], surface, m_requiredDeviceExtentions);

			if (m_foundPhysicalDevices[i].DoesSupportExtensions())
			{
				m_selectedPhysicalDevice = i;
				break;
			}
		}

		if (m_selectedPhysicalDevice == INT_MAX)
		{
			SFM_LOGCRITICAL("No suitable GPU can be found!\n");
			return -1;
		}

		return m_selectedPhysicalDevice;
	}
}

extern "C" MODULE_EXPORT SFM::IGraphicsAPI* __cdecl CreateModule()
{
	return new SFM::VulkanModule();
}