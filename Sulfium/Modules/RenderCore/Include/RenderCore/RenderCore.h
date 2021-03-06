#pragma once
#include <Core/Engine.h>
#include "RenderCore/GraphicsAPILoader.h"
#include "ApplicationCore/Window/Window.h"

namespace SFM
{
	/// <summary>
	/// Used to identify, which current API is being used, together with which API should be used on initialization.
	/// </summary>
	enum class EGraphicsAPI
	{
		UNIDENTIFIED = -1,
		VULKAN = 0,
		DX12,
		OPENGL,

		COUNT
	};

	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class RenderCore final
	{
	public:
		RenderCore();
		~RenderCore() = default;

		void Initialize(std::weak_ptr<Engine> engine, Window& window, EGraphicsAPI api);
		void Terminate();
	
		void Render();

	private:
		void LoadGraphicsAPI(EGraphicsAPI api);

		std::weak_ptr<Engine> m_engine;

		GraphicsAPILoader m_graphicsAPILoader;
		IGraphicsAPI* m_graphicsAPI;
		EGraphicsAPI m_activeGraphicsAPI;

		Window* m_window; //This link is needed for the surface creation in Vulkan and Dx12.
	};
}