#pragma once
#include "RenderCore/IGraphicsAPI.h"
#include "ApplicationCore/Window/WindowEventArgs.h"

#include "VulkanRenderer/Core/VulkanInstance.h"
#include "VulkanRenderer/Core/VulkanDevice.h"
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"

namespace SFM
{
	/// <summary>
	/// Holds accessibility to the core elements of the Vulkan API.
	/// </summary>
	struct VulkanContext
	{
		VulkanInstance Instance;
		VulkanPhysicalDevice* PhysicalDevice;
		VulkanDevice Device;
		vk::SurfaceKHR Surface;
	};

	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class VulkanModule final : public IGraphicsAPI
	{
	public:
		VulkanModule();
		~VulkanModule() = default;

		void Initialize(std::weak_ptr<Engine> engine, WindowHandle windowHandle) override;
		void Terminate() override;

		void OnFrameBufferResize(const WindowResizeEventArgs& e) override;
		
	private:
		int SelectPhysicalDevice(vk::SurfaceKHR& surface);

		std::weak_ptr<Engine> m_engine;
	
		std::vector<VulkanPhysicalDevice> m_foundPhysicalDevices;
		int m_selectedPhysicalDevice;

		VulkanContext m_ctx;

		const std::vector<const char*> m_requiredDeviceExtentions =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		const std::vector<const char*> m_validationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};
	};
}