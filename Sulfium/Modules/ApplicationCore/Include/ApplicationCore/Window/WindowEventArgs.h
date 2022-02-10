#pragma once
#include "Core/Events/EventArgs.h"

namespace SFM
{
	/// <summary>
	/// Changes that can impact the application on the outside.
	/// </summary>
	enum class EWindowRenderState
	{
		Minimized,
		Maximized,
		Terminating
	};

	class ResizeEventArgs : public EventArgs
	{
	public:
		typedef EventArgs base;
		ResizeEventArgs(int width, int height):
			Width(width),
			Height(height)
		{}

		// The new width of the window
		int Width;
		// The new height of the window.
		int Height;
	};

	class WindowStateEventArgs : public EventArgs
	{
	public:
		typedef EventArgs base;
		WindowStateEventArgs(EWindowRenderState state, int frameBufferWidth, int frameBufferHeight) :
			State(state), 
			FrameBufferWidth(frameBufferWidth), 
			FrameBufferHeight(frameBufferHeight)
		{}

		EWindowRenderState State;
		int FrameBufferWidth;
		int FrameBufferHeight;
	};
}