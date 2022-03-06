#include "VulkanRenderer/Core/VulkanSwapchain.h"
#include "VulkanRenderer/Core/VulkanContext.h"

namespace SFM
{
	VulkanSwapchain::VulkanSwapchain() :
		m_swapchain(nullptr)
	{}

	void VulkanSwapchain::Initialize(VulkanSwapchainCreateInfo&& info)
	{
		m_device = &info.Device;

		CreateSwapChain(info);
		CreateImageViews(info.Device);
	}

	void VulkanSwapchain::Terminate()
	{
		DestroySwapChain();
	}

	void VulkanSwapchain::Recreate(VulkanSwapchainCreateInfo&& info)
	{
		DestroySwapChain();
		CreateSwapChain(info);
	}

	void VulkanSwapchain::CreateSwapChain(VulkanSwapchainCreateInfo& info)
	{
		SFM::SwapChainRenderTargetInfo swapChainSupport = info.PhysicalDevice.QuerySwapChainRenderTargetSupport();

		vk::SurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.Formats);
		vk::PresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.PresentationModes);
		vk::Extent2D extents = ChooseSwapExtent(swapChainSupport.Capabilities, info.FrameBufferWidthInPx, info.FrameBufferHeightInPx);

		uint32_t imageCount = swapChainSupport.Capabilities.minImageCount + 1; //Request 1 more image to make sure that the driver doesn't have any waiting intervals.

		//Check if the image count does not exceed the maximum allowed images within the chain swap buffer, if so clamp it to it.
		if (swapChainSupport.Capabilities.maxImageCount > 0 && imageCount > swapChainSupport.Capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.Capabilities.maxImageCount;
		}

		QueueFamilyIndices indices = info.PhysicalDevice.FindGraphicsDisplayQueueFamily();
		uint32_t queueFamilyIndices[] =
		{
			indices.GraphicsFamily.value(),
			indices.PresentationFamily.value()
		};

		vk::SwapchainCreateInfoKHR swapChainCreateInfo =
		{
			vk::SwapchainCreateFlagsKHR(),
			info.Surface,
			imageCount,
			surfaceFormat.format,
			surfaceFormat.colorSpace,
			extents,
			1,
			vk::ImageUsageFlagBits::eColorAttachment, //This could be changed depending on the usage, i.e. Transfer_Dst should be used to post processing.
			vk::SharingMode::eExclusive,
			0,
			nullptr,
			swapChainSupport.Capabilities.currentTransform,
			vk::CompositeAlphaFlagBitsKHR::eOpaque, //Just ignore the alpha channel.
			presentMode,
			VK_TRUE, //Clips pixels away when another window hovers in front of it.
			m_swapchain
		};

		//When using 2 instead of 1 graphics buffer make sure to change the mode to concurrent.
		if (indices.GraphicsFamily != indices.PresentationFamily)
		{
			swapChainCreateInfo.setImageSharingMode(vk::SharingMode::eConcurrent);
			swapChainCreateInfo.setQueueFamilyIndexCount(2);
			swapChainCreateInfo.setPQueueFamilyIndices(queueFamilyIndices);
		}

		m_swapchain = info.Device().createSwapchainKHR(swapChainCreateInfo);
		m_swapChainImages = info.Device().getSwapchainImagesKHR(m_swapchain);
		m_swapChainExtent = extents;
		m_swapChainFormat = surfaceFormat.format;
	}

	void VulkanSwapchain::DestroySwapChain()
	{
		for (auto& imageView : m_swapChainImageViews)
		{
			m_device->Get().destroyImageView(imageView);
		}

		m_swapChainImageViews.clear();
		m_swapChainImages.clear();

		m_device->Get().destroySwapchainKHR();
	}

	vk::SurfaceFormatKHR VulkanSwapchain::ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats)
	{
		//Will try to filter out the most optimal swapchain format. Implement ranking in other formats when needed.
		for (const auto& format : availableFormats)
		{
			if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eVkColorspaceSrgbNonlinear)
				return format;
		}

		return availableFormats[0];
	}

	vk::PresentModeKHR VulkanSwapchain::ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes)
	{
		for (const auto& presentMode : availablePresentModes)
		{
			if (presentMode == vk::PresentModeKHR::eMailbox) //triple buffering.
				return presentMode;
		}

		return vk::PresentModeKHR::eFifo;	//Double buffering (vsync).
	}

	vk::Extent2D VulkanSwapchain::ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities, int frameBufferWidth, int frameBufferHeight)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			return capabilities.currentExtent;
		}
		else
		{
			vk::Extent2D actualExtent =
			{
				static_cast<uint32_t>(frameBufferWidth),
				static_cast<uint32_t>(frameBufferHeight)
			};

			return actualExtent;
		}
	}

	void VulkanSwapchain::CreateImageViews(VulkanDevice& device)
	{
		m_swapChainImageViews.reserve(m_swapChainImages.size());
		for (int i = 0; i < m_swapChainImages.size(); i++)
		{
			vk::ImageViewCreateInfo imageViewCreateInfo =
			{
				vk::ImageViewCreateFlags(),
				m_swapChainImages[i],
				vk::ImageViewType::e2D,
				m_swapChainFormat,
				vk::ComponentMapping(
					vk::ComponentSwizzle::eIdentity,
					vk::ComponentSwizzle::eIdentity,
					vk::ComponentSwizzle::eIdentity,
					vk::ComponentSwizzle::eIdentity),
				vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1)
			};

			m_swapChainImageViews.emplace_back(device().createImageView(imageViewCreateInfo));
		}
	}
}