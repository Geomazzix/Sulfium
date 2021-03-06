#pragma once

namespace SFM
{
	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class VulkanRenderer
	{
	public:
		VulkanRenderer();
		~VulkanRenderer();

		void Initialize();
		void Terminate();

	private:
	};
}