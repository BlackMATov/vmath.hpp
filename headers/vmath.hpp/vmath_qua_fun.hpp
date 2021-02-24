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

namespace vmath_hpp::detail
{
    template < typename A, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const qua<A>& a) {
        return qua(map_join(std::forward<F>(f), vec{a}));
    }

    template < typename A, typename B, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const qua<A>& a, const qua<B>& b) {
        return qua(map_join(std::forward<F>(f), vec{a}, vec{b}));
    }

    template < typename A, typename B, typename C, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const qua<A>& a, const qua<B>& b, const qua<C>& c) {
        return qua(map_join(std::forward<F>(f), vec{a}, vec{b}, vec{c}));
    }

    template < typename A, typename B, typename C, typename D, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const qua<A>& a, const qua<B>& b, const qua<C>& c, const qua<D>& d) {
        return qua(map_join(std::forward<F>(f), vec{a}, vec{b}, vec{c}, vec{d}));
    }

    template < typename A, typename B, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join(F&& f, A init, const qua<B>& b) {
        return fold_join(std::forward<F>(f), std::move(init), vec{b});
    }

    template < typename A, typename B, typename C, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join(F&& f, A init, const qua<B>& b, const qua<C>& c) {
        return fold_join(std::forward<F>(f), std::move(init), vec{b}, vec{c});
    }

    template < typename A, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_join(F&& f, const qua<A>& a) {
        return fold1_join(std::forward<F>(f), vec{a});
    }
}

//
// Operators
//

namespace vmath_hpp
{
    // +operator

    template < typename T >
    [[nodiscard]] constexpr auto operator+(const qua<T>& xs) {
        return qua(+vec<T, 4>{xs});
    }

    // -operator

    template < typename T >
    [[nodiscard]] constexpr auto operator-(const qua<T>& xs) {
        return qua(-vec<T, 4>{xs});
    }

    // operator+

    template < typename T, typename U >
    [[nodiscard]] constexpr auto operator+(const qua<T>& xs, const qua<U>& ys) {
        return qua(vec{xs} + vec{ys});
    }

    // operator+=

    template < typename T >
    constexpr qua<T>& operator+=(qua<T>& xs, const qua<T>& ys) {
        return (xs = (xs + ys));
    }

    // operator-

    template < typename T, typename U >
    [[nodiscard]] constexpr auto operator-(const qua<T>& xs, const qua<U>& ys) {
        return qua(vec{xs} - vec{ys});
    }

    // operator-=

    template < typename T >
    constexpr qua<T>& operator-=(qua<T>& xs, const qua<T>& ys) {
        return (xs = (xs - ys));
    }

    // operator*

    template < typename T, typename U >
    [[nodiscard]] constexpr auto operator*(const qua<T>& xs, U y) {
        return qua(vec{xs} * y);
    }

    template < typename T, typename U >
    [[nodiscard]] constexpr auto operator*(T x, const qua<U>& ys) {
        return qua(x * vec{ys});
    }

    template < typename T, typename U >
    [[nodiscard]] constexpr auto operator*(const vec<T, 3>& xs, const qua<U>& ys) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/

