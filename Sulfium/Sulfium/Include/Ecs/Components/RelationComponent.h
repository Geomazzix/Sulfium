#pragma once
#include "ecs/Entity.h"

namespace SFM
{
	/// <summary>
	/// Manages the relationships between entities, aimed to resolve
	/// scene hierarchy issues when applying the ecs paradigm.
	/// </summary>
	struct RelationComponent
	{
		std::size_t Children = 0;				//Child count.
		EntityHandle First = entt::null;		//The id of the first child
		EntityHandle Prev = entt::null;			//The previous sibling in the list of children for the parent.
		EntityHandle Next = entt::null;			//The next sibling in the list of children for the parent.
		EntityHandle Parent = entt::null;		//The id of the parent (if any - e.g. the root doesn't have one).
	};
}