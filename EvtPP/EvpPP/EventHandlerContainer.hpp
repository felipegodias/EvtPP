#pragma once
#include <unordered_map>
#include <vector>

#include "EventTypeId.hpp"
#include "Common/Aliases.hpp"

namespace EvtPP
{
    class IEventHandlerBase;

    template <typename Ty>
    class IEventHandler;

    class EventHandlerContainer
    {
    public:
        using EventHandlersByEventTypeId = std::unordered_map<EventTypeId, UPtr<IEventHandlerBase>>;
        using EventHandlers = std::vector<IEventHandlerBase*>;

        EventHandlerContainer() = default;
        EventHandlerContainer(const EventHandlerContainer& other) = delete;
        EventHandlerContainer(EventHandlerContainer&& other) noexcept = default;
        EventHandlerContainer& operator=(const EventHandlerContainer& other) = delete;
        EventHandlerContainer& operator=(EventHandlerContainer&& other) noexcept = default;
        virtual ~EventHandlerContainer() = default;

        template <typename Ty>
        IEventHandler<Ty>& FetchHandler();

        virtual EventHandlers GetEventHandlers() const;

    private:
        EventHandlersByEventTypeId _handlers;
    };
}

#include "Internal/EventHandlerContainer.inl"
