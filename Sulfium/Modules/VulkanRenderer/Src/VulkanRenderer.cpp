#include "VulkanRenderer.h"

namespace SFM
{
	VulkanRenderer::VulkanRenderer()
	{
		Initialize();
	}

	VulkanRenderer::~VulkanRenderer()
	{
		Terminate();
	}

	void VulkanRenderer::Initialize()
	{
		somevalue = 1;
	}

	void VulkanRenderer::Terminate()
	{
		somevalue = 0;
	}

}