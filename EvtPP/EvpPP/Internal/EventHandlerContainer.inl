#pragma once

#include "EvpPP/EventHandler.hpp"
#include "EvpPP/EventHandlerContainer.hpp"

namespace EvtPP
{
    template <typename Ty>
    IEventHandler<Ty>& EventHandlerContainer::FetchHandler()
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

    inline EventHandlerContainer::EventHandlers EventHandlerContainer::GetEventHandlers() const
    {
        EventHandlers result(_handlers.size());

        size_t i = 0;
        for (const auto& kvp : _handlers)
        {
            result[i++] = kvp.second.get();
        }

        return result;
    }
}
