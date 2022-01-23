#include "Sulfium.h"

namespace SFM
{
	Sulfium::Sulfium()
	{
		printf("Sulfium version %i.%i\n\n", (int)Sulfium_VERSION_MAJOR, (int)Sulfium_VERSION_MINOR);
		m_renderCore.Initialize(EGraphicsAPI::VULKAN);
	}

	Sulfium::~Sulfium()
	{
		m_renderCore.Terminate();
	}
}