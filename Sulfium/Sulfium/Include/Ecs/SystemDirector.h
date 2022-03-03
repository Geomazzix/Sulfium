#pragma once
#include "Ecs/Systems/ISystem.h"

namespace SFM
{
	/// <summary>
	/// Responsible for the execution order and dependencies within systems.
	/// </summary>
	class SystemDirector
	{
	public:
		SystemDirector() = default;
		~SystemDirector() = default;

		void RegisterSystem(ISystem* system);
		void UnRegisterSystem(ISystem* system);

		void Update(float dt);

	private:
		std::array<std::vector<ISystem*>, static_cast<int>(ESystemStage::STAGE_MAX)> m_stages;
	};
}