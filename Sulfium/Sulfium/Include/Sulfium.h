#pragma once
#include "SulfiumConfig.h"
#include "RenderCore.h"

namespace SFM
{
	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class Sulfium
	{
	public:
		Sulfium();
		~Sulfium();

	private:
		RenderCore m_renderCore;
	};
}