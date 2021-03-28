#pragma once
#include "Interfaces/IEventListener.hpp"

namespace EvtPP
{
    class EventBus;

    template <typename Ty>
    class EventListener : IEventListener<Ty>
    {
    public:
        explicit EventListener(EventBus& eventBus);
        EventListener(const EventListener& other);
        EventListener(EventListener&& other) noexcept;
        EventListener& operator=(const EventListener& other);
        EventListener& operator=(EventListener&& other) noexcept;
        virtual ~EventListener() = 0;

        void OnReceiveEvent(const Ty& event) override = 0;
    private:
        EventBus* _eventBus;
    };
}

#include "Internal/EventListener.inl"
