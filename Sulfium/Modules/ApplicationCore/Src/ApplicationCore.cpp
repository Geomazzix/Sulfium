#include "ApplicationCore/ApplicationCore.h"
#include <cstdio>

namespace SFM
{
	ApplicationCore::ApplicationCore()
	{

	}

	ApplicationCore::~ApplicationCore()
	{

	}

	void ApplicationCore::Initialize()
	{
		printf("ApplicationCore successfully initialized!\n");
	}

	void ApplicationCore::Terminate()
	{
		printf("ApplicationCore successfully terminated!\n");
	}
}