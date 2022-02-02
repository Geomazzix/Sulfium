#pragma once
#include "RenderCore/IGraphicsAPI.h"

namespace SFM
{
	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class VulkanModule final : public IGraphicsAPI
	{
	public:
		VulkanModule() = default;
		~VulkanModule() = default;

		void Initialize() override;
		void Terminate() override;
	};
}