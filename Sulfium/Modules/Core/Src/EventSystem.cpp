#include "Core/Events/EventSystem.h"

namespace SFM
{
	void EventMessenger::RemoveMessenger(const std::string& key)
	{
		m_eventDispatchers.erase(key);
	}

	bool EventMessenger::CheckIfExists(const std::string& key)
	{
		return (m_eventDispatchers.find(key) != m_eventDispatchers.end()) || (m_queuedEventDispatcher.find(key) != m_queuedEventDispatcher.end());
	}
}
