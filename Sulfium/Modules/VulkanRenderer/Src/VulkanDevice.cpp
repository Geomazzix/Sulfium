#include "VulkanRenderer/Core/VulkanDevice.h"
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"

namespace SFM
{
	VulkanDevice::VulkanDevice() :
		m_physicalDevice(nullptr)
	{}

	VulkanDevice::~VulkanDevice()
	{
		m_physicalDevice = nullptr;
	}

	void VulkanDevice::Initialize(VulkanPhysicalDevice& physDevice, const std::vector<const char*>& extensions)
	{
		m_physicalDevice = &physDevice;

		QueueFamilyIndices deviceQueueFamilyIndices = physDevice.FindGraphicsDisplayQueueFamily();

		float queuePriority = 1.0f;
		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies =
		{
			deviceQueueFamilyIndices.GraphicsFamily.value(),
			deviceQueueFamilyIndices.PresentationFamily.value()
		};

		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			queueCreateInfos.emplace_back(vk::DeviceQueueCreateFlags(), queueFamily, 1, &queuePriority);
		}

		vk::PhysicalDeviceFeatures physcDeviceFeatures{};
		vk::DeviceCreateInfo deviceCreateInfo =
		{
			vk::DeviceCreateFlags(),
			static_cast<uint32_t>(queueCreateInfos.size()),
			queueCreateInfos.data(),
			static_cast<uint32_t>(0),
			{},
			static_cast<uint32_t>(extensions.size()),
			extensions.data(),
			&physcDeviceFeatures
		};

		m_device = physDevice().createDevice(deviceCreateInfo);
		VULKAN_HPP_DEFAULT_DISPATCHER.init(m_device);

		//Query the queues from the logical device, though when the graphical and presentation have the same index, just use one of them, since they both draw graphics.
		m_queues.reserve(2);
		m_queues.push_back(m_device.getQueue(deviceQueueFamilyIndices.GraphicsFamily.value(), 0));
		m_queues.push_back(m_device.getQueue(deviceQueueFamilyIndices.PresentationFamily.value(), 0));
	}

	void VulkanDevice::Terminate()
	{
		m_device.destroy();
	}

	vk::Queue& VulkanDevice::GetQueue(EDeviceQueue queue)
	{
		return m_queues[queue];
	}

	vk::Device& VulkanDevice::operator()()
	{
		return m_device;
	}

	vk::Device& VulkanDevice::Get()
	{
		return m_device;
	}

	VulkanFrameBufferHandle VulkanDevice::CreateVulkanFrameBuffer(const VulkanResourceId& id, const vk::FramebufferCreateInfo& createInfo)
	{
		return m_resourceCache.FrameBufferCache.load<VulkanFrameBufferLoader>(id, m_device, createInfo);
	}

	void VulkanDevice::DestroyVulkanFrameBuffer(const VulkanResourceId& id)
	{
		SFM_ASSERT(m_resourceCache.FrameBufferCache.contains(id));
		
		auto& frameBuffer = m_resourceCache.FrameBufferCache.handle(id);
		m_device.destroyFramebuffer(frameBuffer->Get());
		m_resourceCache.FrameBufferCache.discard(id);
	}

	VulkanImageHandle VulkanDevice::CreateVulkanImage(const VulkanResourceId& id, const vk::ImageCreateInfo& createInfo, vk::MemoryPropertyFlags memProps)
	{
		return m_resourceCache.ImageCache.load<VulkanImageLoader>(id, m_device, *m_physicalDevice, createInfo, memProps);;
	}

	void VulkanDevice::DestroyVulkanImage(const VulkanResourceId& id)
	{
		SFM_ASSERT(m_resourceCache.ImageCache.contains(id));
		auto& image = m_resourceCache.ImageCache.handle(id);

		m_device.freeMemory(image->GetMemory());
		m_device.destroyImage(image->GetHandle());
	
		m_resourceCache.ImageCache.discard(id);
	}

	VulkanImageViewHandle VulkanDevice::CreateImageView(const VulkanResourceId& id, const vk::ImageViewCreateInfo& createInfo)
	{
		return m_resourceCache.ImageViewCache.load<VulkanImageViewLoader>(id, m_device, createInfo);
	}

	void VulkanDevice::DestroyImageView(const VulkanResourceId& id)
	{
		SFM_ASSERT(m_resourceCache.ImageViewCache.contains(id));
		auto& imageView = m_resourceCache.ImageViewCache.handle(id);

		m_device.destroyImageView(imageView->GetHandle());
		m_resourceCache.ImageViewCache.discard(id);
	}
}