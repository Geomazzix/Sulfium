#pragma once

namespace SFM
{
	enum class ESceneEntityType
	{
		STATIC,				//Don't move, don't animate
		STATIONAIRY,		//Don't move, can animate (shader value updates)
		DYNAMIC				//Update every frame.
	};

	struct SceneEntityTypeComponent
	{
		ESceneEntityType Type = ESceneEntityType::DYNAMIC;
	
		SceneEntityTypeComponent(ESceneEntityType type = ESceneEntityType::DYNAMIC) :
			Type(type) 
		{}
	};
}