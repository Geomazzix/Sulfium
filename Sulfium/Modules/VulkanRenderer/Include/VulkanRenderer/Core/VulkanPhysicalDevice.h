#pragma once
#include "VulkanRenderer/Core/VulkanQueueFamilyIndices.h"
#include "VulkanRenderer/Core/VulkanSwapChainRenderTargetInfo.h"

namespace SFM
{
	/// <summary>
	/// A wrapper class used to access the vulkan physical device properties.
	/// </summary>
	class VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice() = default;
		~VulkanPhysicalDevice() = default;

		void Initialize(vk::PhysicalDevice& physicalDevice, vk::SurfaceKHR& surface, const std::vector<const char*>& extensions);
		void Terminate();

		bool DoesSupportExtensions();
		SwapChainRenderTargetInfo QuerySwapChainRenderTargetSupport() const;
		QueueFamilyIndices FindGraphicsDisplayQueueFamily();

		vk::PhysicalDevice& operator()();

	private:
		bool IsSwapChainCompatible() const;
		void LogPhysicalDeviceInfo();

		std::vector<const char*> m_extensions;

		QueueFamilyIndices m_selectedQueueFamily;
		std::vector<vk::QueueFamilyProperties> m_queueFamilies;
		vk::PhysicalDevice m_physicalDevice;
		vk::SurfaceKHR m_surface;
	};
}