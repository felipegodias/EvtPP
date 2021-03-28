#pragma once

namespace EvtPP
{
    using EventTypeId = size_t;

    EventTypeId GetNextEventTypeId();

    template <typename Ty>
    EventTypeId GetEventTypeId();
}

#include "Internal/EventTypeId.inl"
