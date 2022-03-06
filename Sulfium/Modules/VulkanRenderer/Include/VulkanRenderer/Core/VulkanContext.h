#pragma once
#include "VulkanRenderer/Core/VulkanInstance.h"
#include "VulkanRenderer/Core/VulkanDevice.h"
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"
#include "VulkanRenderer/Core/VulkanSwapchain.h"

namespace SFM
{
	/// <summary>
	/// Holds accessibility to the core concepts of the Vulkan API.
	/// </summary>
	struct VulkanContext
	{
		VulkanInstance Instance;
		VulkanPhysicalDevice* PhysicalDevice;
		VulkanDevice Device;
		
		vk::SurfaceKHR Surface;
		VulkanSwapchain SwapChain;
	};
}