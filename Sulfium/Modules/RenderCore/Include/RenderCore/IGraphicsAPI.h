#pragma once
#include "Core/Engine.h"
#include "WindowEventArgs.h"

namespace SFM
{
	/// <summary>
	/// The core module interface, each module within the engine will inherit using this.
	/// </summary>
	class IGraphicsAPI
	{
	public:
		IGraphicsAPI() = default;
		virtual ~IGraphicsAPI() = default;

		virtual void Initialize(std::weak_ptr<Engine> engine) = 0;
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