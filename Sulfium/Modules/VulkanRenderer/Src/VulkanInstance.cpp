#include "VulkanRenderer/Core/VulkanInstance.h"
#include "VulkanRenderer/Core/VulkanPhysicalDevice.h"
#include "VulkanRenderer/Core/VulkanDevice.h"

namespace SFM
{
	void VulkanInstance::Initialize(const std::vector<const char*> validationLayers)
	{
		InitializeDynamicLoader();
		m_validationLayers = validationLayers;
		CreateInstance();
	}

	void VulkanInstance::Terminate()
	{	
#if _DEBUG
		m_debugMessenger.Terminate(m_instance);
#endif
		m_instance.destroy();
	}

	vk::Instance& VulkanInstance::operator()()
	{
		return m_instance;
	}

	vk::Instance& VulkanInstance::Get()
	{
		return m_instance;
	}

	void VulkanInstance::InitializeDynamicLoader()
	{
		PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = m_dynamicLoader.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
		VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);
	}

	void VulkanInstance::CreateInstance()
	{
		//Checking for specific layer support when layers are requested.
		if (m_validationLayersEnabled && !CheckLayerSupport())
		{
			SFM_LOGERROR("The mandatory validation layers requested are not available on this device!");
		}

		//#TODO: Pass these values down through the whole application.
		//Application version info.
		vk::ApplicationInfo appInfo =
		{
			"Sulfium_Vulkan_Renderer",
			VK_MAKE_VERSION(1, 0, 0),
			"Sulfium",
			VK_MAKE_VERSION(1, 0, 0),
			VK_API_VERSION_1_2
		};

		//Query the required extentions to run the renderer (defined by the user).
		std::vector<const char*> extentions = GetRequiredExtentions();

		//Creating the vkInstance.
#if defined(NDEBUG)
		vk::InstanceCreateInfo instanceInfo
		{
			vk::InstanceCreateFlags(),
			&appInfo,
			0,
			nullptr,
			static_cast<uint32_t>(extentions.size()),
			extentions.data()
		};

		m_instance = vk::createInstance(instanceInfo);
#else
		vk::InstanceCreateInfo instanceInfo =
		{
			vk::InstanceCreateFlags(),
			&appInfo,
			m_validationLayersEnabled ? static_cast<uint32_t>(m_validationLayers.size()) : 0,
			m_validationLayersEnabled ? m_validationLayers.data() : nullptr,
			static_cast<uint32_t>(extentions.size()),
			extentions.data()
		};

		m_instance = vk::createInstance(instanceInfo);
#endif
		VULKAN_HPP_DEFAULT_DISPATCHER.init(m_instance);

#if _DEBUG
		m_debugMessenger.Initialize(m_instance);
		SFM_LOGINFO("Application required Vulkan extentions:");
		for (int i = 0; i < extentions.size(); i++)
		{
			SFM_LOGINFO(std::string("\t") + extentions[i]);
		}

		uint32_t vulkanExtentionCount = 0;
		std::vector<vk::ExtensionProperties> vulkanExtentions;
		vulkanExtentions = vk::enumerateInstanceExtensionProperties();

		SFM_LOGINFO("Supported Vulkan instance extension properties:");
		for (const auto& vulkanExtention : vulkanExtentions)
		{
			SFM_LOGINFO(std::string(fmt::sprintf("\t %s - version: %i", vulkanExtention.extensionName, vulkanExtention.specVersion)));
		}
		SFM_LOGINFO("\n");
#endif
	}

	bool VulkanInstance::CheckLayerSupport()
	{
#if _DEBUG
		SFM_LOGINFO("Supported Vulkan instance layer properties (requested before instance creation):");
		std::vector<vk::LayerProperties> instanceLayers = vk::enumerateInstanceLayerProperties();
		for (int i = 0; i < instanceLayers.size(); i++)
		{
			SFM_LOGINFO(std::string(fmt::sprintf("\t%s v%i: %s", instanceLayers[i].layerName, instanceLayers[i].implementationVersion, instanceLayers[i].description)));
		}
		SFM_LOGINFO("\n");

		for (const char* layerName : m_validationLayers)
		{
			bool layerFound = false;
			for (const auto& layerProps : instanceLayers)
			{
				if (strcmp(layerName, layerProps.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}
			if (!layerFound)
			{
				return false;
			}
		}
#endif
		return true;
	}

	std::vector<const char*> VulkanInstance::GetRequiredExtentions()
	{
		std::vector<const char*> extentions =
		{
			VK_KHR_SURFACE_EXTENSION_NAME,
#if defined(WIN32) || defined(WIN64)
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#endif
		};

		if (m_validationLayersEnabled)
		{
			extentions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		//#TODO: Check if the requested extentions above are actually available by enumerating over them.

		return extentions;
	}
}