#pragma once
#include "ecs/Entity.h"

using ECSWorld = entt::registry;

namespace SFM
{
	/// <summary>
	/// The scene class manages the life time of an entt registry within the engine.
	/// Takes partial ownership of the ECSWorld created in the engine.
	/// </summary>
	class World
	{
	public:
		World();
		~World();

		Entity& AddLevel(const std::string& name);
		void RemoveLevel(const std::string& name);

		Entity& AddEntity(const std::string& name = std::string(""));
		void RemoveEntity(EntityHandle handle);

		Entity& Translate(EntityHandle handle);

		EntityHandle GetRootHandle() const;
		ECSWorld& GetEcsWorld();

	private:
		ECSWorld m_world;
		Entity* m_worldRoot;

		std::unordered_map<std::string, Entity*> m_levels;			//Keeps track of all the levels.
		std::unordered_map<EntityHandle, Entity*> m_entityWorld;		//Keeps track of all the entity wrapper instances.
	};
}