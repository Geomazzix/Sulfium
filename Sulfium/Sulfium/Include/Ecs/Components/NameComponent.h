#pragma once

namespace SFM
{
	/// <summary>
	/// Holds the name of an entity.
	/// </summary>
	struct NameComponent
	{
		std::string Name;

		NameComponent(const std::string& name) : 
			Name(name) 
		{}

		std::string& operator()() {
			return Name;
		}
	};
}