#pragma once
#include "VulkanRenderer/Utility/VulkanDebugMessenger.h"

namespace SFM
{
	class VulkanPhysicalDevice;
	class VulkanDevice;

	/// <summary>
	/// Responsible for:
	/// - Context initialization.
	/// - Extension loading on instance and device levels.
	/// - Validation layers.
	/// </summary>
	class VulkanInstance
	{
	public:
		VulkanInstance() = default;
		~VulkanInstance() = default;

		void Initialize(const std::vector<const char*> validationLayers);
		void Terminate();

		vk::Instance& operator()();
		vk::Instance& Get();

	private:
		void InitializeDynamicLoader();
		void CreateInstance();

		bool CheckLayerSupport();
		std::vector<const char*> GetRequiredExtentions();

		vk::DynamicLoader m_dynamicLoader;
		vk::Instance m_instance;
		VulkanDebugMessenger m_debugMessenger;

		std::vector<const char*> m_validationLayers;

#if _DEBUG
		const bool m_validationLayersEnabled = true;
#else
		const bool m_validationLayersEnabled = false;
#endif
	};
}