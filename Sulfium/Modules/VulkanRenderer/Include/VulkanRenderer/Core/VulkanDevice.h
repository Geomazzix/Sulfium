#pragma once
#include "VulkanRenderer/Core/VulkanQueueFamilyIndices.h"
#include "VulkanRenderer/Core/VulkanSwapChainRenderTargetInfo.h"

namespace SFM
{
	class VulkanPhysicalDevice;

	/// <summary>
	/// Used to identify the queues of the vulkan device.
	/// </summary>
	enum EDeviceQueue
	{
		Graphics = 0,
		Presentation
	};

	/// <summary>
	/// A wrapper class used to access the vulkan device properties.
	/// </summary>
	class VulkanDevice
	{
	public:
		VulkanDevice() = default;
		~VulkanDevice() = default;
		
		void Initialize(VulkanPhysicalDevice& physDevice, const std::vector<const char*>& extensions);
		void Terminate();

		vk::Queue& GetQueue(EDeviceQueue queue);
		vk::Device& operator()();
		vk::Device& Get();

	private:
		vk::Device m_device;

		std::vector<vk::Queue> m_queues;
	};
}