#pragma once
#include "../event_type_id.hpp"

namespace EvtPP
{
    inline EventTypeId GetNextEventTypeId()
    {
        static EventTypeId next = 0;
        return ++next;
    }

    template <typename Ty>
    EventTypeId GetEventTypeId()
    {
        static EventTypeId eventTypeId = GetNextEventTypeId();
        return eventTypeId;
    }
}
