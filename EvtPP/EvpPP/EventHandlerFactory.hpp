#pragma once
#include "Common/Aliases.hpp"

namespace EvtPP
{
    template <typename Ty>
    class IEventHandler;

    class EventHandlerFactory
    {
    public:
        template <typename Ty>
        UPtr<IEventHandler<Ty>> Create() const;
    };
}
