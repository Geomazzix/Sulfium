#pragma once
#if defined(WIN32) || defined(WIN64)
#pragma warning(push,0)
#pragma warning(disable: 4100)
#include "signals/signals.hpp"
#pragma warning(pop)
#endif

namespace SFM
{
    /// <summary>
    /// Used to create signals for the input of the application core.
    /// Usability: Delegate<ParamaterType(s)> <name_of_event>
    /// </summary>
    /// <typeparam name="...Args"></typeparam>
    template<typename... Args>
    class Delegate
    {
    public:
        Delegate() = default;
        ~Delegate() = default;
        using signal = sig::signal<void(Args...)>;
        using connection = sig::connection;

        template<typename Func>
        connection Connect(Func&& f)
        {
            return m_Callbacks.connect(std::forward<Func>(f));
        }
   
        template<typename Func, typename Instance>
        connection Connect(Func&& f, Instance&& instance)
        {
            return m_Callbacks.connect(std::forward<Func>(f), instance);
        }

        template<typename Func>
        std::size_t Disconnect(Func&& f)
        {
            return m_Callbacks.disconnect(std::forward<Func>(f));
        }

        template<typename Func, typename Instance>
        std::size_t Disconnect(Func&& f, Instance&& instance)
        {
            return m_Callbacks.disconnect(std::forward<Func>(f), instance);
        }

        void operator()(Args&&... args)
        {
            m_Callbacks(std::forward<Args>(args)...);
        }
    private:
        signal m_Callbacks;
    };
}