#pragma once

namespace EvtPP
{
    class EventBus;

    template <typename Ty>
    class EventListener
    {
    public:
        explicit EventListener(EventBus& eventBus);
        EventListener(const EventListener& other);
        EventListener(EventListener&& other) noexcept;
        EventListener& operator=(const EventListener& other);
        EventListener& operator=(EventListener&& other) noexcept;
        virtual ~EventListener() = 0;

        virtual void OnReceiveEvent(const Ty& event) = 0;
    private:
        EventBus* _eventBus;
    };
}

#include "inl/event_listener.inl.hpp"
