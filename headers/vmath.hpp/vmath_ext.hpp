/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"

namespace vmath_hpp::detail
{
    struct hash_combiner {
        template < typename T >
        std::size_t operator()(std::size_t seed, const T& x) noexcept {
            return (seed ^= std::hash<T>{}(x) + 0x9e3779b9 + (seed << 6) + ( seed >> 2));
        }
    };
}

namespace vmath_hpp
{
    template < typename To, typename From >
    constexpr To cast_to(From x) noexcept {
        return static_cast<To>(x);
    }
}
