#pragma once
#include "Core/Events/Delegate.h"

namespace SFM
{
	/// <summary>
	/// The event messenger has the capability to manage listeners, using the delegate wrapper class for the Signals library.
	/// </summary>
	class EventMessenger
	{
	public:
		template<typename... Args>
		void AddMessenger(const std::string& eventName);
		template<typename Arg>
		void AddQueuedMessenger(const std::string& eventName);

		void RemoveMessenger(const std::string& key);

		template<typename... Args>
		void EvokeMessenger(const std::string& key, Args&&... arguments);

		template <typename Arg>
		void AddQueuedMessage(const std::string& key, Arg& argument);

		template <typename Arg>
		void Flush(const std::string& key);

		template<typename... Args, typename Func>
		void ConnectListener(const std::string& key, Func&& f);

		template<typename... Args, typename Func, typename Instance>
		void ConnectListener(const std::string& key, Func&& f, Instance&& instance);

		template<typename... Args, typename Func>
		void DisconnectListener(const std::string& key, Func&& f);

		template<typename... Args, typename Func, typename Instance>
		void DisconnectListener(const std::string& key, Func&& f, Instance&& instance);

		template<typename... Args>
		void operator()(const std::string& key, Args&&... arguments);

	private:
		typedef std::pair<std::queue<std::any>, std::any> queuedEvent;
		
		bool CheckIfExists(const std::string& key);

		std::unordered_map<std::string, std::any> m_eventDispatchers;
		std::unordered_map<std::string, queuedEvent> m_queuedEventDispatcher;
	};

	template <typename... Args>
	void EventMessenger::AddMessenger(const std::string& eventName)
	{
		m_eventDispatchers.insert(std::make_pair(eventName, new Delegate<Args&&...>{}));
	}

	template <typename Arg>
	void EventMessenger::AddQueuedMessenger(const std::string& eventName)
	{
		m_queuedEventDispatcher.insert(std::make_pair(eventName, queuedEvent{ {},new Delegate<Arg>{} }));
	}

	template <typename... Args>
	void EventMessenger::EvokeMessenger(const std::string& key, Args&&... arguments)
	{
		assert(CheckIfExists(key));
		auto delegate = std::any_cast<Delegate<Args&&...>*>(m_eventDispatchers[key]);
		(*delegate)(std::forward<Args>(arguments)...);
	}

	template <typename Arg>
	void EventMessenger::AddQueuedMessage(const std::string& key, Arg& argument)
	{
		assert(CheckIfExists(key));
		m_queuedEventDispatcher[key].first.push(argument);
	}

	template <typename Arg>
	void EventMessenger::Flush(const std::string& key)
	{
		assert(CheckIfExists(key));
		auto delegate = std::any_cast<Delegate<Arg>*>(m_queuedEventDispatcher[key].second);
		auto queue = m_queuedEventDispatcher[key].first;
		while (!queue.empty())
		{
			auto& event = queue.front();
			(*delegate)(std::any_cast<Arg>(event));
			queue.pop();
		}
	}

	template <typename... Args, typename Func>
	void EventMessenger::ConnectListener(const std::string& key, Func&& f)
	{
		assert(CheckIfExists(key));
		if (m_eventDispatchers.find(key) != m_eventDispatchers.end())
		{
			auto delegate = std::any_cast<Delegate<Args&&...>*>(m_eventDispatchers[key]);
			delegate->Connect(f);
		}
		if (m_queuedEventDispatcher.find(key) != m_queuedEventDispatcher.end())
		{
			auto delegate = std::any_cast<Delegate<Args...>*>(m_queuedEventDispatcher[key].second);
			delegate->Connect(f);
		}
	}

	template <typename... Args, typename Func, typename Instance>
	void EventMessenger::ConnectListener(const std::string& key, Func&& f, Instance&& instance)
	{
		assert(CheckIfExists(key));
		if (m_eventDispatchers.find(key) != m_eventDispatchers.end())
		{
			auto delegate = std::any_cast<Delegate<Args&&...>*>(m_eventDispatchers[key]);
			delegate->Connect(f, instance);
		}
		else if (m_queuedEventDispatcher.find(key) != m_queuedEventDispatcher.end())
		{
			auto delegate = std::any_cast<Delegate<Args...>*>(m_queuedEventDispatcher[key].second);
			delegate->Connect(f, instance);
		}
	}

	template <typename... Args, typename Func>
	void EventMessenger::DisconnectListener(const std::string& key, Func&& f)
	{
		assert(CheckIfExists(key));
		if (m_eventDispatchers.find(key) != m_eventDispatchers.end())
		{
			auto delegate = std::any_cast<Delegate<Args&&...>*>(m_eventDispatchers[key]);
			delegate->Disconnect(f);
		}
		else if (m_queuedEventDispatcher.find(key) != m_queuedEventDispatcher.end())
		{
			auto delegate = std::any_cast<Delegate<Args...>*>(m_queuedEventDispatcher[key].second);
			delegate->Disconnect(f);
		}
	}

	template <typename... Args, typename Func, typename Instance>
	void EventMessenger::DisconnectListener(const std::string& key, Func&& f, Instance&& instance)
	{
		assert(CheckIfExists(key));
		if (m_eventDispatchers.find(key) != m_eventDispatchers.end())
		{
			auto delegate = std::any_cast<Delegate<Args&&...>*>(m_eventDispatchers[key]);
			delegate->Disconnect(f, instance);
		}
		else if (m_queuedEventDispatcher.find(key) != m_queuedEventDispatcher.end())
		{
			auto delegate = std::any_cast<Delegate<Args...>*>(m_queuedEventDispatcher[key].second);
			delegate->Disconnect(f, instance);
		}
	}

	template <typename ... Args>
	void EventMessenger::operator()(const std::string& key, Args&&... arguments)
	{
		EvokeMessenger(key, std::forward<Args>(arguments)...);
	}
}
