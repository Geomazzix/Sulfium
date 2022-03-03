#include "ThreadSystem/ThreadSystem.h"
#include "Core/Printer/Printer.h"

namespace SFM
{
	void ThreadSystem::Initialize()
	{
		SFM_LOGINFO("Successfully initialized the thread system!");
	}

	void ThreadSystem::Terminate()
	{
		SFM_LOGINFO("Successfully terminated the thread system!");
	}
}