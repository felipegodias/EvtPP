#pragma once
#include <functional>
#include <queue>

#include "Common/Aliases.hpp"
#include "EventHandlerContainer.hpp"

namespace EvtPP
{
    template <typename Ty>
    class IEventListener;

    class EventHandlerFactory;

    class EventBus final
    {
    public:
        using FireFunction = std::function<void()>;
        using FireQueue = std::queue<FireFunction>;

        explicit EventBus(SPtr<EventHandlerContainer> handlers = std::make_shared<EventHandlerContainer>());

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

    private:
        SPtr<EventHandlerContainer> _handlers;
        FireQueue _fireQueue;
    };
}

#include "Internal/EventBus.inl"
