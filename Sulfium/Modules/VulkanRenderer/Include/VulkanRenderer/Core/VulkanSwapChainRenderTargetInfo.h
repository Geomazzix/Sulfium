#pragma once

namespace SFM
{
	/// <summary>
	/// Contains the image format and capabilities of the swapchain buffer.
	/// </summary>
	struct SwapChainRenderTargetInfo
	{
		vk::SurfaceCapabilitiesKHR Capabilities;
		std::vector<vk::SurfaceFormatKHR> Formats;
		std::vector<vk::PresentModeKHR> PresentationModes;
	};
}