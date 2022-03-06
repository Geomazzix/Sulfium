#pragma once

namespace SFM
{
	/// <summary>
	/// Handles the debug callback and validation layer setup.
	/// </summary>
	class VulkanDebugMessenger
	{
	public:
		VulkanDebugMessenger() = default;
		~VulkanDebugMessenger() = default;

		void Initialize(vk::Instance& instance);
		void Terminate(vk::Instance& instance);

	private:
		static VKAPI_ATTR vk::Bool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		vk::DebugUtilsMessengerEXT m_debugMessager;
	};
}