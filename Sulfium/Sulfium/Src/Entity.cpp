#include "ecs/Entity.h"

namespace SFM
{
	Entity::Entity(EntityHandle handle, ECSWorld* world) :
		m_entityHandle(handle),
		m_world(world)
	{}

	Entity::~Entity()
	{
		m_entityHandle = entt::null;
		m_world = nullptr;
	}

	SFM::EntityHandle& Entity::GetHandle()
	{
		return m_entityHandle;
	}
}