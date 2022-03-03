#include "World/World.h"
#include "ecs/Components/SceneComponent.h"
#include "ecs/Components/TransformComponent.h"
#include "ecs/Components/RelationComponent.h"
#include "ecs/Components/SceneEntityTypeComponent.h"

namespace SFM
{
	World::World() :
		m_world(),
		m_worldRoot(nullptr)
	{
		EntityHandle handle = m_world.create();

		m_entityWorld.emplace(handle, new Entity(handle, &m_world));
		m_entityWorld[handle]->AddComponent<NameComponent>("Root");
		m_entityWorld[handle]->AddComponent<SceneEntityTypeComponent>();
		m_entityWorld[handle]->AddComponent<TransformComponent>();

		RelationComponent& relationComp = m_entityWorld[handle]->AddComponent<RelationComponent>();
		relationComp.Parent = entt::null;

		m_worldRoot = m_entityWorld[handle];
	}

	World::~World()
	{
		m_worldRoot = nullptr;
	}

	SFM::Entity& World::AddLevel(const std::string& name)
	{
		EntityHandle handle = m_world.create();
		
		//Check if the current level name already exists, if so keep 
		//incrementing it's suffix.
		std::string levelName = name;
		int levelNumber = 1;
		while (m_levels.find(name) != m_levels.end())
		{
			levelName = name + std::string("_") + std::to_string(levelNumber);
			++levelNumber;
		}

		m_entityWorld.emplace(handle, new Entity(handle, &m_world));
		m_levels.emplace(levelName, m_entityWorld[handle]);

		//Setting the scene properties.
		RelationComponent& relationComp = m_entityWorld[handle]->AddComponent<RelationComponent>();
		relationComp.Parent = m_worldRoot->GetHandle();
		m_levels[levelName]->AddComponent<SceneComponent>(levelName);
		m_levels[levelName]->AddComponent<TransformComponent>();
		return *m_levels[levelName];
	}

	void World::RemoveLevel(const std::string& name)
	{
		SFM_ASSERT(m_levels.find(name) != m_levels.end());
		EntityHandle handle = m_levels[name]->GetHandle();
		m_levels.erase(name);
		RemoveEntity(handle);
	}

	SFM::Entity& World::AddEntity(const std::string& name /*= std::string("")*/)
	{
		EntityHandle handle = m_world.create();

		m_entityWorld.emplace(handle, new Entity(handle, &m_world));

		RelationComponent& relationComp = m_entityWorld[handle]->AddComponent<RelationComponent>();
		relationComp.Parent = m_worldRoot->GetHandle();

		m_entityWorld[handle]->AddComponent<NameComponent>(name);
		m_entityWorld[handle]->AddComponent<SceneEntityTypeComponent>();
		m_entityWorld[handle]->AddComponent<TransformComponent>();

		return *m_entityWorld[handle];
	}

	void World::RemoveEntity(EntityHandle handle)
	{
		SFM_ASSERT(m_entityWorld.find(handle) != m_entityWorld.end());
		m_world.destroy(m_entityWorld[handle]->GetHandle());
		m_entityWorld.erase(handle);
	}

	SFM::Entity& World::Translate(EntityHandle handle)
	{
		SFM_ASSERT(m_entityWorld.find(handle) != m_entityWorld.end());
		return *m_entityWorld[handle];
	}

	SFM::EntityHandle World::GetRootHandle() const
	{
		return m_worldRoot->GetHandle();
	}

	ECSWorld& World::GetEcsWorld()
	{
		return m_world;
	}

}