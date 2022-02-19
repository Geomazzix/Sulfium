#pragma once
#include <entt/entt.hpp>

namespace SFM
{
	using EventDispatcher = entt::dispatcher;

	/// <summary>
	/// A container class for event dispatcher abstraction within the code base: e.g. WindowEventDisaptcher, InputEventDispatcher, etc.
	/// </summary>
	class EventSystem
	{
	public:
		EventSystem() = default;
		~EventSystem();

		EventDispatcher& AddDispatcher(const std::string& dispatcher);
		void RemoveDispatcher(const std::string& dispatcher);

		EventDispatcher& GetEventDispatcher(const std::string& dispatcherId);
		void ClearDispatchers();

		void DispatchEnqueuedEvents();

	private:
		std::map<std::string, EventDispatcher> m_dispatchers;
	};
}