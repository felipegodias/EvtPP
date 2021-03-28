#pragma once

namespace EvtPP
{
    class IEventHandlerBase
    {
    public:
        IEventHandlerBase() = default;
        IEventHandlerBase(const IEventHandlerBase& other) = default;
        IEventHandlerBase(IEventHandlerBase&& other) noexcept = default;
        IEventHandlerBase& operator=(const IEventHandlerBase& other) = default;
        IEventHandlerBase& operator=(IEventHandlerBase&& other) noexcept = default;

        virtual ~IEventHandlerBase() = 0
        {
        }

        virtual size_t GetListenersCount() const = 0;
    };
}
