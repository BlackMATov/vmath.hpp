/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_ext.hpp"
#include "vmath_fun.hpp"

#include "vmath_vec.hpp"
#include "vmath_vec_fun.hpp"

namespace vmath_hpp
{
    template < typename To, typename From, std::size_t Size >
    constexpr vec<To, Size> cast_to(const vec<From, Size>& xs) {
        return detail::map([](From x){ return cast_to<To>(x); }, xs);
    }
}
