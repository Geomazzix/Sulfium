#pragma once
#include <string>

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

		virtual void Initialize() = 0;
		virtual void Terminate() = 0;

		//#TODO: Add graphics API methods that all graphics APIs should be able to adhere to.
	
		const std::string& GetName() const
		{
			return m_GraphicsAPI_Name;
		}

	protected:
		std::string m_GraphicsAPI_Name;
	};
}