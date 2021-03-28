#pragma once
#include <stdexcept>

#define THROW_IF(exp, msg) if ((exp)) throw std::runtime_error(msg)