#include "Core/Events/EventSystem.h"

namespace SFM
{
	EventSystem::~EventSystem()
	{
		if (m_dispatchers.size() > 0)
		{
			ClearDispatchers();
		}
	}

	SFM::EventDispatcher& EventSystem::AddDispatcher(const std::string& dispatcher)
	{
		assert(m_dispatchers.find(dispatcher) == m_dispatchers.end());
		m_dispatchers.emplace(dispatcher, EventDispatcher());
		return m_dispatchers[dispatcher];
	}

	void EventSystem::RemoveDispatcher(const std::string& dispatcherId)
	{
		assert(m_dispatchers.find(dispatcherId) != m_dispatchers.end());
		m_dispatchers[dispatcherId].clear();
		m_dispatchers.erase(dispatcherId);
	}

	SFM::EventDispatcher& EventSystem::GetEventDispatcher(const std::string& dispatcher)
	{
		return m_dispatchers[dispatcher];
	}

	void EventSystem::ClearDispatchers()
	{
		for (auto& dispatcher : m_dispatchers)
		{
			dispatcher.second.clear();
		}

		m_dispatchers.clear();
	}

	void EventSystem::DispatchEnqueuedEvents()
	{
		for (auto& dispatcher : m_dispatchers)
		{
			dispatcher.second.update();
		}
	}
}