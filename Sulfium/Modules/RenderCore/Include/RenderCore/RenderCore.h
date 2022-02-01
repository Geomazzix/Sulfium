#pragma once
#include "RenderCore/GraphicsAPILoader.h"

namespace SFM
{
	/// <summary>
	/// Used to identify, which current API is being used, together with which API should be used on initialization.
	/// </summary>
	enum class EGraphicsAPI
	{
		VULKAN	= 0,
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

		void Initialize(EGraphicsAPI api);
		void Terminate();
	
	private:
		void LoadGraphicsAPI(EGraphicsAPI api);

		GraphicsAPILoader m_graphicsAPILoader;
		IGraphicsAPI* m_graphicsAPI;
		EGraphicsAPI m_activeGraphicsAPI;
	};
}