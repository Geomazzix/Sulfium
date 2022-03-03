#include "Core/Timer/Stopwatch.h"

namespace SFM
{
	void Stopwatch::Start()
	{
		m_start = std::chrono::high_resolution_clock::now();
	}

	void Stopwatch::Stop()
	{
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(end - m_start);
		m_timeInSec = static_cast<float>(timeSpan.count());
	}

	void Stopwatch::Reset(bool startAgain)
	{
		m_timeInSec = 0;
	
		if (startAgain)
		{
			Start();
		}
	}

	float Stopwatch::GetTimeInSec()
	{
		return m_timeInSec;
	}

	float Stopwatch::GetTimeInMs()
	{
		return m_timeInSec / 1000.0f;
	}

	float Stopwatch::GetTimeInNs()
	{
		return m_timeInSec / 1000.0f / 1000.0f;
	}
}