#pragma once
#include "IEventListenerBase.hpp"

namespace EvtPP
{
    template <typename Ty>
    class IEventListener : public IEventListenerBase
    {
    public:
        IEventListener() = default;
        IEventListener(const IEventListener& other) = default;
        IEventListener(IEventListener&& other) noexcept = default;
        IEventListener& operator=(const IEventListener& other) = default;
        IEventListener& operator=(IEventListener&& other) noexcept = default;
        ~IEventListener() override = default;

        virtual void OnReceiveEvent(const Ty& event) = 0;
    };
}
