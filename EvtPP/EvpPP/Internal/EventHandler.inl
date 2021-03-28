#pragma once
#include <algorithm>
#include <stdexcept>

#include "EvpPP/Common/ThrowHelper.hpp"
#include "EvpPP/EventHandler.hpp"

namespace EvtPP
{
    template <typename Ty>
    void EventHandler<Ty>::Register(IEventListener& eventListener)
    {
        THROW_IF(IsRegistered(eventListener), "");

        _listeners.push_back(&eventListener);
    }

    template <typename Ty>
    void EventHandler<Ty>::Deregister(const IEventListener& eventListener)
    {
        THROW_IF(!IsRegistered(eventListener), "");

        std::replace(_listeners.begin(), _listeners.end(), const_cast<IEventListener*>(&eventListener),
                     static_cast<IEventListener*>(nullptr));
        ++_dirtyListenersCount;
    }

    template <typename Ty>
    bool EventHandler<Ty>::IsRegistered(const IEventListener& eventListener)
    {
        return std::find(_listeners.begin(), _listeners.end(), &eventListener) != _listeners.end();
    }

    template <typename Ty>
    void EventHandler<Ty>::Fire(const Ty& event)
    {
        for (auto& listener : _listeners)
        {
            if (listener != nullptr)
            {
                listener->OnReceiveEvent(event);
            }
        }

        if (_dirtyListenersCount > 0)
        {
            Cleanup();
        }
    }

    template <typename Ty>
    void EventHandler<Ty>::Cleanup()
    {
        _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), nullptr), _listeners.end());
        _dirtyListenersCount = 0;
    }

    template <typename Ty>
    size_t EventHandler<Ty>::GetListenersCount() const
    {
        return _listeners.size() - _dirtyListenersCount;
    }
}
