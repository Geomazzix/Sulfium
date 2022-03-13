#pragma once

namespace SFM
{
	class VulkanPhysicalDevice;
	class VulkanDevice;


	/// <summary>
	/// Serves as a wrapper for the Vulkan command buffer pool.
	/// Note: Unsafe for multi threading, when using make sure to allocate on the operating thread.
	/// </summary>
	class VulkanCommandBufferPool
	{
	public:
		VulkanCommandBufferPool() = default;
		~VulkanCommandBufferPool() = default;

		void Initialize(VulkanPhysicalDevice& physicalDevice, VulkanDevice& device);
		void Terminate();
		void Reset(vk::CommandPoolResetFlags flags = {} /*Default param in Vulkan seems to accept empty.*/);

		vk::CommandBuffer& AllocateCmdBuffer(vk::CommandBufferLevel cmdLevel);
		vk::CommandBuffer* AllocateCmdBuffers(vk::CommandBufferLevel cmdLevel, uint32_t count);
		void FreeCmdBuffers(vk::CommandBuffer& cmdBuffer);

	private:
		VulkanDevice* m_device;
		vk::CommandPool m_cmdPool;

		std::vector<vk::CommandBuffer> m_primaryBuffers;
		std::vector<vk::CommandBuffer> m_secondaryBuffers;
	};
}