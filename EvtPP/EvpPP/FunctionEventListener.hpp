#pragma once
#include <functional>
#include "EventListener.hpp"

namespace EvtPP
{
    template <typename Ty>
    class FunctionEventListener final : public EventListener<Ty>
    {
    public:
        using Function = std::function<void(const Ty&)>;

        FunctionEventListener(EventBus& eventBus, Function function);
        FunctionEventListener(const FunctionEventListener& other) = delete;
        FunctionEventListener(FunctionEventListener&& other) noexcept = delete;
        FunctionEventListener& operator=(const FunctionEventListener& other) = delete;
        FunctionEventListener& operator=(FunctionEventListener&& other) noexcept = delete;
        ~FunctionEventListener() override = default;

        void OnReceiveEvent(const Ty& event) override;

    private:
        Function _function;
    };
}

#include "Internal/FunctionEventListener.inl"
