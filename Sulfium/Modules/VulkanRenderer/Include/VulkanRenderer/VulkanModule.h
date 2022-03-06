#pragma once
#include "RenderCore/IGraphicsAPI.h"
#include "ApplicationCore/Window/WindowEventArgs.h"
#include "VulkanRenderer/Core/VulkanContext.h"

namespace SFM
{
	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class VulkanModule final : public IGraphicsAPI
	{
	public:
		VulkanModule();
		~VulkanModule() = default;

		void Initialize(GraphicsAPICreateInfo&& info) override;
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