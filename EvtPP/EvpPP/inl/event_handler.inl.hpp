#pragma once
#include "../event_handler.hpp"
#include "../event_listener.hpp"

namespace EvtPP
{
    template <typename Ty>
    EventHandler<Ty>::~EventHandler()
    {
    }

    template <typename Ty>
    void EventHandler<Ty>::Register(EventListener& eventListener)
    {
        _listeners.push_back(&eventListener);
    }

    template <typename Ty>
    void EventHandler<Ty>::Deregister(const EventListener& eventListener)
    {
        const EventListener* eventListenerPtr = &eventListener;

        size_t i = 0;
        for (; i < _listeners.size(); ++i)
        {
            if (eventListenerPtr == _listeners[i])
            {
                break;
            }
        }

        if (i == _listeners.size())
        {
            return;
        }

        if (_isFiring)
        {
            _listeners[i] = nullptr;
            _isDirty = true;
            return;
        }

        std::swap(_listeners[i], _listeners[_listeners.size() - 1]);
        _listeners.pop_back();
    }

    template <typename Ty>
    void EventHandler<Ty>::Fire(const Ty& event)
    {
        _isFiring = true;
        for (auto& listener : _listeners)
        {
            if (listener == nullptr)
            {
                _isDirty = true;
            }

            listener->OnReceiveEvent(event);
        }

        if (_isDirty)
        {
            Cleanup();
        }
        _isFiring = false;
    }

    template <typename Ty>
    void EventHandler<Ty>::Cleanup()
    {
        size_t listenersCount = _listeners.size();
        for (size_t i = 0; i < listenersCount; ++i)
        {
            if (_listeners[i] != nullptr)
            {
                continue;
            }

            --listenersCount;
            std::swap(_listeners[i], _listeners[listenersCount]);
            _listeners.pop_back();
        }

        _isDirty = false;
    }
}
