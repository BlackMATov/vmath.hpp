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
#include "vmath_vec_ext.hpp"

#include "vmath_mat.hpp"
#include "vmath_mat_fun.hpp"

namespace vmath_hpp
{
    template < typename T > inline constexpr mat<T, 2> zero2x2{0, 0, 0, 0};
    template < typename T > inline constexpr mat<T, 3> zero3x3{0, 0, 0, 0, 0, 0, 0, 0, 0};
    template < typename T > inline constexpr mat<T, 4> zero4x4{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    template < typename T > inline constexpr mat<T, 2> unit2x2{1, 1, 1, 1};
    template < typename T > inline constexpr mat<T, 3> unit3x3{1, 1, 1, 1, 1, 1, 1, 1, 1};
    template < typename T > inline constexpr mat<T, 4> unit4x4{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    template < typename T > inline constexpr mat<T, 2> identity2x2{1, 0, 0, 1};
    template < typename T > inline constexpr mat<T, 3> identity3x3{1, 0, 0, 0, 1, 0, 0, 0, 1};
    template < typename T > inline constexpr mat<T, 4> identity4x4{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
}

namespace std
{
    template < typename T, size_t Size >
    struct hash<vmath_hpp::mat<T, Size>> {
        size_t operator()(const vmath_hpp::mat<T, Size>& m) const noexcept {
            return vmath_hpp::detail::fold(vmath_hpp::detail::hash_combiner{}, size_t{}, m);
        }
    };
}

namespace vmath_hpp
{
    // cast_to

    template < typename To, typename From, std::size_t Size >
    constexpr mat<To, Size> cast_to(const mat<From, Size>& m) {
        return detail::map([](const vec<From, Size>& v){ return cast_to<To>(v); }, m);
    }

    // row

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> row(const mat<T, Size>& m, std::size_t index) {
        return m.rows[index];
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> row(mat<T, Size> m, std::size_t index, const vec<T, Size>& v) {
        m.rows[index] = v;
        return m;
    }

    // column

    namespace impl
    {
        template < typename T, std::size_t Size, std::size_t... Is >
        constexpr vec<T, Size> column_impl(const mat<T, Size>& m, std::size_t index, std::index_sequence<Is...>) {
            return { m[Is][index]... };
        }

        template < typename T, std::size_t Size, std::size_t... Is >
        constexpr mat<T, Size> column_impl(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& v, std::index_sequence<Is...>) {
            return { component(m[Is], index, v[Is])... };
        }
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> column(const mat<T, Size>& m, std::size_t index) {
        return impl::column_impl(m, index, std::make_index_sequence<Size>{});
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> column(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& v) {
        return impl::column_impl(m, index, v, std::make_index_sequence<Size>{});
    }
}

namespace vmath_hpp
{
    // translate

    template < typename T >
    constexpr mat<T, 4> translate(T x, T y, T z) {
        return {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {x, y, z, 1}};
    }

    template < typename T >
    constexpr mat<T, 4> translate(const vec<T, 3>& xyz) {
        return translate(xyz.x, xyz.y, xyz.z);
    }

    template < typename T >
    constexpr mat<T, 4> translate(const mat<T, 4>& m, T x, T y, T z) {
        return m * translate(x, y, z);
    }

    template < typename T >
    constexpr mat<T, 4> translate(const mat<T, 4>& m, const vec<T, 3>& xyz) {
        return m * translate(xyz);
    }

    // rotate

    template < typename T >
    mat<T, 4> rotate(T angle, T axis_x, T axis_y, T axis_z) {
        const T x = axis_x;
        const T y = axis_y;
        const T z = axis_z;
        const T px = x * x;
        const T py = y * y;
        const T pz = z * z;
        const T cs = cos(angle);
        const T sn = sin(angle);
        const T ics = T(1) - cs;
        const T xym = x * y * ics;
        const T xzm = x * z * ics;
        const T yzm = y * z * ics;
        const T xsn = x * sn;
        const T ysn = y * sn;
        const T zsn = z * sn;
        return {
            px * ics + cs, xym + zsn,     xzm - ysn,     0,
            xym - zsn,     py * ics + cs, yzm + xsn,     0,
            xzm + ysn,     yzm - xsn,     pz * ics + cs, 0,
            0,             0,             0,             1};
    }

    template < typename T >
    mat<T, 4> rotate(T angle, const vec<T, 3>& axis) {
        return rotate(angle, axis.x, axis.y, axis.z);
    }

    template < typename T >
    mat<T, 4> rotate(const mat<T, 4>& m, T angle, T axis_x, T axis_y, T axis_z) {
        return m * rotate(angle, axis_x, axis_y, axis_z);
    }

    template < typename T >
    mat<T, 4> rotate(const mat<T, 4>& m, T angle, const vec<T, 3>& axis) {
        return m * rotate(angle, axis);
    }

    // scale

    template < typename T >
    constexpr mat<T, 4> scale(T x, T y, T z) {
        return {
            {x, 0, 0, 0},
            {0, y, 0, 0},
            {0, 0, z, 0},
            {0, 0, 0, 1}};
    }

    template < typename T >
    constexpr mat<T, 4> scale(const vec<T, 3>& xyz) {
        return scale(xyz.x, xyz.y, xyz.z);
    }

    template < typename T >
    constexpr mat<T, 4> scale(const mat<T, 4>& m, T x, T y, T z) {
        return m * scale(x, y, z);
    }

    template < typename T >
    constexpr mat<T, 4> scale(const mat<T, 4>& m, const vec<T, 3>& xyz) {
        return m * scale(xyz);
    }
}
