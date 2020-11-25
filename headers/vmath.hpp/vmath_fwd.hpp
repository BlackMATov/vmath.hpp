/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include <cassert>
#include <cmath>
#include <cstddef>

#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class vec;

    using bool2 = vec<bool, 2>;
    using bool3 = vec<bool, 3>;
    using bool4 = vec<bool, 4>;

    using int2 = vec<int, 2>;
    using int3 = vec<int, 3>;
    using int4 = vec<int, 4>;

    using uint2 = vec<unsigned, 2>;
    using uint3 = vec<unsigned, 3>;
    using uint4 = vec<unsigned, 4>;

    using float2 = vec<float, 2>;
    using float3 = vec<float, 3>;
    using float4 = vec<float, 4>;

    using double2 = vec<double, 2>;
    using double3 = vec<double, 3>;
    using double4 = vec<double, 4>;

    using size2 = vec<std::size_t, 2>;
    using size3 = vec<std::size_t, 3>;
    using size4 = vec<std::size_t, 4>;
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class mat;

    using bool2x2 = mat<bool, 2>;
    using bool3x3 = mat<bool, 3>;
    using bool4x4 = mat<bool, 4>;

    using int2x2 = mat<int, 2>;
    using int3x3 = mat<int, 3>;
    using int4x4 = mat<int, 4>;

    using uint2x2 = mat<unsigned, 2>;
    using uint3x3 = mat<unsigned, 3>;
    using uint4x4 = mat<unsigned, 4>;

    using float2x2 = mat<float, 2>;
    using float3x3 = mat<float, 3>;
    using float4x4 = mat<float, 4>;

    using double2x2 = mat<double, 2>;
    using double3x3 = mat<double, 3>;
    using double4x4 = mat<double, 4>;

    using size2x2 = mat<std::size_t, 2>;
    using size3x3 = mat<std::size_t, 3>;
    using size4x4 = mat<std::size_t, 4>;
}
