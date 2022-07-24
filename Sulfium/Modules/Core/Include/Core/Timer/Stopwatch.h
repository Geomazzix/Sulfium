#pragma once

namespace SFM
{
	/// <summary>
	/// Used to track time throughout the engine, uses std::chrono as backend.
	/// NOTE: The time values are ONLY valid AFTER calling Stop().
	/// </summary>
	class Stopwatch
	{
	public:
		Stopwatch() = default;
		~Stopwatch() = default;

		Stopwatch(const Stopwatch& rhs) = delete;
		Stopwatch(Stopwatch&& rhs) = default;

		void Start();
		void Reset(bool startAgain = false);

		float GetTimeInSec();
		float GetTimeInMs();
		float GetTimeInNs();

	private:
		std::chrono::steady_clock::time_point m_start;
		std::chrono::steady_clock::time_point m_end;
		std::chrono::duration<float> m_duration;
	};
}