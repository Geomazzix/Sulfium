#pragma once
#include <ThreadSystem/ThreadSystem.h>
#include <RenderCore/RenderCore.h>
#include <ApplicationCore/ApplicationCore.h>

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
		ApplicationCore m_appCore;
		RenderCore m_renderCore;
		ThreadSystem m_threadSystem;
	};
}