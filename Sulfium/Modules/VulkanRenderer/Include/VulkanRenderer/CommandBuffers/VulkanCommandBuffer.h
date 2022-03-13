#pragma once

namespace SFM
{
	struct VulkanCmdBufferBeginInfo
	{
		vk::CommandBufferUsageFlags Usage;
		vk::RenderPass RenderPass;
		uint32_t SubPass;
		vk::Framebuffer FrameBuffer;
		vk::Bool32 OcclusionQueryEnabled;
		vk::QueryControlFlags OcclusionQueryFlags;
#if _DEBUG
		vk::QueryPipelineStatisticFlags PipelineStatistics;
#endif
	};

	/// <summary>
	/// Wrapper for the Vulkan command buffer class.
	/// </summary>
	class VulkanCommandBuffer
	{
	public:
		VulkanCommandBuffer(vk::CommandBuffer& buffer);
		~VulkanCommandBuffer() = default;

		vk::CommandBuffer& operator()();
		vk::CommandBuffer& Get();

		void Begin(VulkanCmdBufferBeginInfo&& beginInfo);
		void End();

	private:
		vk::CommandBuffer& m_commandBuffer;
		vk::CommandBufferLevel m_level;

		vk::RenderPass m_renderPass;
		uint32_t m_subPass;
		vk::Framebuffer m_frameBuffer;
		
		vk::Bool32 m_occlusionQueryEnabled;
		vk::QueryControlFlags m_occlusionQueryFlags;

#if _DEBUG
		vk::QueryPipelineStatisticFlags m_pipelineStatistics;
#endif
	};
}