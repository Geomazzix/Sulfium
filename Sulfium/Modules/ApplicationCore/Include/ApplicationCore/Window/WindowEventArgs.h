#pragma once
#include "Core/Events/EventArgs.h"

namespace SFM
{
	/// <summary>
	/// The resize event args are used for the frame buffer resize and go hand in hand with the window pause event args.
	/// </summary>
	class WindowResizeEventArgs : public EventArgs
	{
	public:
		WindowResizeEventArgs(int width, int height):
			Width(width),
			Height(height)
		{}

		int Width;
		int Height;
	};
	
	/// <summary>
	/// The termination event args are used when the window wants to get terminated, meaning the application also needs to terminate.
	/// </summary>
	struct WindowTerminationEventArgs : public EventArgs
	{
		WindowTerminationEventArgs(bool doesTerminate) :
			DoesTerminate(doesTerminate) 
		{}

		bool DoesTerminate;
	};

	/// <summary>
	/// Used during the window resize in order to make sure that the renderer can keep up.
	/// </summary>
	struct WindowPauseEventArgs : public EventArgs
	{
		WindowPauseEventArgs(bool doesPause) :
			DoesPause(doesPause)
		{}

		bool DoesPause;
	};
}