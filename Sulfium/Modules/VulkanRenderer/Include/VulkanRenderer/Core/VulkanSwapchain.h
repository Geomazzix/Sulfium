#pragma once
#include "VulkanRenderer/Core/VulkanDevice.h"
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"

namespace SFM
{
	class VulkanContext;

	struct VulkanSwapchainCreateInfo
	{
		VulkanPhysicalDevice& PhysicalDevice;
		VulkanDevice& Device;
		vk::SurfaceKHR& Surface;
		int FrameBufferWidthInPx;
		int FrameBufferHeightInPx;
	};

	/// <summary>
	/// Resembles a wrapper for the swapchain and the render targets for the swapchain.
	/// </summary>
	class VulkanSwapchain
	{
	public:
		VulkanSwapchain();
		~VulkanSwapchain() = default;

		void Initialize(VulkanSwapchainCreateInfo&& info);
		void Terminate();

		void Recreate(VulkanSwapchainCreateInfo&& info);

	private:
		vk::SurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
		vk::PresentModeKHR ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes);
		vk::Extent2D ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities, int frameBufferWidth, int frameBufferHeight);

		void CreateSwapChain(VulkanSwapchainCreateInfo& info);
		void DestroySwapChain();
		void CreateImageViews(VulkanDevice& device);

		vk::SwapchainKHR m_swapchain;
		vk::Format m_swapChainFormat;
		vk::Extent2D m_swapChainExtent;

		std::vector<vk::Image> m_swapChainImages;
		std::vector<vk::ImageView> m_swapChainImageViews;
		std::vector<vk::Framebuffer> m_swapChainFrameBuffers;

		VulkanDevice* m_device;
	};
}