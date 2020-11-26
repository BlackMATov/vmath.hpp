/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

//
// Angle and Trigonometry Functions
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
    sin(T x) noexcept {
        return std::sin(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    cos(T x) noexcept {
        return std::cos(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    tan(T x) noexcept {
        return std::tan(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    asin(T x) noexcept {
        return std::asin(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    acos(T x) noexcept {
        return std::acos(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    atan(T x) noexcept {
        return std::atan(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    atan2(T y, T x) noexcept {
        return std::atan2(y, x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    sinh(T x) noexcept {
        return std::sinh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    cosh(T x) noexcept {
        return std::cosh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    tanh(T x) noexcept {
        return std::tanh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    asinh(T x) noexcept {
        return std::asinh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    acosh(T x) noexcept {
        return std::acosh(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    atanh(T x) noexcept {
        return std::atanh(x);
    }
}

//
// Exponential Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    pow(T x, T y) noexcept {
        return std::pow(x, y);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    exp(T x) noexcept {
        return std::exp(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    log(T x) noexcept {
        return std::log(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    exp2(T x) noexcept {
        return std::exp2(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    log2(T x) noexcept {
        return std::log2(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    sqrt(T x) noexcept {
        return std::sqrt(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    rsqrt(T x) noexcept {
        return T(1) / sqrt(x);
    }
}

//
// Common Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_unsigned_v<T>, T>
    constexpr abs(T x) noexcept {
        return x;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_signed_v<T>, T>
    constexpr abs(T x) noexcept {
        return x >= T(0) ? x : -x;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr sign(T x) noexcept {
        return static_cast<T>((T(0) < x) - (x < T(0)));
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr reciprocal(T x) noexcept {
        return T(1) / x;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    floor(T x) noexcept {
        return std::floor(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    trunc(T x) noexcept {
        return std::trunc(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    round(T x) noexcept {
        return std::round(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    ceil(T x) noexcept {
        return std::ceil(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    fract(T x) noexcept {
        return x - floor(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    fmod(T x, T y) noexcept {
        return std::fmod(x, y);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    modf(T x, T* y) noexcept {
        return std::modf(x, y);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr min(T x, T y) noexcept {
        return std::min(x, y);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr max(T x, T y) noexcept {
        return std::max(x, y);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr clamp(T x, T min_x, T max_x) noexcept {
        return min(max(x, min_x), max_x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr saturate(T x) noexcept {
        return clamp(x, T(0), T(1));
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr lerp(T x, T y, T a) noexcept {
        return x * (T(1) - a) + y * a;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr step(T edge, T x) noexcept {
        return x < edge ? T(0) : T(1);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr smoothstep(T edge0, T edge1, T x) noexcept {
        const T t = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
        return t * t * (T(3) - T(2) * t);
    }

    using ::std::isnan;
    using ::std::isinf;
    using ::std::isfinite;

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    fma(T x, T y, T z) noexcept {
        return std::fma(x, y, z);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    frexp(T x, int* exp) noexcept {
        return std::frexp(x, exp);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    ldexp(T x, int exp) noexcept {
        return std::ldexp(x, exp);
    }
}

//
// Geometric Functions
//

namespace vmath_hpp
{
    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr dot(T x, T y) noexcept {
        return x * y;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr length(T x) noexcept {
        return abs(x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr length2(T x) noexcept {
        return dot(x, x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr distance(T x, T y) noexcept {
        return length(y - x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, T>
    constexpr distance2(T x, T y) noexcept {
        return length2(y - x);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    normalize(T x) noexcept {
        return x * rsqrt(dot(x, x));
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr faceforward(T n, T i, T nref) noexcept {
        return dot(nref, i) < T(0) ? n : -n;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    constexpr reflect(T i, T n) noexcept {
        return i - n * dot(n, i) * T(2);
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
    refract(T i, T n, T eta) noexcept {
        const T d = dot(n, i);
        const T k = T(1) - eta * eta * (T(1) - d * d);
        return T(k >= T(0)) * (eta * i - (eta * d + sqrt(k)) * n);
    }
}

//
// Scalar Relational Functions
//

namespace vmath_hpp
{
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
    constexpr equal_to(T x, T y, T epsilon) noexcept {
        return abs(x - y) <= epsilon;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr not_equal_to(T x, T y) noexcept {
        return x != y;
    }

    template < typename T >
    [[nodiscard]] std::enable_if_t<std::is_arithmetic_v<T>, bool>
    constexpr not_equal_to(T x, T y, T epsilon) noexcept {
        return abs(x - y) > epsilon;
    }

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
}
