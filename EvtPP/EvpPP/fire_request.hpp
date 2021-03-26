#pragma once
#include "basic_fire_request.hpp"

namespace EvtPP
{
    template <typename Ty>
    class EventHandler;

    template <typename Ty>
    class FireRequest final : public BasicFireRequest
    {
    public:
        using EventHandler = EventHandler<Ty>;

        FireRequest(Ty event, EventHandler& eventHandler);
        FireRequest(const FireRequest& other) = default;
        FireRequest(FireRequest&& other) noexcept = default;
        FireRequest& operator=(const FireRequest& other) = default;
        FireRequest& operator=(FireRequest&& other) noexcept = default;
        ~FireRequest() override;

        void Fire() override;

    private:
        Ty event;
        EventHandler* _eventHandler;
    };
}

#include "inl/fire_request.inl.hpp"
