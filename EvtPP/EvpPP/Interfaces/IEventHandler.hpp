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
        using IEventListenerType = IEventListener<Ty>;

        IEventHandler() = default;
        IEventHandler(const IEventHandler& other) = default;
        IEventHandler(IEventHandler&& other) noexcept = default;
        IEventHandler& operator=(const IEventHandler& other) = default;
        IEventHandler& operator=(IEventHandler&& other) noexcept = default;
        ~IEventHandler() override = 0;

        virtual void Register(IEventListenerType& eventListener) = 0;
        virtual void Deregister(const IEventListenerType& eventListener) = 0;
        virtual bool IsRegistered(const IEventListenerType& eventListener) = 0;
        virtual void Fire(const Event& event) = 0;
    };

    template <typename Ty>
    IEventHandler<Ty>::~IEventHandler() = default;
}
