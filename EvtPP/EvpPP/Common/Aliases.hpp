#pragma once
#include <memory>

namespace EvtPP
{
    template <typename Ty>
    using UPtr = std::unique_ptr<Ty>;
}
