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
    constexpr T radians(T degrees) noexcept {
        return degrees * T(0.01745329251994329576923690768489);
    }

    template < typename T >
    constexpr T degrees(T radians) noexcept {
        return radians * T(57.295779513082320876798154814105);
    }

    using ::std::sin;
    using ::std::cos;
    using ::std::tan;

    using ::std::asin;
    using ::std::acos;
    using ::std::atan;
    using ::std::atan2;

    using ::std::sinh;
    using ::std::cosh;
    using ::std::tanh;

    using ::std::asinh;
    using ::std::acosh;
    using ::std::atanh;
}

//
// Exponential Functions
//

namespace vmath_hpp
{
    using ::std::pow;
    using ::std::exp;
    using ::std::log;
    using ::std::exp2;
    using ::std::log2;
    using ::std::sqrt;

    template < typename T >
    T invsqrt(T x) noexcept {
        return T(1) / sqrt(x);
    }
}

//
// Common Functions
//

namespace vmath_hpp
{
    using ::std::abs;

    template < typename T >
    T sign(T x) noexcept {
        return static_cast<T>((T(0) < x) - (x < T(0)));
    }

    using ::std::floor;
    using ::std::trunc;
    using ::std::round;
    using ::std::ceil;

    template < typename T >
    T fract(T x) noexcept {
        return x - floor(x);
    }

    using ::std::fmod;
    using ::std::modf;

    using ::std::min;
    using ::std::max;

    template < typename T >
    constexpr T clamp(T x, T min_x, T max_x) noexcept {
        return min(max(x, min_x), max_x);
    }

    template < typename T >
    constexpr T saturate(T x) noexcept {
        return clamp(x, T(0), T(1));
    }

    template < typename T >
    constexpr T lerp(T x, T y, T a) noexcept {
        return x * (T(1) - a) + y * a;
    }

    template < typename T >
    constexpr T step(T edge, T x) noexcept {
        return x < edge ? T(0) : T(1);
    }

    template < typename T >
    constexpr T smoothstep(T edge0, T edge1, T x) noexcept {
        const T t = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
        return t * t * (T(3) - T(2) * t);
    }

    using ::std::isnan;
    using ::std::isinf;
    using ::std::isfinite;

    using ::std::fma;
    using ::std::frexp;
    using ::std::ldexp;
}

//
// Geometric Functions
//

namespace vmath_hpp
{
    template < typename T >
    constexpr T dot(T x, T y) noexcept {
        return x * y;
    }

    template < typename T >
    T length(T x) noexcept {
        return abs(x);
    }

    template < typename T >
    constexpr T length2(T x) noexcept {
        return dot(x, x);
    }

    template < typename T >
    T distance(T x, T y) noexcept {
        return length(y - x);
    }

    template < typename T >
    constexpr T distance2(T x, T y) noexcept {
        return length2(y - x);
    }

    template < typename T >
    T normalize(T x) noexcept {
        return x * invsqrt(dot(x, x));
    }

    template < typename T >
    constexpr T faceforward(T n, T i, T nref) noexcept {
        return dot(nref, i) < T(0) ? n : -n;
    }

    template < typename T >
    constexpr T reflect(T i, T n) noexcept {
        return i - n * dot(n, i) * T(2);
    }

    template < typename T >
    T refract(T i, T n, T eta) noexcept {
        const T d = dot(n, i);
        const T k = T(1) - eta * eta * (T(1) - d * d);
        return T(k >= T(0)) * (eta * i - (eta * d + sqrt(k)) * n);
    }
}
