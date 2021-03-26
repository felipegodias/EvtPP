#pragma once
#include <queue>
#include <unordered_map>
#include <concepts>

#include "basic_fire_request.hpp"
#include "event_handler.hpp"
#include "event_type_id.hpp"

namespace EvtPP
{
    template <typename Ty>
    class EventListener;

    class EventBus
    {
    public:
        using EventHandlersByEventTypeId = std::unordered_map<EventTypeId, BasicEventHandlerUPtr>;
        using FireRequestsQueue = std::queue<BasicFireRequestUPtr>;

        template <typename Ty>
        void Register(EventListener<Ty>& eventListener);

        template <typename Ty>
        void Deregister(const EventListener<Ty>& eventListener);

        template <typename Ty>
        void Fire(Ty event);

        template <typename Ty, typename ... ArgTys>
        requires std::constructible_from<Ty, ArgTys...>
        void Fire(ArgTys&& ... args);

    private:
        void ConsumeFireRequestsQueue();

        template <typename Ty>
        EventHandler<Ty>& FetchHandler();

    private:
        EventHandlersByEventTypeId _handlers;
        FireRequestsQueue _fireRequestsQueue;
    };
}

#include "inl/event_bus.inl.hpp"
