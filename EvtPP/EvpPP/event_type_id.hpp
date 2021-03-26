#pragma once

namespace EvtPP
{
    using EventTypeId = size_t;
    using event_type_id = size_t;

    EventTypeId GetNextEventTypeId();

    template <typename Ty>
    EventTypeId GetEventTypeId();
}

#include "inl/event_type_id.inl.hpp"
