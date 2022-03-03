#pragma once
#include "World/World.h"
#include "Ecs/Systems/ISystem.h"
#include <Core/Engine.h>

namespace SFM
{
	/// <summary>
	/// Updates all the scene transforms, through sorting them according to the scene hierarchy.
	/// The processing of the hierarchy is inspired by: https://skypjack.github.io/2019-08-20-ecs-baf-part-4-insights/
	/// </summary>
	class TransformSystem final : public ISystem
	{
	public:
		TransformSystem(ECSWorld& world);
		~TransformSystem() = default;

		void Execute(float dt) override;

	private:
		void OnTransformConstructOrUpdate(entt::registry& world, entt::entity entity);
		void MakeTransformDirty(EntityHandle entity);

		ECSWorld& m_world;
	};
}