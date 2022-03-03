#pragma once

namespace SFM
{
	/// <summary>
	/// Used to track time throughout the engine, uses std::chrono as backend.
	/// </summary>
	class Stopwatch
	{
	public:
		Stopwatch() = default;
		~Stopwatch() = default;

		Stopwatch(const Stopwatch& rhs) = delete;
		Stopwatch(Stopwatch&& rhs) = default;

		void Start();
		void Stop();
		void Reset(bool startAgain = false);

		float GetTimeInSec();
		float GetTimeInMs();
		float GetTimeInNs();

	private:
		std::chrono::high_resolution_clock::time_point m_start;
		float m_timeInSec;
	};
}