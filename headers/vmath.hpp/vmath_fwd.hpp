/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace vmath_hpp
{
    struct uninit_t {};
    inline constexpr uninit_t uninit;
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class vec;

    using vec2i = vec<int, 2>;
    using vec3i = vec<int, 3>;
    using vec4i = vec<int, 4>;

    using vec2b = vec<bool, 2>;
    using vec3b = vec<bool, 3>;
    using vec4b = vec<bool, 4>;

    using vec2f = vec<float, 2>;
    using vec3f = vec<float, 3>;
    using vec4f = vec<float, 4>;
}
