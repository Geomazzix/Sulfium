#include "Core/Timer/Stopwatch.h"

namespace SFM
{
	void Stopwatch::Start()
	{
		m_start = std::chrono::high_resolution_clock::now();
	}

	void Stopwatch::Reset(bool startAgain)
	{	
		if (startAgain)
		{
			Start();
		}
	}

	float Stopwatch::GetTimeInSec()
	{
		m_end = std::chrono::high_resolution_clock::now();
		m_duration = m_end - m_start;
		return m_duration.count();
	}

	float Stopwatch::GetTimeInMs()
	{
		m_end = std::chrono::high_resolution_clock::now();
		m_duration = m_end - m_start;
		return m_duration.count() * 1000.0f;
	}

	float Stopwatch::GetTimeInNs()
	{
		m_end = std::chrono::high_resolution_clock::now();
		m_duration = m_end - m_start;
		return m_duration.count() * 1000.0f * 1000.0f;
	}
}