#include "VulkanRenderer/Core/VulkanDevice.h"
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"

namespace SFM
{
	void VulkanDevice::Initialize(VulkanPhysicalDevice& physDevice, const std::vector<const char*>& extensions)
	{
		QueueFamilyIndices deviceQueueFamilyIndices = physDevice.FindGraphicsDisplayQueueFamily();

		float queuePriority = 1.0f;
		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies =
		{
			deviceQueueFamilyIndices.GraphicsFamily.value(),
			deviceQueueFamilyIndices.PresentationFamily.value()
		};

		for (uint32_t queueFamily : uniqueQueueFamilies)
			queueCreateInfos.emplace_back(vk::DeviceQueueCreateFlags(), queueFamily, 1, &queuePriority);

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
}