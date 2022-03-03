#pragma once
#include "Ecs/Components/NameComponent.h"

namespace SFM
{
	/// <summary>
	/// The scene components is used to identify which scenes should get loaded and unloaded
	/// upon a new scene request.
	/// </summary>
	struct SceneComponent
	{
		NameComponent Name;
		bool IsPersistent;

		SceneComponent(const std::string& name, bool isPersistent = false) :
			Name(name),
			IsPersistent(isPersistent)
		{}
	};
}