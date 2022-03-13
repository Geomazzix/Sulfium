#include "VulkanRenderer/CommandBuffers/VulkanCommandBufferPool.h"
#include "VulkanRenderer/Core/VulkanQueueFamilyIndices.h"
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"
#include "VulkanRenderer/Core/VulkanDevice.h"

namespace SFM
{
	void VulkanCommandBufferPool::Initialize(VulkanPhysicalDevice& physicalDevice, VulkanDevice& device)
	{
		m_device = &device;

		QueueFamilyIndices queuefamilyIndices = physicalDevice.FindGraphicsDisplayQueueFamily();

		vk::CommandPoolCreateInfo poolInfo =
		{
			vk::CommandPoolCreateFlags(),
			queuefamilyIndices.GraphicsFamily.value()
		};

		m_cmdPool = m_device->Get().createCommandPool(poolInfo);
	}

	void VulkanCommandBufferPool::Terminate()
	{
		m_device->Get().destroyCommandPool(m_cmdPool);
	}

	void VulkanCommandBufferPool::Reset(vk::CommandPoolResetFlags flags /*= {}*/)
	{
		m_device->Get().resetCommandPool(m_cmdPool);
	}

	vk::CommandBuffer& VulkanCommandBufferPool::AllocateCmdBuffer(vk::CommandBufferLevel cmdLevel)
	{
		vk::CommandBufferAllocateInfo info =
		{
			m_cmdPool,
			cmdLevel,
			1
		};

		vk::CommandBuffer& cmdBuffer = *m_device->Get().allocateCommandBuffers(info).data();

		if (cmdLevel == vk::CommandBufferLevel::ePrimary)
		{
			m_primaryBuffers.push_back(cmdBuffer);
			return m_primaryBuffers[m_primaryBuffers.size() - 1];
		}
			
		m_secondaryBuffers.push_back(cmdBuffer);
		return m_secondaryBuffers[m_primaryBuffers.size() - 1];
	}

	vk::CommandBuffer* VulkanCommandBufferPool::AllocateCmdBuffers(vk::CommandBufferLevel cmdLevel, uint32_t count)
	{
		vk::CommandBufferAllocateInfo info =
		{
			m_cmdPool,
			cmdLevel,
			count
		};

		std::vector<vk::CommandBuffer> cmdbuffers = m_device->Get().allocateCommandBuffers(info);
		int cmdBufferCount = 0;

		if (cmdLevel == vk::CommandBufferLevel::ePrimary)
		{
			cmdBufferCount = m_primaryBuffers.size() - 1;
			for (auto& cmdBuffer : cmdbuffers)
			{
				m_primaryBuffers.push_back(cmdBuffer);
			}
			return &m_primaryBuffers[cmdBufferCount];
		}

		cmdBufferCount = m_secondaryBuffers.size() - 1;
		for (auto& cmdBuffer : cmdbuffers)
		{
			m_secondaryBuffers.push_back(cmdBuffer);
		}
		return &m_secondaryBuffers[cmdBufferCount];
	}

	void VulkanCommandBufferPool::FreeCmdBuffers(vk::CommandBuffer& cmdBuffer)
	{
		m_device->Get().freeCommandBuffers(m_cmdPool, 1, &cmdBuffer);
	}
}