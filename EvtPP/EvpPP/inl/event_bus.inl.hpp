#pragma once
#include "../event_bus.hpp"
#include "../fire_request.hpp"

namespace EvtPP
{
    template <typename Ty>
    void EventBus::Register(EventListener<Ty>& eventListener)
    {
        using EventHandler = EventHandler<Ty>;
        EventHandler& handler = FetchHandler<Ty>();
        handler.Register(eventListener);
    }

    template <typename Ty>
    void EventBus::Deregister(const EventListener<Ty>& eventListener)
    {
        using EventHandler = EventHandler<Ty>;
        EventHandler& handler = FetchHandler<Ty>();
        handler.Deregister(eventListener);
    }

    template <typename Ty>
    void EventBus::Fire(Ty event)
    {
        using EventHandler = EventHandler<Ty>;
        using FireRequest = FireRequest<Ty>;

        EventHandler& handler = FetchHandler<Ty>();
        auto fireRequest = std::make_unique<FireRequest>(std::move(event), handler);
        _fireRequestsQueue.push(std::move(fireRequest));

        if (_fireRequestsQueue.size() == 1)
        {
            ConsumeFireRequestsQueue();
        }
    }

    template <typename Ty, typename ... ArgTys>
    void EventBus::Fire(ArgTys&&... args)
    {
        Fire(std::move(Ty(std::forward<ArgTys>(args)...)));
    }

    inline void EventBus::ConsumeFireRequestsQueue()
    {
        while (!_fireRequestsQueue.empty())
        {
            BasicFireRequest* fireRequest = _fireRequestsQueue.front().release();
            _fireRequestsQueue.pop();
            fireRequest->Fire();
        }
    }

    template <typename Ty>
    EventHandler<Ty>& EventBus::FetchHandler()
    {
        using EventHandler = EventHandler<Ty>;

        const EventTypeId eventTypeId = GetEventTypeId<Ty>();
        const auto it = _handlers.find(eventTypeId);
        if (it != _handlers.end())
        {
            return *dynamic_cast<EventHandler*>(it->second.get());
        }

        auto eventHandler = std::make_unique<EventHandler>();
        EventHandler* eventHandlerPtr = eventHandler.get();
        _handlers.emplace(eventTypeId, std::move(eventHandler));
        return *eventHandlerPtr;
    }
}
