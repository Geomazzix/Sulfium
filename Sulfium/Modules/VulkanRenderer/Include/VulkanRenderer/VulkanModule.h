#pragma once
#include "RenderCore/IGraphicsAPI.h"
#include "WindowEventArgs.h"

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

		void OnFrameBufferResize(const WindowResizeEventArgs& e) override;

	private:
		std::weak_ptr<Engine> m_engine;
	};
}