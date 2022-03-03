#include "ecs/Systems/ISystem.h"

namespace SFM
{
	int ISystem::s_systemCount = 0;

	ISystem::ISystem(bool enabled /*= true*/, ESystemStage stage /*= ESystemStage::PostUpdate*/) :
		m_id(UINT_MAX),
		m_enabled(enabled),
		m_stage(stage)
	{
		m_id = s_systemCount;
		++s_systemCount;
	}

	unsigned int ISystem::GetId() const
	{
		return m_id;
	}

	bool ISystem::IsEnabled() const
	{
		return m_enabled;
	}

	SFM::ESystemStage ISystem::GetStage() const
	{
		return m_stage;
	}
}