#pragma once

namespace SFM
{
	/// <summary>
	/// Represents the application at the very core. This class holds the lifetime of the application.
	/// </summary>
	class ApplicationCore
	{
	public:
		ApplicationCore();
		~ApplicationCore();

		void Initialize();
		void Terminate();

	private:

	};
}