/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2023, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include <cmath>
#include <cstddef>
#include <cstdlib>

#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>

#if defined(_MSC_VER)
#  define VMATH_HPP_FORCE_INLINE __forceinline
#elif defined(__clang__) || defined(__GNUC__)
#  define VMATH_HPP_FORCE_INLINE inline __attribute__((__always_inline__))
#else
#  define VMATH_HPP_FORCE_INLINE inline
#endif

#if !defined(__cpp_exceptions) && !defined(__EXCEPTIONS) && !defined(_CPPUNWIND)
#  define VMATH_HPP_NO_EXCEPTIONS
#endif

#ifdef VMATH_HPP_NO_EXCEPTIONS
#  define VMATH_HPP_THROW(...) std::abort()
#else
#  define VMATH_HPP_THROW(...) throw __VA_ARGS__
#endif

#define VMATH_HPP_THROW_IF(pred, ...)\
    ( (pred) ? VMATH_HPP_THROW(__VA_ARGS__) : (void)0 )

namespace vmath_hpp
{
    struct no_init_t { explicit no_init_t() = default; };
    inline constexpr no_init_t no_init{};

    struct zero_init_t { explicit zero_init_t() = default; };
    inline constexpr zero_init_t zero_init{};

    struct unit_init_t { explicit unit_init_t() = default; };
    inline constexpr unit_init_t unit_init{};

    struct identity_init_t { explicit identity_init_t() = default; };
    inline constexpr identity_init_t identity_init{};
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class vec;

    using bvec2 = vec<bool, 2>;
    using bvec3 = vec<bool, 3>;
    using bvec4 = vec<bool, 4>;

    using ivec2 = vec<int, 2>;
    using ivec3 = vec<int, 3>;
    using ivec4 = vec<int, 4>;

    using uvec2 = vec<unsigned, 2>;
    using uvec3 = vec<unsigned, 3>;
    using uvec4 = vec<unsigned, 4>;

    using fvec2 = vec<float, 2>;
    using fvec3 = vec<float, 3>;
    using fvec4 = vec<float, 4>;

    using dvec2 = vec<double, 2>;
    using dvec3 = vec<double, 3>;
    using dvec4 = vec<double, 4>;
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class mat;

    using bmat2 = mat<bool, 2>;
    using bmat3 = mat<bool, 3>;
    using bmat4 = mat<bool, 4>;

    using imat2 = mat<int, 2>;
    using imat3 = mat<int, 3>;
    using imat4 = mat<int, 4>;

    using umat2 = mat<unsigned, 2>;
    using umat3 = mat<unsigned, 3>;
    using umat4 = mat<unsigned, 4>;

    using fmat2 = mat<float, 2>;
    using fmat3 = mat<float, 3>;
    using fmat4 = mat<float, 4>;

    using dmat2 = mat<double, 2>;
    using dmat3 = mat<double, 3>;
    using dmat4 = mat<double, 4>;
}

namespace vmath_hpp
{
    template < typename T >
    class qua;

    using fqua = qua<float>;
    using dqua = qua<double>;
}
