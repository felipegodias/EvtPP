#pragma once
#include "EvpPP/FunctionEventListener.hpp"

namespace EvtPP
{
    template <typename Ty>
    FunctionEventListener<Ty>::FunctionEventListener(EventBus& eventBus, Function function) :
        EventListener<Ty>(eventBus),
        _function(std::move(function))
    {
    }

    template <typename Ty>
    void FunctionEventListener<Ty>::OnReceiveEvent(const Ty& event)
    {
        _function(event);
    }
}
