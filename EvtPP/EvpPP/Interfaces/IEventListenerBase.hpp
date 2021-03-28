#pragma once

namespace EvtPP
{
    class IEventListenerBase
    {
    public:
        IEventListenerBase() = default;
        IEventListenerBase(const IEventListenerBase& other) = default;
        IEventListenerBase(IEventListenerBase&& other) noexcept = default;
        IEventListenerBase& operator=(const IEventListenerBase& other) = default;
        IEventListenerBase& operator=(IEventListenerBase&& other) noexcept = default;

        virtual ~IEventListenerBase() = 0
        {
        }
    };
}
