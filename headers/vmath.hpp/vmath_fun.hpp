/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2023, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

//
// Common Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr abs(T x) noexcept {
        if constexpr ( std::is_signed_v<T> ) {
            return x < T{0} ? -x : x;
        } else {
            return x;
        }
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr sqr(T x) noexcept {
        return x * x;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr sign(T x) noexcept {
        return static_cast<T>((T{0} < x) - (x < T{0}));
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr rcp(T x) noexcept {
        return T{1} / x;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr floor(T x) noexcept {
        return std::floor(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr trunc(T x) noexcept {
        return std::trunc(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr round(T x) noexcept {
        return std::round(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr ceil(T x) noexcept {
        return std::ceil(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr fract(T x) noexcept {
        return x - floor(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr fmod(T x, T y) noexcept {
        return std::fmod(x, y);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr modf(T x, T* y) noexcept {
        return std::modf(x, y);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr copysign(T x, T s) noexcept {
        return std::copysign(x, s);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr min(T x, T y) noexcept {
        return x < y ? x : y;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr max(T x, T y) noexcept {
        return x < y ? y : x;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr clamp(T x, T min_x, T max_x) noexcept {
        return min(max(x, min_x), max_x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr saturate(T x) noexcept {
        return clamp(x, T{0}, T{1});
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr lerp(T x, T y, T a) noexcept {
        return x * (T{1} - a) + y * a;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr lerp(T x, T y, T x_a, T y_a) noexcept {
        return x * x_a + y * y_a;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr step(T edge, T x) noexcept {
        return x < edge ? T{0} : T{1};
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr smoothstep(T edge0, T edge1, T x) noexcept {
        const T t = clamp((x - edge0) * rcp(edge1 - edge0), T{0}, T{1});
        return t * t * (T{3} - T{2} * t);
    }
}

//
// Angle and Trigonometric Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr radians(T degrees) noexcept {
        return degrees * T(0.01745329251994329576923690768489);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr degrees(T radians) noexcept {
        return radians * T(57.295779513082320876798154814105);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr sin(T x) noexcept {
        return std::sin(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr cos(T x) noexcept {
        return std::cos(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr tan(T x) noexcept {
        return std::tan(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr asin(T x) noexcept {
        return std::asin(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr acos(T x) noexcept {
        return std::acos(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr atan(T x) noexcept {
        return std::atan(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr atan2(T y, T x) noexcept {
        return std::atan2(y, x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr sinh(T x) noexcept {
        return std::sinh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr cosh(T x) noexcept {
        return std::cosh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr tanh(T x) noexcept {
        return std::tanh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr asinh(T x) noexcept {
        return std::asinh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr acosh(T x) noexcept {
        return std::acosh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr atanh(T x) noexcept {
        return std::atanh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, std::pair<T, T>>
    constexpr sincos(T x) noexcept {
        return { sin(x), cos(x) };
    }

    template < typename T >
    std::enable_if_t<std::is_floating_point_v<T>, void>
    constexpr sincos(T x, T* s, T* c) noexcept {
        *s = sin(x);
        *c = cos(x);
    }
}

//
// Exponential Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr pow(T x, T y) noexcept {
        return std::pow(x, y);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr exp(T x) noexcept {
        return std::exp(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr log(T x) noexcept {
        return std::log(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr exp2(T x) noexcept {
        return std::exp2(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr log2(T x) noexcept {
        return std::log2(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr sqrt(T x) noexcept {
        return std::sqrt(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr rsqrt(T x) noexcept {
        return rcp(sqrt(x));
    }
}

//
// Geometric Functions
//

namespace vmath_hpp
{
    template < typename T, typename U
             , typename V = decltype(std::declval<T>() * std::declval<U>()) >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<V>, V>
    constexpr dot(T x, U y) noexcept {
        return { x * y };
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr length(T x) noexcept {
        return abs(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr rlength(T x) noexcept {
        return rcp(abs(x));
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr length2(T x) noexcept {
        return dot(x, x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr rlength2(T x) noexcept {
        return rcp(dot(x, x));
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr distance(T x, T y) noexcept {
        if constexpr ( std::is_unsigned_v<T> ) {
            return x < y ? (y - x) : (x - y);
        } else {
            return length(x - y);
        }
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr distance2(T x, T y) noexcept {
        if constexpr ( std::is_unsigned_v<T> ) {
            const T d = x < y ? (y - x) : (x - y);
            return d * d;
        } else {
            return length2(x - y);
        }
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr normalize(T x) noexcept {
        return x * rlength(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr faceforward(T n, T i, T nref) noexcept {
        return dot(nref, i) < T{0} ? n : -n;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr reflect(T i, T n) noexcept {
        return i - T{2} * dot(n, i) * n;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr refract(T i, T n, T eta) noexcept {
        const T d = dot(n, i);
        const T k = T{1} - sqr(eta) * (T{1} - sqr(d));
        return k < T{0} ? T{0} : (eta * i - (eta * d + sqrt(k)) * n);
    }
}

//
// Relational Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr any(T x) noexcept {
        return !!x;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr all(T x) noexcept {
        return !!x;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr approx(T x, T y, T epsilon) noexcept {
        return distance(x, y) <= epsilon;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr approx(T x, T y) noexcept {
        if constexpr ( std::is_floating_point_v<T> ) {
            /// REFERENCE:
            /// http://www.realtimecollisiondetection.net/pubs/Tolerances
            const T epsilon = std::numeric_limits<T>::epsilon();
            return approx(x, y, epsilon * max(T{1}, max(abs(x), abs(y))));
        } else {
            return x == y;
        }
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr less(T x, T y) noexcept {
        return x < y;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr less_equal(T x, T y) noexcept {
        return x <= y;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr greater(T x, T y) noexcept {
        return x > y;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr greater_equal(T x, T y) noexcept {
        return x >= y;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr equal_to(T x, T y) noexcept {
        return x == y;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr not_equal_to(T x, T y) noexcept {
        return x != y;
    }
}
