#pragma once
#include "../event_handler.hpp"
#include "../fire_request.hpp"

namespace EvtPP
{
    template <typename Ty>
    FireRequest<Ty>::FireRequest(Ty event, EventHandler& eventHandler) : event(std::move(event)),
                                                                         _eventHandler(&eventHandler)
    {
    }

    template <typename Ty>
    FireRequest<Ty>::~FireRequest() = default;

    template <typename Ty>
    void FireRequest<Ty>::Fire()
    {
        _eventHandler->Fire(event);
    }
}
