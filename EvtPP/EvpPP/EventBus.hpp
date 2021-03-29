#pragma once
#include <functional>
#include <queue>
#include <unordered_map>

#include "EventHandlerFactory.hpp"
#include "EventTypeId.hpp"
#include "Common/Aliases.hpp"

namespace EvtPP
{
    template <typename Ty>
    class IEventListener;

    class IEventHandlerBase;

    template <typename Ty>
    class IEventHandler;

    class EventHandlerFactory;

    class EventBus final
    {
    public:
        using EventHandlersByEventTypeId = std::unordered_map<EventTypeId, UPtr<IEventHandlerBase>>;
        using FireFunction = std::function<void()>;
        using FireQueue = std::queue<FireFunction>;

        EventBus() = default;
        EventBus(const EventBus& other) = default;
        EventBus(EventBus&& other) noexcept = default;
        EventBus& operator=(const EventBus& other) = default;
        EventBus& operator=(EventBus&& other) noexcept = default;
        ~EventBus();

        template <typename Ty>
        void Register(IEventListener<Ty>& eventListener);

        template <typename Ty>
        void Deregister(const IEventListener<Ty>& eventListener);

        template <typename Ty>
        void Fire(Ty& event);

        template <typename Ty>
        void Fire(const Ty& event);

        template <typename Ty, typename ... ArgTys>
        std::enable_if_t<std::is_constructible_v<Ty, ArgTys...>, void>
        Fire(ArgTys&& ... args);

        size_t GetListenersCount() const;

    private:
        void ConsumeFireQueue();

        template <typename Ty>
        IEventHandler<Ty>& FetchHandler();

    private:
        EventHandlerFactory _eventHandlerFactory;
        EventHandlersByEventTypeId _handlers;
        FireQueue _fireQueue;
    };
}

#include "Internal/EventBus.inl"
