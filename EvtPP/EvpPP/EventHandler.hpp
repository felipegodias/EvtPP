#pragma once
#include <vector>

#include "Interfaces/IEventHandler.hpp"

namespace EvtPP
{
    template <typename Ty>
    class EventHandler final : public IEventHandler<Ty>
    {
    public:
        using Event = typename IEventHandler<Ty>::Event;
        using IEventListenerType = typename IEventHandler<Ty>::IEventListenerType;
        using EventListeners = std::vector<IEventListenerType*>;

        EventHandler() = default;
        EventHandler(const EventHandler& other) = default;
        EventHandler(EventHandler&& other) noexcept = default;
        EventHandler& operator=(const EventHandler& other) = default;
        EventHandler& operator=(EventHandler&& other) noexcept = default;
        ~EventHandler() override = default;

        void Register(IEventListenerType& eventListener) override;
        void Deregister(const IEventListenerType& eventListener) override;
        bool IsRegistered(const IEventListenerType& eventListener) override;
        void Fire(const Event& event) override;

        size_t GetListenersCount() const override;

    private:
        void Cleanup();

    private:
        EventListeners _listeners;
        size_t _dirtyListenersCount = 0;
    };
}

#include "Internal/EventHandler.inl"
