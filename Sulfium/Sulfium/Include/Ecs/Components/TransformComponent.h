#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace SFM
{
	struct TransformComponent
	{
		glm::vec3 Position = glm::vec3(0.0f);
		glm::quat Orientation = glm::identity<glm::quat>();
		glm::vec3 Scale = glm::vec3(1.0f);

		glm::mat4 WorldTransform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const glm::vec3& position, const glm::vec3& eulerRotationInRads = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f)) :
			Position(position),
			Orientation(eulerRotationInRads),
			Scale(scale)
		{}

		TransformComponent(const glm::vec3& position, const glm::quat& rotation = glm::identity<glm::quat>(), const glm::vec3& scale = glm::vec3(1.0f)) :
			Position(position),
			Orientation(rotation),
			Scale(scale)
		{}
	};

	struct TransformDirtyComponent {};
}