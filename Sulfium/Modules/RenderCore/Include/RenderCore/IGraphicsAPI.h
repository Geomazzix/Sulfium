#pragma once
#include <Core/Engine.h>
#include "ApplicationCore/Window/WindowEventArgs.h"
#include "ApplicationCore/Window/Window.h"

namespace SFM
{
	/// <summary>
	/// The info needed for any graphics API to be initialized.
	/// </summary>
	struct GraphicsAPICreateInfo
	{
		std::weak_ptr<Engine> Engine;
		WindowHandle Window;
		int FrameBufferWidth;
		int FrameBufferHeight;
	};

	/// <summary>
	/// The core module interface, each module within the engine will inherit using this.
	/// </summary>
	class IGraphicsAPI
	{
	public:
		IGraphicsAPI() = default;
		virtual ~IGraphicsAPI() = default;

		virtual void Initialize(GraphicsAPICreateInfo&& info) = 0;
		virtual void Terminate() = 0;

		virtual void OnFrameBufferResize(const SFM::WindowResizeEventArgs& e) = 0;

		//#TODO: Add graphics API methods that all graphics APIs should be able to adhere to.
	
		const std::string& GetName() const
		{
			return m_GraphicsAPI_Name;
		}

	protected:
		std::string m_GraphicsAPI_Name;
	};
}