#pragma once
#include <RenderCore/RenderCore.h>
#include <Core/Engine.h>
#include "Ecs/Systems/ISystem.h"

namespace SFM
{
	/// <summary>
	/// Updates all the scene transforms, through sorting them according to the scene hierarchy.
	/// The processing of the hierarchy is inspired by: https://skypjack.github.io/2019-08-20-ecs-baf-part-4-insights/
	/// </summary>
	class RenderSystem final : public ISystem
	{
	public:
		RenderSystem(RenderCore& renderCore);
		~RenderSystem() = default;

		void Execute(float dt) override;

	private:
		RenderCore& m_renderCore;
	};
}