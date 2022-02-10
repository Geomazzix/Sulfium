#pragma once

namespace SFM
{
	/// <summary>
	/// Base class for the events that are used by the event system.
	struct EventArgs
	{
	public:
		EventArgs() = default;
		virtual ~EventArgs() = default;
	};

	/// <summary>
	///A custom event that can be used to specify anything the engine is in need of.
	/// </summary>
	class UserEventArgs : public EventArgs
	{
	public:
		typedef EventArgs base;
		UserEventArgs(int code, void* data1, void* data2)
			: Code(code)
			, Data1(data1)
			, Data2(data2)
		{}

		int     Code;
		void* Data1;
		void* Data2;
	};
}