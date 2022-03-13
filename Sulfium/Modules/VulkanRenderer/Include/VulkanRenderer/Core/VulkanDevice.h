#pragma once
#include "VulkanRenderer/Core/VulkanQueueFamilyIndices.h"
#include "VulkanRenderer/Core/VulkanSwapChainRenderTargetInfo.h"
#include "VulkanRenderer/Core/VulkanResourceCache.h"

namespace SFM
{
	class VulkanResourceCache;
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
		VulkanDevice();
		~VulkanDevice();
		
		void Initialize(VulkanPhysicalDevice& physDevice, const std::vector<const char*>& extensions);
		void Terminate();

		vk::Queue& GetQueue(EDeviceQueue queue);
		vk::Device& operator()();
		vk::Device& Get();

		VulkanFrameBufferHandle CreateVulkanFrameBuffer(const VulkanResourceId& id, const vk::FramebufferCreateInfo& createInfo);
		void DestroyVulkanFrameBuffer(const VulkanResourceId& id);

		VulkanImageHandle CreateVulkanImage(const VulkanResourceId& id, const vk::ImageCreateInfo& createInfo, vk::MemoryPropertyFlags memProps);
		void DestroyVulkanImage(const VulkanResourceId& id);

		VulkanImageViewHandle CreateImageView(const VulkanResourceId& id, const vk::ImageViewCreateInfo& createInfo);
		void DestroyImageView(const VulkanResourceId& id);

	private:
		uint32_t FindMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags memProps);

		VulkanPhysicalDevice* m_physicalDevice;
		vk::Device m_device;
		VulkanResourceCache m_resourceCache;

		std::vector<vk::Queue> m_queues;
	};
}