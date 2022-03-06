#include "VulkanRenderer/Utility/VulkanDebugMessenger.h"
#include <Core/Printer/Printer.h>

namespace SFM
{
	void VulkanDebugMessenger::Initialize(vk::Instance& instance)
	{
		vk::DebugUtilsMessageSeverityFlagsEXT logSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
		vk::DebugUtilsMessageTypeFlagsEXT logType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
			vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
			vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;

		vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo =
		{
			vk::DebugUtilsMessengerCreateFlagsEXT(),
			logSeverity,
			logType,
			VulkanDebugMessenger::DebugCallback,
			nullptr
		};

		m_debugMessager = instance.createDebugUtilsMessengerEXT(debugCreateInfo);
	}

	void VulkanDebugMessenger::Terminate(vk::Instance& instance)
	{
		instance.destroyDebugUtilsMessengerEXT(m_debugMessager);
	}

	VKAPI_ATTR vk::Bool32 VulkanDebugMessenger::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		if (messageSeverity > VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) 
		{
			SFM_LOGERROR(pCallbackData->pMessage);
		}
		else if(messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			SFM_LOGWARNING(pCallbackData->pMessage);
		}

		return VK_FALSE;
	}
}