#include "ThreadSystem/ThreadSystem.h"
#include <cstdio>

namespace SFM
{
	ThreadSystem::ThreadSystem()
	{

	}

	ThreadSystem::~ThreadSystem()
	{

	}

	void ThreadSystem::Initialize()
	{
		printf("Successfully initialized the thread system!\n");
	}

	void ThreadSystem::Terminate()
	{
		printf("Successfully terminated the thread system!\n");

	}
}