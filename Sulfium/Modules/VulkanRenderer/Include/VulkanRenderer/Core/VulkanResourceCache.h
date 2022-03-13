#pragma once
#include "VulkanRenderer/Resources/VulkanImage.h"
#include "VulkanRenderer/Resources/VulkanFramebuffer.h"

namespace SFM
{
	using VulkanResourceId = entt::hashed_string;

	/// <summary>
	/// Holds all the resource lookup tables for the Vulkan renderer's resources.
	/// #TODO: EnTT didn't provide any performance measurements on this topic, therefore profiling on
	/// benchmark scenes is adviced!
	/// </summary>
	struct VulkanResourceCache
	{
		VulkanImageCache ImageCache;
		VulkanImageViewCache ImageViewCache;
		VulkanFrameBufferCache FrameBufferCache;
	};
}