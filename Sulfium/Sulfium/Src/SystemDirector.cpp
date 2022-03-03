#include "ecs/SystemDirector.h"

namespace SFM
{
	void SystemDirector::RegisterSystem(ISystem* system)
	{
		m_stages[static_cast<int>(system->GetStage())].push_back(system);
	}

	void SystemDirector::UnRegisterSystem(ISystem* system)
	{
		int stage = static_cast<int>(system->GetStage());
		SFM_ASSERT(!m_stages[stage].empty());

		auto pos = std::find(m_stages[stage].begin(), m_stages[stage].end(), system);
		SFM_ASSERT(pos != m_stages[stage].end());
		m_stages[stage].erase(pos);
	}

	void SystemDirector::Update(float dt)
	{
		for (int i = 0; i < static_cast<int>(ESystemStage::STAGE_MAX); ++i)
		{
			for (ISystem* system : m_stages[i])
			{
				system->Execute(dt);
			}
		}
	}
}