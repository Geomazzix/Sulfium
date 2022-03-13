#pragma once
#include "VulkanRenderer/Core/VulkanDevice.h"
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"
#include "VulkanRenderer/Resources/VulkanFramebuffer.h"

#include "VulkanRenderer/Resources/VulkanImage.h"

namespace SFM
{
	struct VulkanSwapchainCreateInfo
	{
		VulkanPhysicalDevice& PhysicalDevice;
		VulkanDevice& Device;
		vk::SurfaceKHR& Surface;
		int FrameBufferWidthInPx;
		int FrameBufferHeightInPx;
		vk::RenderPass RenderPass;
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

		void DestroyInternals();

		void CreateSwapChain(VulkanSwapchainCreateInfo& info);
		void CreateImageViews(VulkanDevice& device);
		void CreateFrameBuffers(VulkanDevice& device, vk::RenderPass& renderPass);

		vk::SwapchainKHR m_swapchain;
		vk::Format m_swapChainFormat;
		vk::Extent2D m_swapChainExtent;

		std::vector<vk::Image> m_swapChainImages; //Don't use Vulkan image when you can't identify the image.
		std::vector<VulkanImageViewHandle> m_swapChainImageViews;
		std::vector<VulkanFrameBufferHandle> m_swapChainFrameBuffers;

		const std::string m_swapchainImageViewName = "SwapchainImageView_";
		const std::string m_swapchainFrameBufferName= "SwapChainFrameBuffer_";

		VulkanDevice* m_device;
	};
}