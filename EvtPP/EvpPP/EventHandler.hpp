#pragma once
#include <vector>

#include "Interfaces/IEventHandler.hpp"

namespace EvtPP
{
    template <typename Ty>
    class EventHandler final : public IEventHandler<Ty>
    {
    public:
        using IEventListener = typename IEventHandler<Ty>::IEventListener;
        using EventListeners = std::vector<IEventListener*>;

        EventHandler() = default;
        EventHandler(const EventHandler& other) = default;
        EventHandler(EventHandler&& other) noexcept = default;
        EventHandler& operator=(const EventHandler& other) = default;
        EventHandler& operator=(EventHandler&& other) noexcept = default;
        ~EventHandler() override = default;

        void Register(IEventListener& eventListener) override;
        void Deregister(const IEventListener& eventListener) override;
        bool IsRegistered(const IEventListener& eventListener) override;
        void Fire(const Ty& event) override;

        size_t GetListenersCount() const override;

    private:
        void Cleanup();

    private:
        EventListeners _listeners;
        size_t _dirtyListenersCount = 0;
    };
}

#include "Internal/EventHandler.inl"
