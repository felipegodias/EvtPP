#pragma once
#include "EvpPP/EventHandlerFactory.hpp"

namespace EvtPP
{
    template <typename Ty>
    UPtr<IEventHandler<Ty>> EventHandlerFactory::Create() const
    {
    }
}
