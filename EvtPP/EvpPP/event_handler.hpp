#pragma once
#include <vector>

#include "basic_event_handler.hpp"

namespace EvtPP
{
    template <typename Ty>
    class EventListener;

    template <typename Ty>
    class EventHandler final : public BasicEventHandler
    {
    public:
        using EventListener = EventListener<Ty>;
        using EventListeners = std::vector<EventListener*>;

        EventHandler() = default;
        EventHandler(const EventHandler& other) = default;
        EventHandler(EventHandler&& other) noexcept = default;
        EventHandler& operator=(const EventHandler& other) = default;
        EventHandler& operator=(EventHandler&& other) noexcept = default;
        ~EventHandler() override;

        void Register(EventListener& eventListener);
        void Deregister(const EventListener& eventListener);
        void Fire(const Ty& event);

    private:
        void Cleanup();

    private:
        bool _isFiring;
        bool _isDirty;
        EventListeners _listeners;
    };
}

#include "inl/event_handler.inl.hpp"
