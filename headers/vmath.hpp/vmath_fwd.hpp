/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include <cassert>
#include <cmath>
#include <cstddef>

#include <functional>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

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

    using vec2d = vec<double, 2>;
    using vec3d = vec<double, 3>;
    using vec4d = vec<double, 4>;

    using vec2u = vec<unsigned, 2>;
    using vec3u = vec<unsigned, 3>;
    using vec4u = vec<unsigned, 4>;
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class mat;

    using mat2i = mat<int, 2>;
    using mat3i = mat<int, 3>;
    using mat4i = mat<int, 4>;

    using mat2b = mat<bool, 2>;
    using mat3b = mat<bool, 3>;
    using mat4b = mat<bool, 4>;

    using mat2f = mat<float, 2>;
    using mat3f = mat<float, 3>;
    using mat4f = mat<float, 4>;

    using mat2d = mat<double, 2>;
    using mat3d = mat<double, 3>;
    using mat4d = mat<double, 4>;

    using mat2u = mat<unsigned, 2>;
    using mat3u = mat<unsigned, 3>;
    using mat4u = mat<unsigned, 4>;
}
