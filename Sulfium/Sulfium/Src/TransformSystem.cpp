#include "ecs/Systems/TransformSystem.h"
#include "ecs/Components/TransformComponent.h"
#include "ecs/Components/RelationComponent.h"
#include "ecs/Components/SceneEntityTypeComponent.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <Core/Printer/Printer.h>

namespace SFM
{
	TransformSystem::TransformSystem(ECSWorld& world) :
		m_world(world)
	{
		m_world.on_construct<TransformComponent>().connect<&TransformSystem::OnTransformConstructOrUpdate>(this);
		m_world.on_update<TransformComponent>().connect<&TransformSystem::OnTransformConstructOrUpdate>(this);
	}

	void TransformSystem::Execute(float dt)
	{
		auto hierarchy = m_world.group<TransformComponent, RelationComponent, TransformDirtyComponent>();

		//Sort all dirty transforms accordingly.
		hierarchy.sort([this](const entt::entity lhs, const entt::entity rhs)
			{
				const auto& clhs = m_world.get<RelationComponent>(lhs);
				const auto& crhs = m_world.get<RelationComponent>(rhs);

				return crhs.Parent == lhs || clhs.Next == rhs || (!(clhs.Parent == rhs || crhs.Next == lhs)
					&& (clhs.Parent < crhs.Parent || (clhs.Parent == crhs.Parent && &clhs < &crhs)));
			});

		//Loop over all the transforms and only recalculate them whenever they contain the dirty component.
		hierarchy.each([&hierarchy](auto entity, auto& transform, auto& relation)
			{
				TransformComponent& transformComp = hierarchy.get<TransformComponent>(entity);
				RelationComponent& relationComp = hierarchy.get<RelationComponent>(entity);

				//Calculate the local transform.
				const glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform.Position);
				const glm::mat4 rotation = glm::toMat4(transform.Orientation);
				const glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.Scale);
				glm::mat4 localTransform = (translation * rotation * scale);

				//Calculate the world transform.
				TransformComponent& parentTransformComp = hierarchy.get<TransformComponent>(entity);
				transformComp.WorldTransform = localTransform * parentTransformComp.WorldTransform;
			});

		//Remove all dirty entries, for the following frame.
		m_world.clear<TransformDirtyComponent>();
	}

	void TransformSystem::OnTransformConstructOrUpdate(entt::registry& world, entt::entity entity)
	{
		MakeTransformDirty(entity);

		RelationComponent& relationComp = m_world.get<RelationComponent>(entity);
		if (relationComp.First == entt::null)
		{
			return;
		}

		MakeTransformDirty(relationComp.First);
		for (int i = 1; i < relationComp.Children; ++i)
		{
			MakeTransformDirty(relationComp.Next);
		}
	}

	void TransformSystem::MakeTransformDirty(EntityHandle entity)
	{
		if (m_world.any_of<TransformDirtyComponent>(entity))
		{
			return;
		}

		m_world.emplace<TransformDirtyComponent>(entity);
	}
}