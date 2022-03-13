#include "VulkanRenderer/SceneGraph/VulkanRenderPass.h"
#include "VulkanRenderer/Core/VulkanDevice.h"

namespace SFM
{
	/*void VulkanRenderPass::Initialize(VulkanDevice& device)
	{
		vk::AttachmentDescription colorAttachmentDescription =
		{
			vk::AttachmentDescriptionFlags(),
			m_SwapChainFormat,
			vk::SampleCountFlagBits::e1,
			vk::AttachmentLoadOp::eClear,		//Stencil
			vk::AttachmentStoreOp::eStore,
			vk::AttachmentLoadOp::eDontCare,	//Depth
			vk::AttachmentStoreOp::eDontCare,
			vk::ImageLayout::eUndefined,
			vk::ImageLayout::ePresentSrcKHR,
		};

		vk::AttachmentReference colorAttachmentRef =
		{
			0,
			vk::ImageLayout::eColorAttachmentOptimal
		};

		vk::SubpassDescription subpassDescription =
		{
			vk::SubpassDescriptionFlags(),
			vk::PipelineBindPoint::eGraphics,
			0,
			nullptr,
			1,
			&colorAttachmentRef,
		};

		vk::SubpassDependency dependency =
		{
			VK_SUBPASS_EXTERNAL,
			0,
			vk::PipelineStageFlags(vk::PipelineStageFlagBits::eColorAttachmentOutput),
			vk::PipelineStageFlags(vk::PipelineStageFlagBits::eColorAttachmentOutput),
			vk::AccessFlags(),
			vk::AccessFlags(vk::AccessFlagBits::eColorAttachmentWrite),
			vk::DependencyFlags()
		};

		vk::RenderPassCreateInfo renderPassCreateInfo =
		{
			vk::RenderPassCreateFlags(),
			1,
			&colorAttachmentDescription,
			1,
			&subpassDescription,
			1,
			&dependency
		};
		m_renderPass = device.createRenderPass(renderPassCreateInfo);
	}*/
}