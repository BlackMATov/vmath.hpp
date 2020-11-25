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
    template < typename T > inline constexpr vec<T, 2> zero2{0, 0};
    template < typename T > inline constexpr vec<T, 3> zero3{0, 0, 0};
    template < typename T > inline constexpr vec<T, 4> zero4{0, 0, 0, 0};

    template < typename T > inline constexpr vec<T, 2> unit2{1, 1};
    template < typename T > inline constexpr vec<T, 3> unit3{1, 1, 1};
    template < typename T > inline constexpr vec<T, 4> unit4{1, 1, 1, 1};

    template < typename T > inline constexpr vec<T, 2> unit2_x{1, 0};
    template < typename T > inline constexpr vec<T, 2> unit2_y{0, 1};

    template < typename T > inline constexpr vec<T, 3> unit3_x{1, 0, 0};
    template < typename T > inline constexpr vec<T, 3> unit3_y{0, 1, 0};
    template < typename T > inline constexpr vec<T, 3> unit3_z{0, 0, 1};

    template < typename T > inline constexpr vec<T, 4> unit4_x{1, 0, 0, 0};
    template < typename T > inline constexpr vec<T, 4> unit4_y{0, 1, 0, 0};
    template < typename T > inline constexpr vec<T, 4> unit4_z{0, 0, 1, 0};
    template < typename T > inline constexpr vec<T, 4> unit4_w{0, 0, 0, 1};
}

namespace std
{
    template < typename T, size_t Size >
    struct hash<vmath_hpp::vec<T, Size>> {
        size_t operator()(const vmath_hpp::vec<T, Size>& v) const noexcept {
            return vmath_hpp::detail::fold(vmath_hpp::detail::hash_combiner{}, size_t{}, v);
        }
    };
}

namespace vmath_hpp
{
    // cast_to

    template < typename To, typename From, std::size_t Size >
    constexpr vec<To, Size> cast_to(const vec<From, Size>& v) {
        return detail::map([](From x){ return cast_to<To>(x); }, v);
    }

    // component

    template < typename T, std::size_t Size >
    constexpr T component(const vec<T, Size>& v, std::size_t index) {
        return v[index];
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> component(vec<T, Size> v, std::size_t index, T x) {
        v[index] = x;
        return v;
    }
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    T angle(const vec<T, Size>& x, const vec<T, Size>& y) {
        return acos(dot(x, y) * invsqrt(length2(x) * length2(y)));
    }
}
