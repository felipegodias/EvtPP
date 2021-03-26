#pragma once
#include <memory>

namespace EvtPP
{
    class BasicFireRequest
    {
    public:
        BasicFireRequest() = default;
        BasicFireRequest(const BasicFireRequest& other) = default;
        BasicFireRequest(BasicFireRequest&& other) noexcept = default;
        BasicFireRequest& operator=(const BasicFireRequest& other) = default;
        BasicFireRequest& operator=(BasicFireRequest&& other) noexcept = default;
        virtual ~BasicFireRequest() = 0;

        virtual void Fire() = 0;
    };

    using BasicFireRequestUPtr = std::unique_ptr<BasicFireRequest>;
}

#include "inl/basic_fire_request.inl.hpp"
