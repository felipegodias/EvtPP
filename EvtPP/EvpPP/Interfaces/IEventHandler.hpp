#pragma once
#include "IEventHandlerBase.hpp"

namespace EvtPP
{
    template <typename Ty>
    class IEventListener;

    template <typename Ty>
    class IEventHandler : public IEventHandlerBase
    {
    public:
        using Event = Ty;
        using IEventListener = IEventListener<Ty>;

        IEventHandler() = default;
        IEventHandler(const IEventHandler& other) = default;
        IEventHandler(IEventHandler&& other) noexcept = default;
        IEventHandler& operator=(const IEventHandler& other) = default;
        IEventHandler& operator=(IEventHandler&& other) noexcept = default;
        ~IEventHandler() override = default;

        virtual void Register(IEventListener& eventListener) = 0;
        virtual void Deregister(const IEventListener& eventListener) = 0;
        virtual bool IsRegistered(const IEventListener& eventListener) = 0;
        virtual void Fire(const Event& event) = 0;
    };
}
