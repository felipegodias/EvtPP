#pragma once
#include "EvpPP/EventBus.hpp"
#include "EvpPP/EventHandler.hpp"

namespace EvtPP
{
    inline EventBus::EventBus(SPtr<EventHandlerContainer> handlers) : _handlers(std::move(handlers))
    {
    }

    template <typename Ty>
    void EventBus::Register(IEventListener<Ty>& eventListener)
    {
        using IEventHandler = IEventHandler<Ty>;
        IEventHandler& handler = _handlers->FetchHandler<Ty>();
        handler.Register(eventListener);
    }

    template <typename Ty>
    void EventBus::Deregister(const IEventListener<Ty>& eventListener)
    {
        using IEventHandler = IEventHandler<Ty>;
        IEventHandler& handler = _handlers->FetchHandler<Ty>();
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
            IEventHandler& handler = _handlers->FetchHandler<Ty>();
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
        for (const auto& eventHandler : _handlers->GetEventHandlers())
        {
            listenersCount += eventHandler->GetListenersCount();
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
}