        const vec qv2 = cross(ys.v, xs) * T{2};
        return xs + qv2 * ys.s + cross(ys.v, qv2);
    }

    template < typename T, typename U >
    [[nodiscard]] constexpr auto operator*(const qua<T>& xs, const qua<U>& ys) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/

        return qua{
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

    template < typename T, typename U >
    [[nodiscard]] constexpr auto operator/(const qua<T>& xs, U y) {
        return qua(vec{xs} / y);
    }

    template < typename T, typename U >
    [[nodiscard]] constexpr auto operator/(T x, const qua<U>& ys) {
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
    [[nodiscard]] constexpr qua<T> lerp(const qua<T>& xs, const qua<T>& ys, T a) {
        return qua(lerp(vec{xs}, vec{ys}, a));
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> lerp(const qua<T>& xs, const qua<T>& ys, T x_a, T y_a) {
        return qua(lerp(vec{xs}, vec{ys}, x_a, y_a));
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> nlerp(const qua<T>& unit_xs, const qua<T>& unit_ys, T a) {
        const T xs_scale = T{1} - a;
        const T ys_scale = a * sign(dot(unit_xs, unit_ys));
        return normalize(lerp(unit_xs, unit_ys, xs_scale, ys_scale));
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> slerp(const qua<T>& unit_xs, const qua<T>& unit_ys, T a) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/

        const T raw_cos_theta = dot(unit_xs, unit_ys);
        const T raw_cos_theta_sign = sign(raw_cos_theta);

        // half degree linear threshold: cos((pi / 180) * 0.25)
        if ( const T cos_theta = raw_cos_theta * raw_cos_theta_sign; cos_theta < T{0.99999f} ) {
            const T theta = acos(cos_theta);
            const T rsin_theta = rsqrt(T{1} - sqr(cos_theta));
            const T xs_scale = sin((T{1} - a) * theta) * rsin_theta;
            const T ys_scale = sin(a * theta) * raw_cos_theta_sign * rsin_theta;
            return lerp(unit_xs, unit_ys, xs_scale, ys_scale);
        } else {
            // use linear interpolation for small angles
            const T xs_scale = T{1} - a;
            const T ys_scale = a * raw_cos_theta_sign;
            return normalize(lerp(unit_xs, unit_ys, xs_scale, ys_scale));
        }
    }
}

//
// Geometric Functions
//

namespace vmath_hpp
{
    template < typename T, typename U
             , typename V = decltype(dot(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<U, 4>>())) >
    [[nodiscard]] constexpr V dot(const qua<T>& xs, const qua<U>& ys) {
        return dot(vec{xs}, vec{ys});
    }

    template < typename T >
    [[nodiscard]] constexpr T length(const qua<T>& xs) {
        return length(vec{xs});
    }

    template < typename T >
    [[nodiscard]] constexpr T rlength(const qua<T>& xs) {
        return rlength(vec{xs});
    }

    template < typename T >
    [[nodiscard]] constexpr T length2(const qua<T>& xs) {
        return length2(vec{xs});
    }

    template < typename T >
    [[nodiscard]] constexpr T rlength2(const qua<T>& xs) {
        return rlength2(vec{xs});
    }

    template < typename T >
    [[nodiscard]] constexpr T distance(const qua<T>& xs, const qua<T>& ys) {
        const qua zs = xs * conjugate(ys);
        return T{2} * atan2(length(zs.v), abs(zs.s));
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
    template < typename T
             , typename U = decltype(any(std::declval<vec<T, 4>>())) >
    [[nodiscard]] constexpr U any(const qua<T>& xs) {
        return any(vec{xs});
    }

    template < typename T
             , typename U = decltype(all(std::declval<vec<T, 4>>())) >
    [[nodiscard]] constexpr U all(const qua<T>& xs) {
        return all(vec{xs});
    }

    template < typename T
             , typename U = typename decltype(approx(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<T, 4>>()))::component_type >
    [[nodiscard]] constexpr vec<U, 4> approx(const qua<T>& xs, const qua<T>& ys) {
        return approx(vec{xs}, vec{ys});
    }

    template < typename T
             , typename U = typename decltype(approx(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<T, 4>>(),
                 std::declval<T>()))::component_type >
    [[nodiscard]] constexpr vec<U, 4> approx(const qua<T>& xs, const qua<T>& ys, T epsilon) {
        return approx(vec{xs}, vec{ys}, epsilon);
    }

    template < typename T
             , typename U = typename decltype(less(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<T, 4>>()))::component_type >
    [[nodiscard]] constexpr vec<U, 4> less(const qua<T>& xs, const qua<T>& ys) {
        return less(vec{xs}, vec{ys});
    }

    template < typename T
             , typename U = typename decltype(less_equal(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<T, 4>>()))::component_type >
    [[nodiscard]] constexpr vec<U, 4> less_equal(const qua<T>& xs, const qua<T>& ys) {
        return less_equal(vec{xs}, vec{ys});
    }

    template < typename T
             , typename U = typename decltype(greater(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<T, 4>>()))::component_type >
    [[nodiscard]] constexpr vec<U, 4> greater(const qua<T>& xs, const qua<T>& ys) {
        return greater(vec{xs}, vec{ys});
    }

    template < typename T
             , typename U = typename decltype(greater_equal(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<T, 4>>()))::component_type >
    [[nodiscard]] constexpr vec<U, 4> greater_equal(const qua<T>& xs, const qua<T>& ys) {
        return greater_equal(vec{xs}, vec{ys});
    }

    template < typename T
             , typename U = typename decltype(equal_to(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<T, 4>>()))::component_type >
    [[nodiscard]] constexpr vec<U, 4> equal_to(const qua<T>& xs, const qua<T>& ys) {
        return equal_to(vec{xs}, vec{ys});
    }

    template < typename T
             , typename U = typename decltype(not_equal_to(
                 std::declval<vec<T, 4>>(),
                 std::declval<vec<T, 4>>()))::component_type >
    [[nodiscard]] constexpr vec<U, 4> not_equal_to(const qua<T>& xs, const qua<T>& ys) {
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
        return conjugate(q) * rlength2(q);
    }
}
