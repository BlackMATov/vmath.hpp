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
    [[nodiscard]] constexpr vec<T, 4> operator*(const vec<T, 4>& xs, const qua<T>& ys) {
        return {vec<T, 3>{xs} * ys, xs.w};
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
    constexpr vec<T, 4>& operator*=(vec<T, 4>& xs, const qua<T>& ys) {
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

//
// Common Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] vec<bool, 4> isnan(const qua<T>& xs) {
        return isnan(vec{xs});
    }

    template < typename T >
    [[nodiscard]] vec<bool, 4> isinf(const qua<T>& xs) {
        return isinf(vec{xs});
    }

    template < typename T >
    [[nodiscard]] vec<bool, 4> isfinite(const qua<T>& xs) {
        return isfinite(vec{xs});
    }
}

//
// Geometric Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] constexpr T dot(const qua<T>& xs, const qua<T>& ys) {
        return dot(vec{xs}, vec{ys});
    }

    template < typename T >
    [[nodiscard]] T length(const qua<T>& xs) {
        return length(vec{xs});
    }

    template < typename T >
    [[nodiscard]] constexpr T length2(const qua<T>& xs) {
        return length2(vec{xs});
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> normalize(const qua<T>& xs) {
        return qua(normalize(vec{xs}));
    }
}

//
// Relational Functions
//

namespace vmath_hpp
{
    // approx

    template < typename T >
    [[nodiscard]] constexpr vec<bool, 4> approx(const qua<T>& xs, const qua<T>& ys) {
        return approx(vec{xs}, vec{ys});
    }

    template < typename T >
    [[nodiscard]] constexpr vec<bool, 4> approx(const qua<T>& xs, const qua<T>& ys, T epsilon) {
        return approx(vec{xs}, vec{ys}, epsilon);
    }

    // less

    template < typename T >
    [[nodiscard]] constexpr vec<bool, 4> less(const qua<T>& xs, const qua<T>& ys) {
        return less(vec{xs}, vec{ys});
    }

    // less_equal

    template < typename T >
    [[nodiscard]] constexpr vec<bool, 4> less_equal(const qua<T>& xs, const qua<T>& ys) {
        return less_equal(vec{xs}, vec{ys});
    }

    // greater

    template < typename T >
    [[nodiscard]] constexpr vec<bool, 4> greater(const qua<T>& xs, const qua<T>& ys) {
        return greater(vec{xs}, vec{ys});
    }

    // greater_equal

    template < typename T >
    [[nodiscard]] constexpr vec<bool, 4> greater_equal(const qua<T>& xs, const qua<T>& ys) {
        return greater_equal(vec{xs}, vec{ys});
    }

    // equal_to

    template < typename T >
    [[nodiscard]] constexpr vec<bool, 4> equal_to(const qua<T>& xs, const qua<T>& ys) {
        return equal_to(vec{xs}, vec{ys});
    }

    // not_equal_to

    template < typename T >
    [[nodiscard]] constexpr vec<bool, 4> not_equal_to(const qua<T>& xs, const qua<T>& ys) {
        return not_equal_to(vec{xs}, vec{ys});
    }
}

//
// Quaternion Functions
//

namespace vmath_hpp
{
    // conjugate

    template < typename T >
    [[nodiscard]] constexpr qua<T> conjugate(const qua<T>& q) {
        return {-q.v, q.s};
    }

    // inverse

    template < typename T >
    [[nodiscard]] constexpr qua<T> inverse(const qua<T>& q) {
        return conjugate(q) * rcp(dot(q, q));
    }
}
