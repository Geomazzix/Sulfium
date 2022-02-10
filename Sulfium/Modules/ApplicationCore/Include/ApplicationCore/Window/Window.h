#pragma once

#if defined(WIN32) || defined(WIN64)
#include "ApplicationCore/Window/Win32Window.h"
#endif //Add different platforms here.

namespace SFM
{
#if defined(WIN32) || defined(WIN64)
	typedef SFM::Win32Window Window;
#endif //Add different platforms here.
}