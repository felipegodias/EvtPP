#pragma once
#include <memory>

namespace EvtPP
{
    template <typename Ty>
    using UPtr = std::unique_ptr<Ty>;

    template <typename Ty>
    using SPtr = std::shared_ptr<Ty>;
}
