#pragma once
#include <memory>

namespace EvtPP
{
    class BasicEventHandler
    {
    public:
        BasicEventHandler() = default;
        BasicEventHandler(const BasicEventHandler& other) = default;
        BasicEventHandler(BasicEventHandler&& other) noexcept = default;
        BasicEventHandler& operator=(const BasicEventHandler& other) = default;
        BasicEventHandler& operator=(BasicEventHandler&& other) noexcept = default;
        virtual ~BasicEventHandler() = 0;
    };

    using BasicEventHandlerUPtr = std::unique_ptr<BasicEventHandler>;
}

#include "inl/basic_event_handler.inl.hpp"

