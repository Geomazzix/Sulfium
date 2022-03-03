#pragma once
#include "Ecs/EcsUtility.h"

namespace SFM
{
	using EntityHandle = entt::entity;

	/// <summary>
	/// Wrapper class that converts the entity to a component based interface.
	/// The implementation's purpose is convenience without losing performance.
	/// </summary>
	class Entity
	{
	public:
		Entity(EntityHandle handle, ECSWorld* world);
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args);

		template<typename T>
		T& GetComponent();

		template<typename T>
		void RemoveComponent();

		template<typename T>
		bool HasComponent();

		EntityHandle& GetHandle();

	private:
		EntityHandle m_entityHandle;
		ECSWorld* m_world;
	};

	template<typename T, typename... Args>
	T& SFM::Entity::AddComponent(Args&&... args)
	{
		SFM_ASSERT(!HasComponent<T>());
		return m_world->emplace<T>(m_entityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& SFM::Entity::GetComponent()
	{
		SFM_ASSERT(HasComponent<T>());
		return m_world->get<T>(m_entityHandle);
	}

	template<typename T>
	void SFM::Entity::RemoveComponent()
	{
		SFM_ASSERT(HasComponent<T>());
		m_world->remove<T>(m_entityHandle);
	}

	template<typename T>
	bool SFM::Entity::HasComponent()
	{
		return m_world->any_of<T>(m_entityHandle);
	}
}