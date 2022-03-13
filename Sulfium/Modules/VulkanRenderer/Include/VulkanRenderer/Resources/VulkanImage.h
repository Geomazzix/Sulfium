#pragma once
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"

namespace SFM
{
	/// <summary>
	/// Contains all the image data an image Vulkan can consist of,
	/// useful when creating an image view that needs to align with the
	/// image format and size.
	/// </summary>
	struct VulkanImage
	{
		friend class VulkanImageLoader;

		const vk::ImageType ImageType;
		const vk::Format Format;
		const vk::Extent3D Extent;

		const uint32_t MipLevels;
		const uint32_t ArrayLayers;

		const vk::SampleCountFlags SampleRate;
		const vk::ImageTiling Tiling;
		const vk::ImageUsageFlags Usage;
		const vk::ImageLayout Layout;
	
		VulkanImage(vk::ImageType imageType, vk::Format format, vk::Extent3D extent, uint32_t mipLevels, uint32_t arrayLayers, 
			vk::SampleCountFlags sampleRate, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::ImageLayout layout) :
			ImageType(imageType),
			Format(format),
			Extent(extent),
			MipLevels(mipLevels),
			ArrayLayers(arrayLayers),
			SampleRate(sampleRate),
			Tiling(tiling),
			Usage(usage),
			Layout(layout)
		{}
		~VulkanImage() = default;

		vk::Image& GetHandle()
		{
			return m_handle;
		}

		vk::DeviceMemory& GetMemory()
		{
			return m_memory;
		}

	private:
		vk::Image m_handle;
		vk::DeviceMemory m_memory;
	};

	/// <summary>
	/// Wrapper for the vk::Image view.
	/// Creates a link to the image itself, and has small utility to access it.
	/// </summary>
	struct VulkanImageView
	{
		friend class VulkanImageViewLoader;

		const vk::Format ImageFormat;
		const vk::ImageViewType ViewType;
		const vk::ComponentMapping Components;
		const vk::ImageSubresourceRange SubResourceRange;

		VulkanImageView(vk::Format imageFormat, vk::ImageViewType viewType, const vk::ComponentMapping& comps, const vk::ImageSubresourceRange& subResRange) :
			ImageFormat(imageFormat),
			ViewType(viewType),
			Components(comps),
			SubResourceRange(subResRange)
		{}

		vk::ImageView& GetHandle()
		{
			return m_handle;
		}

	private:
		vk::ImageView m_handle;
	};

	//Define the image caches, used in the resource cache.
	using VulkanImageCache = entt::resource_cache<VulkanImage>;
	using VulkanImageViewCache = entt::resource_cache<VulkanImageView>;

	using VulkanImageHandle = entt::resource_handle<VulkanImage>;
	using VulkanImageViewHandle = entt::resource_handle<VulkanImageView>;

	/// <summary>
	/// The image loader is responsible for the creation of an image.
	/// </summary>
	class VulkanImageLoader final : public entt::resource_loader<VulkanImageLoader, VulkanImage>
	{
	public:
		std::shared_ptr<VulkanImage> load(vk::Device& device, VulkanPhysicalDevice& physicalDevice, const vk::ImageCreateInfo& info, vk::MemoryPropertyFlags memProps) const
		{
			vk::Image image = device.createImage(info);

			//#TODO: Implement a memory manager that takes care of allocation and freeing of the Vulkan memory.
			vk::MemoryRequirements memReq = device.getImageMemoryRequirements(image);
			vk::MemoryAllocateInfo allocationInfo =
			{
				memReq.size,
				physicalDevice.FindMemoryType(memReq.memoryTypeBits, memProps)
			};

			std::shared_ptr<VulkanImage> vulkanImage = std::make_shared<VulkanImage>(
				info.imageType,
				info.format,
				info.extent,

				info.mipLevels,
				info.arrayLayers,

				info.samples,
				info.tiling,
				info.usage,
				info.initialLayout
			);

			vulkanImage->m_handle = image;
			vulkanImage->m_memory = device.allocateMemory(allocationInfo);
			
			return vulkanImage;
		};
	};

	/// <summary>
	/// The image view loader is responsible for the creation of an image view.
	/// </summary>
	class VulkanImageViewLoader final : public entt::resource_loader<VulkanImageViewLoader, VulkanImageView>
	{
	public:
		std::shared_ptr<VulkanImageView> load(vk::Device& device, const vk::ImageViewCreateInfo& createInfo) const
		{
			std::shared_ptr<VulkanImageView> imageView = std::make_shared<VulkanImageView>(
				createInfo.format,
				createInfo.viewType,
				createInfo.components,
				createInfo.subresourceRange
			);

			imageView->m_handle = device.createImageView(createInfo);

			return imageView;
		};
	};
}