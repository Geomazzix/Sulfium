#pragma once

namespace SFM
{
	///<summary>
	/// Holds the queried queue families that the assigned GPU supports.
	///</summary>
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> GraphicsFamily;
		std::optional<uint32_t> PresentationFamily;

		inline bool IsFilled()
		{
			return GraphicsFamily.has_value() && PresentationFamily.has_value();
		}
	};
}