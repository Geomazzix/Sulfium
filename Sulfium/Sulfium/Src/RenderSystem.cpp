#include "Ecs/Systems/RenderSystem.h"

namespace SFM
{
	RenderSystem::RenderSystem(RenderCore& renderCore) :
		m_renderCore(renderCore)
	{

	}

	void RenderSystem::Execute(float dt)
	{
		m_renderCore.Render();
	}
}