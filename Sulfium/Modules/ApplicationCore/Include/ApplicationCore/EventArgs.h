#pragma once

namespace SFM
{
	/// <summary>
	/// The base struct for the events used by the event system.
	/// </summary>
	struct EventArgs
	{
	public:
		EventArgs() = default;
		virtual ~EventArgs() = default;
	};
}