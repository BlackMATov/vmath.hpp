/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_qua.hpp"

#include "vmath_vec.hpp"
#include "vmath_vec_fun.hpp"

//
// Operators
//

namespace vmath_hpp
{
    // +operator

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator+(const qua<T>& xs) {
        return xs;
    }

    // -operator

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator-(const qua<T>& xs) {
        return qua(-vec<T, 4>{xs});
    }

    // operator+

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator+(const qua<T>& xs, const qua<T>& ys) {
        return qua(vec{xs} + vec{ys});
    }

    // operator+=

    template < typename T >
    constexpr qua<T>& operator+=(qua<T>& xs, const qua<T>& ys) {
        return (xs = (xs + ys));
    }

    // operator-

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator-(const qua<T>& xs, const qua<T>& ys) {
        return qua(vec{xs} - vec{ys});
    }

    // operator-=

    template < typename T >
    constexpr qua<T>& operator-=(qua<T>& xs, const qua<T>& ys) {
        return (xs = (xs - ys));
    }

    // operator*

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator*(const qua<T>& xs, T y) {
        return qua(vec{xs} * y);
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator*(T x, const qua<T>& ys) {
        return qua(x * vec{ys});
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> operator*(const vec<T, 3>& xs, const qua<T>& ys) {
        const vec qv2 = cross(ys.v, xs) * T(2);
        return xs + qv2 * ys.s + cross(ys.v, qv2);
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator*(const qua<T>& xs, const qua<T>& ys) {
        return {
            cross(ys.v, xs.v) + ys.s * xs.v + xs.s * ys.v,
            ys.s * xs.s - dot(ys.v, xs.v)};
    }

    // operator*=

    template < typename T >
    constexpr qua<T>& operator*=(qua<T>& xs, T y) {
        return (xs = (xs * y));
    }

    template < typename T >
    constexpr vec<T, 3>& operator*=(vec<T, 3>& xs, const qua<T>& ys) {
        return (xs = (xs * ys));
    }

    template < typename T >
    constexpr qua<T>& operator*=(qua<T>& xs, const qua<T>& ys) {
        return (xs = (xs * ys));
    }

    // operator/

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator/(const qua<T>& xs, T y) {
        return qua(vec{xs} / y);
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator/(T x, const qua<T>& ys) {
        return qua(x / vec{ys});
    }

    // operator/=

    template < typename T >
    constexpr qua<T>& operator/=(qua<T>& xs, T y) {
        return (xs = (xs / y));
    }

    // operator==

    template < typename T >
    [[nodiscard]] constexpr bool operator==(const qua<T>& xs, const qua<T>& ys) {
        return vec{xs} == vec{ys};
    }

    // operator!=

    template < typename T >
    [[nodiscard]] constexpr bool operator!=(const qua<T>& xs, const qua<T>& ys) {
        return vec{xs} != vec{ys};
    }

    // operator<

    template < typename T >
    [[nodiscard]] constexpr bool operator<(const qua<T>& xs, const qua<T>& ys) {
        return vec{xs} < vec{ys};
    }
}

    }
}
