#pragma once

namespace SFM
{
	/// <summary>
	/// Wrapper class used to create the Vulkan frame buffer objects.
	/// </summary>
	struct VulkanFrameBuffer final
	{
		friend class VulkanFrameBufferLoader;

		const uint32_t Width;
		const uint32_t Height;
		const uint32_t LayerCount;

		VulkanFrameBuffer(uint32_t width, uint32_t height, uint32_t layerCount) :
			Width(width),
			Height(height),
			LayerCount(layerCount)
		{}

		void SetRenderPass(vk::RenderPass renderPass, const vk::ImageView* attachments, uint32_t attachmentCount)
		{
			m_renderPass = renderPass;

			m_attachments.reserve(attachmentCount);
			for (size_t i = 0; i < attachmentCount; ++i)
			{
				m_attachments.push_back(&attachments[i]);
			}
		}

		vk::RenderPass GetRenderPass() const 
		{
			return m_renderPass;
		}

		const vk::ImageView& GetImageView(int index) const
		{
			return *m_attachments[index];
		}

		vk::Framebuffer& Get() 
		{
			return m_handle;
		}

		vk::Framebuffer& operator()()
		{
			return m_handle;
		}

	private:
		vk::RenderPass m_renderPass;
		std::vector<const vk::ImageView*> m_attachments;
		vk::Framebuffer m_handle;
	};

	using VulkanFrameBufferHandle = entt::resource_handle<VulkanFrameBuffer>;
	using VulkanFrameBufferCache = entt::resource_cache<VulkanFrameBuffer>;

	/// <summary>
	/// Handles the creation of a frame buffer internally, so the frame buffer can be cached appropriately.
	/// Is used internally by the cache system, should not be used without it.
	/// </summary>
	class VulkanFrameBufferLoader : public entt::resource_loader<VulkanFrameBufferLoader, VulkanFrameBuffer>
	{
	public:
		std::shared_ptr<VulkanFrameBuffer> load(vk::Device& device, const vk::FramebufferCreateInfo& createInfo) const
		{
			std::shared_ptr<VulkanFrameBuffer> vulkanFrameBuffer = std::make_shared<VulkanFrameBuffer>(
				createInfo.width,
				createInfo.height,
				createInfo.layers
			);

			vulkanFrameBuffer->SetRenderPass(createInfo.renderPass, createInfo.pAttachments, createInfo.attachmentCount);
			vulkanFrameBuffer->m_handle = device.createFramebuffer(createInfo);

			return vulkanFrameBuffer;
		};
	};
}