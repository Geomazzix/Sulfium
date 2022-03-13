#include "VulkanRenderer/CommandBuffers/VulkanCommandBuffer.h"

namespace SFM
{
	VulkanCommandBuffer::VulkanCommandBuffer(vk::CommandBuffer& buffer) :
		m_commandBuffer(buffer)
	{}

	vk::CommandBuffer& VulkanCommandBuffer::operator()()
	{
		return m_commandBuffer;
	}

	vk::CommandBuffer& VulkanCommandBuffer::Get()
	{
		return m_commandBuffer;
	}

	void VulkanCommandBuffer::Begin(VulkanCmdBufferBeginInfo&& beginInfo)
	{
		m_renderPass = beginInfo.RenderPass;
		m_subPass = beginInfo.SubPass;
		m_frameBuffer = beginInfo.FrameBuffer;

		m_occlusionQueryEnabled = beginInfo.OcclusionQueryEnabled;
		m_occlusionQueryFlags = beginInfo.OcclusionQueryFlags;

#if _DEBUG
		m_pipelineStatistics = beginInfo.PipelineStatistics;
#endif

		vk::CommandBufferInheritanceInfo inheritanceInfo = nullptr;
		if (m_level == vk::CommandBufferLevel::eSecondary)
		{
			inheritanceInfo =
			{
				m_renderPass,
				m_subPass,
				m_frameBuffer,
				m_occlusionQueryEnabled,
				m_occlusionQueryFlags,
				m_pipelineStatistics
			};
		}

		vk::CommandBufferBeginInfo info =
		{
			beginInfo.Usage,
			&inheritanceInfo
		};

		m_commandBuffer.begin(info);
	}

	void VulkanCommandBuffer::End()
	{
		m_commandBuffer.end();
	}
}