#pragma once
#include <cassert>

#include "EvpPP/EventBus.hpp"
#include "EvpPP/EventHandler.hpp"

namespace EvtPP
{
    inline EventBus::~EventBus()
    {
        assert(GetListenersCount() == 0);
    }

    template <typename Ty>
    void EventBus::Register(IEventListener<Ty>& eventListener)
    {
        using IEventHandler = IEventHandler<Ty>;
        IEventHandler& handler = FetchHandler<Ty>();
        handler.Register(eventListener);
    }

    template <typename Ty>
    void EventBus::Deregister(const IEventListener<Ty>& eventListener)
    {
        using IEventHandler = IEventHandler<Ty>;
        IEventHandler& handler = FetchHandler<Ty>();
        handler.Deregister(eventListener);
    }

    template <typename Ty>
    void EventBus::Fire(Ty& event)
    {
        const Ty& constEvent = event;
        Fire(constEvent);
    }

    template <typename Ty>
    void EventBus::Fire(const Ty& event)
    {
        using IEventHandler = IEventHandler<Ty>;

        _fireQueue.push([&]()
        {
            IEventHandler& handler = FetchHandler<Ty>();
            handler.Fire(event);
        });

        if (_fireQueue.size() == 1)
        {
            ConsumeFireQueue();
        }
    }

    template <typename Ty, typename ... ArgTys>
    std::enable_if_t<std::is_constructible_v<Ty, ArgTys...>, void>
    EventBus::Fire(ArgTys&&... args)
    {
        Fire(Ty(std::forward<ArgTys>(args)...));
    }

    inline size_t EventBus::GetListenersCount() const
    {
        size_t listenersCount = 0;
        for (const auto& kvp : _handlers)
        {
            listenersCount += kvp.second->GetListenersCount();
        }
        return listenersCount;
    }

    inline void EventBus::ConsumeFireQueue()
    {
        while (!_fireQueue.empty())
        {
            FireFunction function(std::move(_fireQueue.front()));
            _fireQueue.pop();
            function();
        }
    }

    template <typename Ty>
    IEventHandler<Ty>& EventBus::FetchHandler()
    {
        using IEventHandler = IEventHandler<Ty>;
        using EventHandler = EventHandler<Ty>;

        const EventTypeId eventTypeId = GetEventTypeId<Ty>();
        const auto it = _handlers.find(eventTypeId);
        if (it != _handlers.end())
        {
            return *dynamic_cast<IEventHandler*>(it->second.get());
        }

        auto eventHandler = std::make_unique<EventHandler>();
        IEventHandler* eventHandlerPtr = eventHandler.get();
        _handlers.emplace(eventTypeId, std::move(eventHandler));
        return *eventHandlerPtr;
    }
}
