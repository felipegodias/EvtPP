#pragma once
#include "EvpPP/EventBus.hpp"
#include "EvpPP/EventListener.hpp"

namespace EvtPP
{
    template <typename Ty>
    EventListener<Ty>::EventListener(EventBus& eventBus) : _eventBus(&eventBus)
    {
        _eventBus->Register(*this);
    }

    template <typename Ty>
    EventListener<Ty>::EventListener(const EventListener& other) : _eventBus(other._eventBus)
    {
        _eventBus->Register(*this);
    }

    template <typename Ty>
    EventListener<Ty>::EventListener(EventListener&& other) noexcept : _eventBus(other._eventBus)
    {
        _eventBus->Register(*this);
        _eventBus->Deregister(&other);
        other._eventBus = nullptr;
    }

    template <typename Ty>
    EventListener<Ty>& EventListener<Ty>::operator=(const EventListener& other)
    {
        if (this == &other)
        {
            return *this;
        }

        if (_eventBus != other._eventBus)
        {
            return *this;
        }

        _eventBus->Deregister(*this);
        _eventBus = other._eventBus;
        _eventBus->Register(*this);
        return *this;
    }

    template <typename Ty>
    EventListener<Ty>& EventListener<Ty>::operator=(EventListener&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        other._eventBus->Deregister(&other);
        if (_eventBus != other._eventBus)
        {
            return *this;
        }

        _eventBus->Deregister(*this);
        _eventBus = other._eventBus;
        _eventBus->Register(*this);
        other._eventBus = nullptr;
        return *this;
    }

    template <typename Ty>
    EventListener<Ty>::~EventListener()
    {
        _eventBus->Deregister(*this);
    }

    template <typename Ty>
    void EventListener<Ty>::OnReceiveEvent(const Ty& event)
    {
    }
}
