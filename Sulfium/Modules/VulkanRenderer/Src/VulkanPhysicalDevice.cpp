#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"
#include "VulkanRenderer/Core/VulkanQueueFamilyIndices.h"

namespace SFM
{
	void VulkanPhysicalDevice::Initialize(vk::PhysicalDevice& physicalDevice, vk::SurfaceKHR& surface, const std::vector<const char*>& extensions)
	{
		m_physicalDevice = physicalDevice;
		m_surface = surface;
		m_extensions = extensions;
	}

	void VulkanPhysicalDevice::Terminate()
	{
		m_queueFamilies.clear();
		m_selectedQueueFamily.GraphicsFamily = 0;
		m_selectedQueueFamily.PresentationFamily = 0;
	}

	bool VulkanPhysicalDevice::DoesSupportExtensions()
	{
		m_selectedQueueFamily = FindGraphicsDisplayQueueFamily();
		bool extensionsSupported = IsSwapChainCompatible();

#if _DEBUG
		LogPhysicalDeviceInfo();
#endif

		return m_selectedQueueFamily.IsFilled() && extensionsSupported;
	}

	SFM::QueueFamilyIndices VulkanPhysicalDevice::FindGraphicsDisplayQueueFamily()
	{
		QueueFamilyIndices indices;
		m_queueFamilies = m_physicalDevice.getQueueFamilyProperties();

		for (int i = 0; i < m_queueFamilies.size(); i++)
		{
			if (m_queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
			{
				indices.GraphicsFamily = i;
			}

			if (m_physicalDevice.getSurfaceSupportKHR(i, m_surface))
			{
				indices.PresentationFamily = i;
			}

			if (indices.IsFilled())
			{
				break;
			}
		}

		return indices;
	}

	bool VulkanPhysicalDevice::IsSwapChainCompatible() const
	{
		std::vector<vk::ExtensionProperties> physicalDeviceExtProps = m_physicalDevice.enumerateDeviceExtensionProperties();
		std::set<std::string> requiredExtentions(m_extensions.begin(), m_extensions.end());

		for (const auto& extension : physicalDeviceExtProps)
		{
			requiredExtentions.erase(extension.extensionName);
		}

		bool swapChainAdequate = false;
		if (requiredExtentions.empty())
		{
			SwapChainRenderTargetInfo swapChainSupport = QuerySwapChainRenderTargetSupport();
			swapChainAdequate = !swapChainSupport.Formats.empty() && !swapChainSupport.PresentationModes.empty();
		}

		return swapChainAdequate;
	}

	SFM::SwapChainRenderTargetInfo VulkanPhysicalDevice::QuerySwapChainRenderTargetSupport() const
	{
		SwapChainRenderTargetInfo details =
		{
			m_physicalDevice.getSurfaceCapabilitiesKHR(m_surface),
			m_physicalDevice.getSurfaceFormatsKHR(m_surface),
			m_physicalDevice.getSurfacePresentModesKHR(m_surface)
		};

		return details;
	}

	vk::PhysicalDevice& VulkanPhysicalDevice::operator()()
	{
		return m_physicalDevice;
	}

	void VulkanPhysicalDevice::LogPhysicalDeviceInfo()
	{
		vk::PhysicalDeviceProperties props = m_physicalDevice.getProperties();
		vk::PhysicalDeviceFeatures features = m_physicalDevice.getFeatures();

		//Log properties.
		SFM_LOGINFO("Found physical device properties:");
		SFM_LOGINFO(std::string(fmt::sprintf("\tName: %s\n\t\t\t\t\tVendorId: %i\n\t\t\t\t\tDeviceId: %i\n\t\t\t\t\tAPIVersion: %i\n\t\t\t\t\tDriverVersion: %i\n\t\t\t\t\tVendorId: %i",
			props.deviceName, props.vendorID, props.deviceID, props.apiVersion, props.driverVersion, props.vendorID)));
		SFM_LOGINFO("\nFeatures:");
		SFM_LOGINFO("\t-no features are being printed right now-");

		//Log extensions.
		SFM_LOGINFO("Supported physical device extentions:");

		std::vector<vk::ExtensionProperties> deviceExtentionProps = m_physicalDevice.enumerateDeviceExtensionProperties();
		for (const auto& props : deviceExtentionProps)
		{
			SFM_LOGINFO(std::string(fmt::sprintf("\t%s - version: %i", props.extensionName, props.specVersion)));
		}
		SFM_LOGINFO("\n");

		//Log layers.
		SFM_LOGINFO("Supported physical device layers:");

		std::vector<vk::LayerProperties> deviceLayerProps = m_physicalDevice.enumerateDeviceLayerProperties();
		for (int i = 0; i < deviceLayerProps.size(); i++)
		{
			SFM_LOGINFO(std::string(fmt::sprintf("\t%s v%i: %s", deviceLayerProps[i].layerName, deviceLayerProps[i].implementationVersion, deviceLayerProps[i].description)));
		}
		SFM_LOGINFO("\n");
	}
}