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

namespace vmath_hpp::detail
{
    template < typename T, std::size_t Size >
    class vec_base;

    template < typename T >
    class vec_base<T, 2> {
    public:
        T x, y;
    public:
        constexpr vec_base()
        : vec_base{zero_init} {}

        constexpr vec_base(no_init_t) {}
        constexpr vec_base(zero_init_t): vec_base{T{0}} {}
        constexpr vec_base(unit_init_t): vec_base{T{1}} {}

        constexpr explicit vec_base(T v): x{v}, y{v} {}
        constexpr vec_base(T x, T y): x{x}, y{y} {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr vec_base(const vec_base<U, 2>& other): vec_base(other[0], other[1]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const vec_base<U, 3>& other): vec_base(other[0], other[1]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const vec_base<U, 4>& other): vec_base(other[0], other[1]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        // NOLINTNEXTLINE(*-pointer-arithmetic)
        constexpr explicit vec_base(const U* p): vec_base(p[0], p[1]) {}

        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            }
        }

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            }
        }
    };

    template < typename T >
    class vec_base<T, 3> {
    public:
        T x, y, z;
    public:
        constexpr vec_base()
        : vec_base{zero_init} {}

        constexpr vec_base(no_init_t) {}
        constexpr vec_base(zero_init_t): vec_base{T{0}} {}
        constexpr vec_base(unit_init_t): vec_base{T{1}} {}

        constexpr explicit vec_base(T v): x{v}, y{v}, z{v} {}
        constexpr vec_base(T x, T y, T z): x{x}, y{y}, z{z} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z): vec_base(xy[0], xy[1], z) {}
        constexpr vec_base(T x, const vec_base<T, 2>& yz): vec_base(x, yz[0], yz[1]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr vec_base(const vec_base<U, 3>& other): vec_base(other[0], other[1], other[2]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const vec_base<U, 4>& other): vec_base(other[0], other[1], other[2]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        // NOLINTNEXTLINE(*-pointer-arithmetic)
        constexpr explicit vec_base(const U* p): vec_base(p[0], p[1], p[2]) {}

        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
        }

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
        }
    };

    template < typename T >
    class vec_base<T, 4> {
    public:
        T x, y, z, w;
    public:
        constexpr vec_base()
        : vec_base{zero_init} {}

        constexpr vec_base(no_init_t) {}
        constexpr vec_base(zero_init_t) : vec_base{T{0}} {}
        constexpr vec_base(unit_init_t) : vec_base{T{1}} {}

        constexpr explicit vec_base(T v): x{v}, y{v}, z{v}, w{v} {}
        constexpr vec_base(T x, T y, T z, T w): x{x}, y{y}, z{z}, w{w} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z, T w): vec_base(xy[0], xy[1], z, w) {}
        constexpr vec_base(T x, const vec_base<T, 2>& yz, T w): vec_base(x, yz[0], yz[1], w) {}
        constexpr vec_base(T x, T y, const vec_base<T, 2>& zw): vec_base(x, y, zw[0], zw[1]) {}
        constexpr vec_base(const vec_base<T, 2>& xy, const vec_base<T, 2>& zw): vec_base(xy[0], xy[1], zw[0], zw[1]) {}

        constexpr vec_base(const vec_base<T, 3>& xyz, T w): vec_base(xyz[0], xyz[1], xyz[2], w) {}
        constexpr vec_base(T x, const vec_base<T, 3>& yzw): vec_base(x, yzw[0], yzw[1], yzw[2]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr vec_base(const vec_base<U, 4>& other): vec_base(other[0], other[1], other[2], other[3]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        // NOLINTNEXTLINE(*-pointer-arithmetic)
        constexpr explicit vec_base(const U* p): vec_base(p[0], p[1], p[2], p[3]) {}

        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }
    };
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class vec final : public detail::vec_base<T, Size> {
    public:
        using self_type = vec;
        using base_type = detail::vec_base<T, Size>;
        using component_type = T;

        using pointer = component_type*;
        using const_pointer = const component_type*;

        using reference = component_type&;
        using const_reference = const component_type&;

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        static inline constexpr std::size_t size = Size;
    public:
        using base_type::vec_base;
        using base_type::operator[];

        // NOLINTNEXTLINE(*-noexcept-swap)
        void swap(vec& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < Size; ++i ) {
                using std::swap;
                swap((*this)[i], other[i]);
            }
        }

        [[nodiscard]] iterator begin() noexcept { return iterator(data()); }
        [[nodiscard]] const_iterator begin() const noexcept { return const_iterator(data()); }
        [[nodiscard]] iterator end() noexcept { return iterator(data() + Size); }
        [[nodiscard]] const_iterator end() const noexcept { return const_iterator(data() + Size); }

        [[nodiscard]] reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        [[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        [[nodiscard]] reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        [[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        [[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }
        [[nodiscard]] const_iterator cend() const noexcept { return end(); }
        [[nodiscard]] const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        [[nodiscard]] const_reverse_iterator crend() const noexcept { return rend(); }

        [[nodiscard]] pointer data() noexcept {
            return &(*this)[0];
        }

        [[nodiscard]] const_pointer data() const noexcept {
            return &(*this)[0];
        }

        [[nodiscard]] constexpr reference at(std::size_t index) {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("vec::at"));
            return (*this)[index];
        }

        [[nodiscard]] constexpr const_reference at(std::size_t index) const {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("vec::at"));
            return (*this)[index];
        }
    };
}

namespace vmath_hpp
{
    // vec2

    template < typename T >
    vec(T, T) -> vec<T, 2>;

    // vec3

    template < typename T >
    vec(T, T, T) -> vec<T, 3>;

    template < typename T >
    vec(const vec<T, 2>&, T) -> vec<T, 3>;

    template < typename T >
    vec(T, const vec<T, 2>&) -> vec<T, 3>;

    // vec4

    template < typename T >
    vec(T, T, T, T) -> vec<T, 4>;

    template < typename T >
    vec(const vec<T, 2>&, T, T) -> vec<T, 4>;

    template < typename T >
    vec(T, const vec<T, 2>&, T) -> vec<T, 4>;

    template < typename T >
    vec(T, T, const vec<T, 2>&) -> vec<T, 4>;

    template < typename T >
    vec(const vec<T, 2>&, const vec<T, 2>&) -> vec<T, 4>;

    template < typename T >
    vec(const vec<T, 3>&, T) -> vec<T, 4>;

    template < typename T >
    vec(T, const vec<T, 3>&) -> vec<T, 4>;

    // swap

    template < typename T, std::size_t Size >
    // NOLINTNEXTLINE(*-noexcept-swap)
    void swap(vec<T, Size>& l, vec<T, Size>& r) noexcept(noexcept(l.swap(r))) {
        l.swap(r);
    }
}

namespace vmath_hpp::detail::impl
{
    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return vec{ f(a[Is])... };
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return vec{ f(a[Is], b[Is])... };
    }

    template < typename A, typename B, typename C, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        const vec<C, Size>& c,
        std::index_sequence<Is...>)
    {
        return vec{ f(a[Is], b[Is], c[Is])... };
    }

    template < typename A, typename B, typename C, typename D, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        const vec<C, Size>& c,
        const vec<D, Size>& d,
        std::index_sequence<Is...>)
    {
        return vec{ f(a[Is], b[Is], c[Is], d[Is])... };
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        A init,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return ((init = f(std::move(init), b[Is])), ...);
    }

    template < typename A, std::size_t Size, typename F, std::size_t I, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        std::index_sequence<I, Is...>)
    {
        A init = a[I];
        return ((init = f(std::move(init), a[Is])), ...);
    }

    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return (... && f(a[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... && f(a[Is], b[Is]));
    }

    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return (... || f(a[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... || f(a[Is], b[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_plus_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... + f(a[Is], b[Is]));
    }
}

namespace vmath_hpp::detail
{
    template < typename A, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const vec<A, Size>& a) {
        return impl::map_join_impl(std::forward<F>(f), a, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const vec<A, Size>& a, const vec<B, Size>& b) {
        return impl::map_join_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, typename C, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const vec<A, Size>& a, const vec<B, Size>& b, const vec<C, Size>& c) {
        return impl::map_join_impl(std::forward<F>(f), a, b, c, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, typename C, typename D, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const vec<A, Size>& a, const vec<B, Size>& b, const vec<C, Size>& c, const vec<D, Size>& d) {
        return impl::map_join_impl(std::forward<F>(f), a, b, c, d, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join(F&& f, A init, const vec<B, Size>& b) {
        return impl::fold_join_impl(std::forward<F>(f), std::move(init), b, std::make_index_sequence<Size>{});
    }

    template < typename A, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_join(F&& f, const vec<A, Size>& a) {
        return impl::fold1_join_impl(std::forward<F>(f), a, std::make_index_sequence<Size>{});
    }

    template < typename A, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join(F&& f, const vec<A, Size>& a) {
        return impl::fold1_and_join_impl(std::forward<F>(f), a, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join(F&& f, const vec<A, Size>& a, const vec<B, Size>& b) {
        return impl::fold1_and_join_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }

    template < typename A, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join(F&& f, const vec<A, Size>& a) {
        return impl::fold1_or_join_impl(std::forward<F>(f), a, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join(F&& f, const vec<A, Size>& a, const vec<B, Size>& b) {
        return impl::fold1_or_join_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_plus_join(F&& f, const vec<A, Size>& a, const vec<B, Size>& b) {
        return impl::fold1_plus_join_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }
}

//
// Operators
//

namespace vmath_hpp
{
    // +operator

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator+(const vec<T, Size>& xs) {
        return map_join([](T x){ return +x; }, xs);
    }

    // -operator

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator-(const vec<T, Size>& xs) {
        return map_join([](T x){ return -x; }, xs);
    }

    // ~operator

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator~(const vec<T, Size>& xs) {
        return map_join([](T x){ return ~x; }, xs);
    }

    // !operator

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator!(const vec<T, Size>& xs) {
        return map_join([](T x){ return !x; }, xs);
    }

    // ++operator

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator++(vec<T, Size>& xs) {
        return (xs = xs + T{1});
    }

    // --operator

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator--(vec<T, Size>& xs) {
        return (xs = xs - T{1});
    }

    // operator++

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator++(vec<T, Size>& xs, int) {
        vec<T, Size> ys = xs;
        ++xs;
        return ys;
    }

    // operator--

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator--(vec<T, Size>& xs, int) {
        vec<T, Size> ys = xs;
        --xs;
        return ys;
    }

    // operator+

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator+(const vec<T, Size>& xs, U y) {
        return map_join([y](T x){ return x + y; }, xs);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator+(T x, const vec<U, Size>& ys) {
        return map_join([x](U y){ return x + y; }, ys);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator+(const vec<T, Size>& xs, const vec<U, Size>& ys) {
        return map_join([](T x, U y){ return x + y; }, xs, ys);
    }

    // operator+=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator+=(vec<T, Size>& xs, T y) {
        return (xs = (xs + y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator+=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs + ys));
    }

    // operator-

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator-(const vec<T, Size>& xs, U y) {
        return map_join([y](T x){ return x - y; }, xs);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator-(T x, const vec<U, Size>& ys) {
        return map_join([x](U y){ return x - y; }, ys);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator-(const vec<T, Size>& xs, const vec<U, Size>& ys) {
        return map_join([](T x, U y){ return x - y; }, xs, ys);
    }

    // operator-=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator-=(vec<T, Size>& xs, T y) {
        return (xs = (xs - y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator-=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs - ys));
    }

    // operator*

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator*(const vec<T, Size>& xs, U y) {
        return map_join([y](T x){ return x * y; }, xs);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator*(T x, const vec<U, Size>& ys) {
        return map_join([x](U y){ return x * y; }, ys);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator*(const vec<T, Size>& xs, const vec<U, Size>& ys) {
        return map_join([](T x, U y){ return x * y; }, xs, ys);
    }

    // operator*=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator*=(vec<T, Size>& xs, T y) {
        return (xs = (xs * y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator*=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs * ys));
    }

    // operator/

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator/(const vec<T, Size>& xs, U y) {
        return map_join([y](T x){ return x / y; }, xs);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator/(T x, const vec<U, Size>& ys) {
        return map_join([x](U y){ return x / y; }, ys);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator/(const vec<T, Size>& xs, const vec<U, Size>& ys) {
        return map_join([](T x, U y){ return x / y; }, xs, ys);
    }

    // operator/=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator/=(vec<T, Size>& xs, T y) {
        return (xs = (xs / y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator/=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs / ys));
    }

    // operator&

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&(const vec<T, Size>& xs, T y) {
        return map_join([y](T x){ return x & y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&(T x, const vec<T, Size>& ys) {
        return map_join([x](T y){ return x & y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return x & y; }, xs, ys);
    }

    // operator&=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator&=(vec<T, Size>& xs, T y) {
        return (xs = (xs & y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator&=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs & ys));
    }

    // operator|

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator|(const vec<T, Size>& xs, T y) {
        return map_join([y](T x){ return x | y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator|(T x, const vec<T, Size>& ys) {
        return map_join([x](T y){ return x | y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator|(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return x | y; }, xs, ys);
    }

    // operator|=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator|=(vec<T, Size>& xs, T y) {
        return (xs = (xs | y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator|=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs | ys));
    }

    // operator^

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator^(const vec<T, Size>& xs, T y) {
        return map_join([y](T x){ return x ^ y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator^(T x, const vec<T, Size>& ys) {
        return map_join([x](T y){ return x ^ y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator^(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return x ^ y; }, xs, ys);
    }

    // operator^=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator^=(vec<T, Size>& xs, T y) {
        return (xs = (xs ^ y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator^=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs ^ ys));
    }

    // operator<<

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator<<(const vec<T, Size>& xs, T y) {
        return map_join([y](T x){ return x << y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator<<(T x, const vec<T, Size>& ys) {
        return map_join([x](T y){ return x << y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator<<(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return x << y; }, xs, ys);
    }

    // operator<<=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator<<=(vec<T, Size>& xs, T y) {
        return (xs = (xs << y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator<<=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs << ys));
    }

    // operator>>

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator>>(const vec<T, Size>& xs, T y) {
        return map_join([y](T x){ return x >> y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator>>(T x, const vec<T, Size>& ys) {
        return map_join([x](T y){ return x >> y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator>>(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return x >> y; }, xs, ys);
    }

    // operator>>=

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator>>=(vec<T, Size>& xs, T y) {
        return (xs = (xs >> y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator>>=(vec<T, Size>& xs, const vec<T, Size>& ys) {
        return (xs = (xs >> ys));
    }

    // operator&&

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&&(const vec<T, Size>& xs, T y) {
        return map_join([y](T x){ return x && y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&&(T x, const vec<T, Size>& ys) {
        return map_join([x](T y){ return x && y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&&(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return x && y; }, xs, ys);
    }

    // operator||

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator||(const vec<T, Size>& xs, T y) {
        return map_join([y](T x){ return x || y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator||(T x, const vec<T, Size>& ys) {
        return map_join([x](T y){ return x || y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator||(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return x || y; }, xs, ys);
    }

    // operator==

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr bool operator==(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return fold1_and_join([](T x, T y){ return x == y; }, xs, ys);
    }

    // operator!=

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr bool operator!=(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return fold1_or_join([](T x, T y){ return x != y; }, xs, ys);
    }

    // operator<

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr bool operator<(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        for ( std::size_t i = 0; i < Size; ++i ) {
            if ( xs[i] < ys[i] ) {
                return true;
            }
            if ( ys[i] < xs[i] ) {
                return false;
            }
        }
        return false;
    }
}

//
// Common Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> abs(const vec<T, Size>& xs) {
        return map_join([](T x) { return abs(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> sqr(const vec<T, Size>& xs) {
        return map_join([](T x) { return sqr(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> sign(const vec<T, Size>& xs) {
        return map_join([](T x) { return sign(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> rcp(const vec<T, Size>& xs) {
        return map_join([](T x) { return rcp(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> floor(const vec<T, Size>& xs) {
        return map_join([](T x) { return floor(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> trunc(const vec<T, Size>& xs) {
        return map_join([](T x) { return trunc(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> round(const vec<T, Size>& xs) {
        return map_join([](T x) { return round(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> ceil(const vec<T, Size>& xs) {
        return map_join([](T x) { return ceil(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> fract(const vec<T, Size>& xs) {
        return map_join([](T x) { return fract(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> fmod(const vec<T, Size>& xs, T y) {
        return map_join([y](T x) { return fmod(x, y); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> fmod(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y) { return fmod(x, y); }, xs, ys);
    }

    namespace impl
    {
        template < typename T, std::size_t Size, std::size_t... Is >
        constexpr VMATH_HPP_FORCE_INLINE
        vec<T, Size> modf_impl(const vec<T, Size>& xs, vec<T, Size>* is, std::index_sequence<Is...>) {
            return { modf(xs[Is], &(*is)[Is])... };
        }
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> modf(const vec<T, Size>& xs, vec<T, Size>* is) {
        return impl::modf_impl(xs, is, std::make_index_sequence<Size>{});
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> copysign(const vec<T, Size>& xs, T s) {
        return map_join([s](T x) { return copysign(x, s); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> copysign(const vec<T, Size>& xs, const vec<T, Size>& ss) {
        return map_join([](T x, T s) { return copysign(x, s); }, xs, ss);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T min(const vec<T, Size>& xs) {
        return fold1_join([](T acc, T x){ return min(acc, x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> min(const vec<T, Size>& xs, T y) {
        return map_join([y](T x) { return min(x, y); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> min(T x, const vec<T, Size>& ys) {
        return map_join([x](T y) { return min(x, y); }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> min(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y) { return min(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T max(const vec<T, Size>& xs) {
        return fold1_join([](T acc, T x){ return max(acc, x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> max(const vec<T, Size>& xs, T y) {
        return map_join([y](T x) { return max(x, y); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> max(T x, const vec<T, Size>& ys) {
        return map_join([x](T y) { return max(x, y); }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> max(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y) { return max(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> clamp(const vec<T, Size>& xs, T min_x, T max_x) {
        return map_join([min_x, max_x](T x) { return clamp(x, min_x, max_x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> clamp(const vec<T, Size>& xs, const vec<T, Size>& min_xs, const vec<T, Size>& max_xs) {
        return map_join([](T x, T min_x, T max_x) { return clamp(x, min_x, max_x); }, xs, min_xs, max_xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> saturate(const vec<T, Size>& xs) {
        return map_join([](T x) { return saturate(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> lerp(const vec<T, Size>& xs, const vec<T, Size>& ys, T a) {
        return map_join([a](T x, T y) { return lerp(x, y, a); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> lerp(const vec<T, Size>& xs, const vec<T, Size>& ys, T x_a, T y_a) {
        return map_join([x_a, y_a](T x, T y) { return lerp(x, y, x_a, y_a); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> lerp(
        const vec<T, Size>& xs,
        const vec<T, Size>& ys,
        const vec<T, Size>& as)
    {
        return map_join([](T x, T y, T a) { return lerp(x, y, a); }, xs, ys, as);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> lerp(
        const vec<T, Size>& xs,
        const vec<T, Size>& ys,
        const vec<T, Size>& xs_a,
        const vec<T, Size>& ys_a)
    {
        return map_join([](T x, T y, T x_a, T y_a) { return lerp(x, y, x_a, y_a); }, xs, ys, xs_a, ys_a);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> step(T edge, const vec<T, Size>& xs) {
        return map_join([edge](T x) { return step(edge, x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> step(const vec<T, Size>& edges, const vec<T, Size>& xs) {
        return map_join([](T edge, T x) { return step(edge, x); }, edges, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> smoothstep(T edge0, T edge1, const vec<T, Size>& xs) {
        return map_join([edge0, edge1](T x) { return smoothstep(edge0, edge1, x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> smoothstep(const vec<T, Size>& edges0, const vec<T, Size>& edges1, const vec<T, Size>& xs) {
        return map_join([](T edge0, T edge1, T x) { return smoothstep(edge0, edge1, x); }, edges0, edges1, xs);
    }
}

//
// Angle and Trigonometric Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> radians(const vec<T, Size>& degrees) {
        return map_join([](T x) { return radians(x); }, degrees);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> degrees(const vec<T, Size>& radians) {
        return map_join([](T x) { return degrees(x); }, radians);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> sin(const vec<T, Size>& xs) {
        return map_join([](T x) { return sin(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> cos(const vec<T, Size>& xs) {
        return map_join([](T x) { return cos(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> tan(const vec<T, Size>& xs) {
        return map_join([](T x) { return tan(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> asin(const vec<T, Size>& xs) {
        return map_join([](T x) { return asin(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> acos(const vec<T, Size>& xs) {
        return map_join([](T x) { return acos(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> atan(const vec<T, Size>& xs) {
        return map_join([](T x) { return atan(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> atan2(const vec<T, Size>& ys, const vec<T, Size>& xs) {
        return map_join([](T y, T x) { return atan2(y, x); }, ys, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> sinh(const vec<T, Size>& xs) {
        return map_join([](T x) { return sinh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> cosh(const vec<T, Size>& xs) {
        return map_join([](T x) { return cosh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> tanh(const vec<T, Size>& xs) {
        return map_join([](T x) { return tanh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> asinh(const vec<T, Size>& xs) {
        return map_join([](T x) { return asinh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> acosh(const vec<T, Size>& xs) {
        return map_join([](T x) { return acosh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> atanh(const vec<T, Size>& xs) {
        return map_join([](T x) { return atanh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr std::pair<vec<T, Size>, vec<T, Size>> sincos(const vec<T, Size>& xs) {
        return { sin(xs), cos(xs) };
    }

    template < typename T, std::size_t Size >
    constexpr void sincos(const vec<T, Size>& xs, vec<T, Size>* ss, vec<T, Size>* cs) {
        *ss = sin(xs);
        *cs = cos(xs);
    }
}

//
// Exponential Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> pow(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y) { return pow(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> exp(const vec<T, Size>& xs) {
        return map_join([](T x) { return exp(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> log(const vec<T, Size>& xs) {
        return map_join([](T x) { return log(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> exp2(const vec<T, Size>& xs) {
        return map_join([](T x) { return exp2(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> log2(const vec<T, Size>& xs) {
        return map_join([](T x) { return log2(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> sqrt(const vec<T, Size>& xs) {
        return map_join([](T x) { return sqrt(x); }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> rsqrt(const vec<T, Size>& xs) {
        return map_join([](T x) { return rsqrt(x); }, xs);
    }
}

//
// Geometric Functions
//

namespace vmath_hpp
{
    template < typename T, typename U, std::size_t Size
             , typename V = decltype(std::declval<T>() * std::declval<U>()) >
    [[nodiscard]] constexpr V dot(const vec<T, Size>& xs, const vec<U, Size>& ys) {
        return fold1_plus_join([](T x, U y){ return x * y; }, xs, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T length(const vec<T, Size>& xs) {
        return sqrt(dot(xs, xs));
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T rlength(const vec<T, Size>& xs) {
        return rsqrt(dot(xs, xs));
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T length2(const vec<T, Size>& xs) {
        return dot(xs, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T rlength2(const vec<T, Size>& xs) {
        return rcp(dot(xs, xs));
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T distance(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return length(xs - ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T distance2(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return length2(xs - ys);
    }

    template < typename T, typename U
             , typename V = decltype(std::declval<T>() * std::declval<U>()) >
    [[nodiscard]] constexpr V cross(const vec<T, 2>& xs, const vec<U, 2>& ys) {
        return { xs.x * ys.y - xs.y * ys.x };
    }

    template < typename T, typename U
             , typename V = decltype(std::declval<T>() * std::declval<U>()) >
    [[nodiscard]] constexpr vec<V, 3> cross(const vec<T, 3>& xs, const vec<U, 3>& ys) {
        return {
            xs.y * ys.z - xs.z * ys.y,
            xs.z * ys.x - xs.x * ys.z,
            xs.x * ys.y - xs.y * ys.x};
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> normalize(const vec<T, Size>& xs) {
        return xs * rlength(xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> faceforward(const vec<T, Size>& n, const vec<T, Size>& i, const vec<T, Size>& nref) {
        return dot(nref, i) < T{0} ? n : -n;
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> reflect(const vec<T, Size>& i, const vec<T, Size>& n) {
        return i - T{2} * dot(n, i) * n;
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> refract(const vec<T, Size>& i, const vec<T, Size>& n, T eta) {
        const T d = dot(n, i);
        const T k = T{1} - sqr(eta) * (T{1} - sqr(d));
        return k < T{0} ? vec<T, Size>{T{0}} : (eta * i - (eta * d + sqrt(k)) * n);
    }
}

//
// Relational Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size
             , typename U = decltype(any(std::declval<T>())) >
    [[nodiscard]] constexpr U any(const vec<T, Size>& xs) {
        return fold1_or_join([](T x){ return any(x); }, xs);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(all(std::declval<T>())) >
    [[nodiscard]] constexpr U all(const vec<T, Size>& xs) {
        return fold1_and_join([](T x){ return all(x); }, xs);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(approx(
                 std::declval<T>(),
                 std::declval<T>())) >
    [[nodiscard]] constexpr vec<U, Size> approx(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return approx(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(approx(
                 std::declval<T>(),
                 std::declval<T>(),
                 std::declval<T>())) >
    [[nodiscard]] constexpr vec<U, Size> approx(const vec<T, Size>& xs, const vec<T, Size>& ys, T epsilon) {
        return map_join([epsilon](T x, T y){ return approx(x, y, epsilon); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(less(
                 std::declval<T>(),
                 std::declval<T>())) >
    [[nodiscard]] constexpr vec<U, Size> less(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return less(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(less_equal(
                 std::declval<T>(),
                 std::declval<T>())) >
    [[nodiscard]] constexpr vec<U, Size> less_equal(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return less_equal(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(greater(
                 std::declval<T>(),
                 std::declval<T>())) >
    [[nodiscard]] constexpr vec<U, Size> greater(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return greater(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(greater_equal(
                 std::declval<T>(),
                 std::declval<T>())) >
    [[nodiscard]] constexpr vec<U, Size> greater_equal(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return greater_equal(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(equal_to(
                 std::declval<T>(),
                 std::declval<T>())) >
    [[nodiscard]] constexpr vec<U, Size> equal_to(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return equal_to(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(not_equal_to(
                 std::declval<T>(),
                 std::declval<T>())) >
    [[nodiscard]] constexpr vec<U, Size> not_equal_to(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return map_join([](T x, T y){ return not_equal_to(x, y); }, xs, ys);
    }
}

namespace vmath_hpp::detail
{
    template < typename T, std::size_t Size >
    class mat_base;

    template < typename T >
    class mat_base<T, 2> {
    public:
        using row_type = vec<T, 2>;
        // NOLINTNEXTLINE(*-avoid-c-arrays)
        row_type rows[2]{no_init, no_init};
    public:
        constexpr mat_base()
        : mat_base(identity_init) {}

        constexpr mat_base(no_init_t) {}
        constexpr mat_base(zero_init_t): mat_base{zero_init, zero_init} {}
        constexpr mat_base(unit_init_t): mat_base{unit_init, unit_init} {}
        constexpr mat_base(identity_init_t): mat_base{T{1}} {}

        constexpr explicit mat_base(T d)
        : rows{
            {d, T{0}},
            {T{0}, d}} {}

        constexpr explicit mat_base(const row_type& d)
        : rows{
            {d[0], T{0}},
            {T{0}, d[1]}} {}

        constexpr mat_base(
            T m11, T m12,
            T m21, T m22)
        : rows{
            {m11, m12},
            {m21, m22}} {}

        constexpr mat_base(
            const row_type& row0,
            const row_type& row1)
        : rows{row0, row1} {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr mat_base(const mat_base<U, 2>& other): mat_base(
            row_type{other.rows[0]},
            row_type{other.rows[1]}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const mat_base<U, 3>& other): mat_base(
            row_type{other.rows[0]},
            row_type{other.rows[1]}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const mat_base<U, 4>& other): mat_base(
            row_type{other.rows[0]},
            row_type{other.rows[1]}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const U* p): mat_base(
            row_type{p + 0u * row_type::size},
            row_type{p + 1u * row_type::size}) {}
    };

    template < typename T >
    class mat_base<T, 3> {
    public:
        using row_type = vec<T, 3>;
        // NOLINTNEXTLINE(*-avoid-c-arrays)
        row_type rows[3]{no_init, no_init, no_init};
    public:
        constexpr mat_base()
        : mat_base(identity_init) {}

        constexpr mat_base(no_init_t) {}
        constexpr mat_base(zero_init_t): mat_base{zero_init, zero_init, zero_init} {}
        constexpr mat_base(unit_init_t): mat_base{unit_init, unit_init, unit_init} {}
        constexpr mat_base(identity_init_t): mat_base{T{1}} {}

        constexpr explicit mat_base(T d)
        : rows{
            {d, T{0}, T{0}},
            {T{0}, d, T{0}},
            {T{0}, T{0}, d}} {}

        constexpr explicit mat_base(const row_type& d)
        : rows{
            {d[0], T{0}, T{0}},
            {T{0}, d[1], T{0}},
            {T{0}, T{0}, d[2]}} {}

        constexpr mat_base(
            T m11, T m12, T m13,
            T m21, T m22, T m23,
            T m31, T m32, T m33)
        : rows{
            {m11, m12, m13},
            {m21, m22, m23},
            {m31, m32, m33}} {}

        constexpr mat_base(
            const row_type& row0,
            const row_type& row1,
            const row_type& row2)
        : rows{row0, row1, row2} {}

        constexpr mat_base(
            const mat_base<T, 2>& m,
            const vec_base<T, 2>& v)
        : rows{
            {m.rows[0], T{0}},
            {m.rows[1], T{0}},
            {v, T{1}}} {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr mat_base(const mat_base<U, 3>& other): mat_base(
            row_type{other.rows[0]},
            row_type{other.rows[1]},
            row_type{other.rows[2]}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const mat_base<U, 2>& other): mat_base(
            row_type{other.rows[0], T{0}},
            row_type{other.rows[1], T{0}},
            row_type{T{0}, T{0}, T{1}}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const mat_base<U, 4>& other): mat_base(
            row_type{other.rows[0]},
            row_type{other.rows[1]},
            row_type{other.rows[2]}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const U* p): mat_base(
            row_type{p + 0u * row_type::size},
            row_type{p + 1u * row_type::size},
            row_type{p + 2u * row_type::size}) {}
    };

    template < typename T >
    class mat_base<T, 4> {
    public:
        using row_type = vec<T, 4>;
        // NOLINTNEXTLINE(*-avoid-c-arrays)
        row_type rows[4]{no_init, no_init, no_init, no_init};
    public:
        constexpr mat_base()
        : mat_base(identity_init) {}

        constexpr mat_base(no_init_t) {}
        constexpr mat_base(zero_init_t): mat_base{zero_init, zero_init, zero_init, zero_init} {}
        constexpr mat_base(unit_init_t): mat_base{unit_init, unit_init, unit_init, unit_init} {}
        constexpr mat_base(identity_init_t): mat_base{T{1}} {}

        constexpr explicit mat_base(T d)
        : rows{
            {d, T{0}, T{0}, T{0}},
            {T{0}, d, T{0}, T{0}},
            {T{0}, T{0}, d, T{0}},
            {T{0}, T{0}, T{0}, d}} {}

        constexpr explicit mat_base(const row_type& d)
        : rows{
            {d[0], T{0}, T{0}, T{0}},
            {T{0}, d[1], T{0}, T{0}},
            {T{0}, T{0}, d[2], T{0}},
            {T{0}, T{0}, T{0}, d[3]}} {}

        constexpr mat_base(
            T m11, T m12, T m13, T m14,
            T m21, T m22, T m23, T m24,
            T m31, T m32, T m33, T m34,
            T m41, T m42, T m43, T m44)
        : rows{
            {m11, m12, m13, m14},
            {m21, m22, m23, m24},
            {m31, m32, m33, m34},
            {m41, m42, m43, m44}} {}

        constexpr mat_base(
            const row_type& row0,
            const row_type& row1,
            const row_type& row2,
            const row_type& row3)
        : rows{row0, row1, row2, row3} {}

        constexpr mat_base(
            const mat_base<T, 3>& m,
            const vec_base<T, 3>& v)
        : rows{
            {m.rows[0], T{0}},
            {m.rows[1], T{0}},
            {m.rows[2], T{0}},
            {v, T{1}}} {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr mat_base(const mat_base<U, 4>& other): mat_base(
            row_type{other.rows[0]},
            row_type{other.rows[1]},
            row_type{other.rows[2]},
            row_type{other.rows[3]}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const mat_base<U, 2>& other): mat_base(
            row_type{other.rows[0], T{0}, T{0}},
            row_type{other.rows[1], T{0}, T{0}},
            row_type{T{0}, T{0}, T{1}, T{0}},
            row_type{T{0}, T{0}, T{0}, T{1}}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const mat_base<U, 3>& other): mat_base(
            row_type{other.rows[0], T{0}},
            row_type{other.rows[1], T{0}},
            row_type{other.rows[2], T{0}},
            row_type{T{0}, T{0}, T{0}, T{1}}) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit mat_base(const U* p): mat_base(
            row_type{p + 0u * row_type::size},
            row_type{p + 1u * row_type::size},
            row_type{p + 2u * row_type::size},
            row_type{p + 3u * row_type::size}) {}
    };
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class mat final : public detail::mat_base<T, Size> {
    public:
        using self_type = mat;
        using base_type = detail::mat_base<T, Size>;
        using component_type = T;

        using row_type = vec<T, Size>;

        using pointer = row_type*;
        using const_pointer = const row_type*;

        using reference = row_type&;
        using const_reference = const row_type&;

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        static inline constexpr std::size_t size = Size;
    public:
        using base_type::mat_base;
        using base_type::rows;

        // NOLINTNEXTLINE(*-noexcept-swap)
        void swap(mat& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < Size; ++i ) {
                using std::swap;
                swap(rows[i], other.rows[i]);
            }
        }

        [[nodiscard]] iterator begin() noexcept { return iterator(data()); }
        [[nodiscard]] const_iterator begin() const noexcept { return const_iterator(data()); }
        [[nodiscard]] iterator end() noexcept { return iterator(data() + Size); }
        [[nodiscard]] const_iterator end() const noexcept { return const_iterator(data() + Size); }

        [[nodiscard]] reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        [[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        [[nodiscard]] reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        [[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        [[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }
        [[nodiscard]] const_iterator cend() const noexcept { return end(); }
        [[nodiscard]] const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        [[nodiscard]] const_reverse_iterator crend() const noexcept { return rend(); }

        [[nodiscard]] pointer data() noexcept {
            return &rows[0];
        }

        [[nodiscard]] const_pointer data() const noexcept {
            return &rows[0];
        }

        [[nodiscard]] constexpr reference at(std::size_t index) {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("mat::at"));
            return rows[index];
        }

        [[nodiscard]] constexpr const_reference at(std::size_t index) const {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("mat::at"));
            return rows[index];
        }

        [[nodiscard]] constexpr reference operator[](std::size_t index) noexcept {
            return rows[index];
        }

        [[nodiscard]] constexpr const_reference operator[](std::size_t index) const noexcept {
            return rows[index];
        }
    };
}

namespace vmath_hpp
{
    // mat2

    template < typename T >
    mat(T, T, T, T) -> mat<T, 2>;

    template < typename T >
    mat(const vec<T, 2>&, const vec<T, 2>&) -> mat<T, 2>;

    template < typename T >
    mat(std::initializer_list<T>, std::initializer_list<T>) -> mat<T, 2>;

    // mat3

    template < typename T >
    mat(T, T, T, T, T, T, T, T, T) -> mat<T, 3>;

    template < typename T >
    mat(const vec<T, 3>&, const vec<T, 3>&, const vec<T, 3>&) -> mat<T, 3>;

    template < typename T >
    mat(const mat<T, 2>&, const vec<T, 2>&) -> mat<T, 3>;

    template < typename T >
    mat(std::initializer_list<T>, std::initializer_list<T>, std::initializer_list<T>) -> mat<T, 3>;

    // mat4

    template < typename T >
    mat(T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T) -> mat<T, 4>;

    template < typename T >
    mat(const vec<T, 4>&, const vec<T, 4>&, const vec<T, 4>&, const vec<T, 4>&) -> mat<T, 4>;

    template < typename T >
    mat(const mat<T, 3>&, const vec<T, 3>&) -> mat<T, 4>;

    template < typename T >
    mat(std::initializer_list<T>, std::initializer_list<T>, std::initializer_list<T>, std::initializer_list<T>) -> mat<T, 4>;

    // swap

    template < typename T, std::size_t Size >
    // NOLINTNEXTLINE(*-noexcept-swap)
    void swap(mat<T, Size>& l, mat<T, Size>& r) noexcept(noexcept(l.swap(r))) {
        l.swap(r);
    }
}

namespace vmath_hpp::detail::impl
{
    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const mat<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return mat{ f(a[Is])... };
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const mat<A, Size>& a,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return mat{ f(a[Is], b[Is])... };
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        A init,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return ((init = f(std::move(init), b[Is])), ...);
    }

    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const mat<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return (... && f(a[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const mat<A, Size>& a,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... && f(a[Is], b[Is]));
    }

    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const mat<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return (... || f(a[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const mat<A, Size>& a,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... || f(a[Is], b[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_plus_join_impl(
        F&& f, // NOLINT(*-missing-std-forward)
        const vec<A, Size>& a,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... + f(a[Is], b[Is]));
    }
}

namespace vmath_hpp::detail
{
    template < typename A, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const mat<A, Size>& a) {
        return impl::map_join_impl(std::forward<F>(f), a, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const mat<A, Size>& a, const mat<B, Size>& b) {
        return impl::map_join_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join(F&& f, A init, const mat<B, Size>& b) {
        return impl::fold_join_impl(std::forward<F>(f), std::move(init), b, std::make_index_sequence<Size>{});
    }

    template < typename A, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join(F&& f, const mat<A, Size>& a) {
        return impl::fold1_and_join_impl(std::forward<F>(f), a, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join(F&& f, const mat<A, Size>& a, const mat<B, Size>& b) {
        return impl::fold1_and_join_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }

    template < typename A, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join(F&& f, const mat<A, Size>& a) {
        return impl::fold1_or_join_impl(std::forward<F>(f), a, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join(F&& f, const mat<A, Size>& a, const mat<B, Size>& b) {
        return impl::fold1_or_join_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_plus_join(F&& f, const vec<A, Size>& a, const mat<B, Size>& b) {
        return impl::fold1_plus_join_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }
}

//
// Operators
//

namespace vmath_hpp
{
    // +operator

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator+(const mat<T, Size>& xs) {
        return map_join([](const vec<T, Size>& x){ return +x; }, xs);
    }

    // -operator

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator-(const mat<T, Size>& xs) {
        return map_join([](const vec<T, Size>& x){ return -x; }, xs);
    }

    // ~operator

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator~(const mat<T, Size>& xs) {
        return map_join([](const vec<T, Size>& x){ return ~x; }, xs);
    }

    // !operator

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator!(const mat<T, Size>& xs) {
        return map_join([](const vec<T, Size>& x){ return !x; }, xs);
    }

    // ++operator

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator++(mat<T, Size>& xs) {
        return (xs = xs + T{1});
    }

    // --operator

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator--(mat<T, Size>& xs) {
        return (xs = xs - T{1});
    }

    // operator++

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator++(mat<T, Size>& xs, int) {
        mat<T, Size> ys = xs;
        ++xs;
        return ys;
    }

    // operator--

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator--(mat<T, Size>& xs, int) {
        mat<T, Size> ys = xs;
        --xs;
        return ys;
    }

    // operator+

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator+(const mat<T, Size>& xs, U y) {
        return map_join([y](const vec<T, Size>& x){ return x + y; }, xs);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator+(T x, const mat<U, Size>& ys) {
        return map_join([x](const vec<U, Size>& y){ return x + y; }, ys);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator+(const mat<T, Size>& xs, const mat<U, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<U, Size>& y){ return x + y; }, xs, ys);
    }

    // operator+=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator+=(mat<T, Size>& xs, T y) {
        return (xs = (xs + y));
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator+=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs + ys));
    }

    // operator-

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator-(const mat<T, Size>& xs, U y) {
        return map_join([y](const vec<T, Size>& x){ return x - y; }, xs);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator-(T x, const mat<U, Size>& ys) {
        return map_join([x](const vec<U, Size>& y){ return x - y; }, ys);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator-(const mat<T, Size>& xs, const mat<U, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<U, Size>& y){ return x - y; }, xs, ys);
    }

    // operator-=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator-=(mat<T, Size>& xs, T y) {
        return (xs = (xs - y));
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator-=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs - ys));
    }

    // operator*

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator*(const mat<T, Size>& xs, U y) {
        return map_join([y](const vec<T, Size>& x){ return x * y; }, xs);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator*(T x, const mat<U, Size>& ys) {
        return map_join([x](const vec<U, Size>& y){ return x * y; }, ys);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator*(const vec<T, Size>& xs, const mat<U, Size>& ys) {
        return fold1_plus_join([](T x, const vec<U, Size>& y){ return x * y; }, xs, ys);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator*(const mat<T, Size>& xs, const mat<U, Size>& ys) {
        return map_join([&ys](const vec<T, Size>& x){ return x * ys; }, xs);
    }

    // operator*=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator*=(mat<T, Size>& xs, T y) {
        return (xs = (xs * y));
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator*=(vec<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs * ys));
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator*=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs * ys));
    }

    // operator/

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator/(const mat<T, Size>& xs, U y) {
        return map_join([y](const vec<T, Size>& x){ return x / y; }, xs);
    }

    template < typename T, typename U, std::size_t Size >
    [[nodiscard]] constexpr auto operator/(T x, const mat<U, Size>& ys) {
        return map_join([x](const vec<U, Size>& y){ return x / y; }, ys);
    }

    // operator/=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator/=(mat<T, Size>& xs, T y) {
        return (xs = (xs / y));
    }

    // operator&

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&(const mat<T, Size>& xs, T y) {
        return map_join([y](const vec<T, Size>& x){ return x & y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&(T x, const mat<T, Size>& ys) {
        return map_join([x](const vec<T, Size>& y){ return x & y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x & y; }, xs, ys);
    }

    // operator&=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator&=(mat<T, Size>& xs, T y) {
        return (xs = (xs & y));
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator&=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs & ys));
    }

    // operator|

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator|(const mat<T, Size>& xs, T y) {
        return map_join([y](const vec<T, Size>& x){ return x | y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator|(T x, const mat<T, Size>& ys) {
        return map_join([x](const vec<T, Size>& y){ return x | y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator|(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x | y; }, xs, ys);
    }

    // operator|=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator|=(mat<T, Size>& xs, T y) {
        return (xs = (xs | y));
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator|=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs | ys));
    }

    // operator^

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator^(const mat<T, Size>& xs, T y) {
        return map_join([y](const vec<T, Size>& x){ return x ^ y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator^(T x, const mat<T, Size>& ys) {
        return map_join([x](const vec<T, Size>& y){ return x ^ y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator^(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x ^ y; }, xs, ys);
    }

    // operator^=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator^=(mat<T, Size>& xs, T y) {
        return (xs = (xs ^ y));
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator^=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs ^ ys));
    }

    // operator<<

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator<<(const mat<T, Size>& xs, T y) {
        return map_join([y](const vec<T, Size>& x){ return x << y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator<<(T x, const mat<T, Size>& ys) {
        return map_join([x](const vec<T, Size>& y){ return x << y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator<<(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x << y; }, xs, ys);
    }

    // operator<<=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator<<=(mat<T, Size>& xs, T y) {
        return (xs = (xs << y));
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator<<=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs << ys));
    }

    // operator>>

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator>>(const mat<T, Size>& xs, T y) {
        return map_join([y](const vec<T, Size>& x){ return x >> y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator>>(T x, const mat<T, Size>& ys) {
        return map_join([x](const vec<T, Size>& y){ return x >> y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator>>(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x >> y; }, xs, ys);
    }

    // operator>>=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator>>=(mat<T, Size>& xs, T y) {
        return (xs = (xs >> y));
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator>>=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = (xs >> ys));
    }

    // operator&&

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&&(const mat<T, Size>& xs, T y) {
        return map_join([y](const vec<T, Size>& x){ return x && y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&&(T x, const mat<T, Size>& ys) {
        return map_join([x](const vec<T, Size>& y){ return x && y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator&&(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x && y; }, xs, ys);
    }

    // operator||

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator||(const mat<T, Size>& xs, T y) {
        return map_join([y](const vec<T, Size>& x){ return x || y; }, xs);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator||(T x, const mat<T, Size>& ys) {
        return map_join([x](const vec<T, Size>& y){ return x || y; }, ys);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr auto operator||(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x || y; }, xs, ys);
    }

    // operator==

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr bool operator==(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return fold1_and_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x == y; }, xs, ys);
    }

    // operator!=

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr bool operator!=(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return fold1_or_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return x != y; }, xs, ys);
    }

    // operator<

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr bool operator<(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        for ( std::size_t i = 0; i < Size; ++i ) {
            if ( xs[i] < ys[i] ) {
                return true;
            }
            if ( ys[i] < xs[i] ) {
                return false;
            }
        }
        return false;
    }
}

//
// Relational Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size
             , typename U = decltype(any(std::declval<vec<T, Size>>())) >
    [[nodiscard]] constexpr U any(const mat<T, Size>& xs) {
        return fold1_or_join([](const vec<T, Size>& x){ return any(x); }, xs);
    }

    template < typename T, std::size_t Size
             , typename U = decltype(all(std::declval<vec<T, Size>>())) >
    [[nodiscard]] constexpr U all(const mat<T, Size>& xs) {
        return fold1_and_join([](const vec<T, Size>& x){ return all(x); }, xs);
    }

    template < typename T, std::size_t Size
             , typename U = typename decltype(approx(
                 std::declval<vec<T, Size>>(),
                 std::declval<vec<T, Size>>()))::component_type >
    [[nodiscard]] constexpr mat<U, Size> approx(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return approx(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = typename decltype(approx(
                 std::declval<vec<T, Size>>(),
                 std::declval<vec<T, Size>>(),
                 std::declval<T>()))::component_type >
    [[nodiscard]] constexpr mat<U, Size> approx(const mat<T, Size>& xs, const mat<T, Size>& ys, T epsilon) {
        return map_join([epsilon](const vec<T, Size>& x, const vec<T, Size>& y){ return approx(x, y, epsilon); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = typename decltype(less(
                 std::declval<vec<T, Size>>(),
                 std::declval<vec<T, Size>>()))::component_type >
    [[nodiscard]] constexpr mat<U, Size> less(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return less(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = typename decltype(less_equal(
                 std::declval<vec<T, Size>>(),
                 std::declval<vec<T, Size>>()))::component_type >
    [[nodiscard]] constexpr mat<U, Size> less_equal(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return less_equal(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = typename decltype(greater(
                 std::declval<vec<T, Size>>(),
                 std::declval<vec<T, Size>>()))::component_type >
    [[nodiscard]] constexpr mat<U, Size> greater(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return greater(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = typename decltype(greater_equal(
                 std::declval<vec<T, Size>>(),
                 std::declval<vec<T, Size>>()))::component_type >
    [[nodiscard]] constexpr mat<U, Size> greater_equal(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return greater_equal(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = typename decltype(equal_to(
                 std::declval<vec<T, Size>>(),
                 std::declval<vec<T, Size>>()))::component_type >
    [[nodiscard]] constexpr mat<U, Size> equal_to(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return equal_to(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size
             , typename U = typename decltype(not_equal_to(
                 std::declval<vec<T, Size>>(),
                 std::declval<vec<T, Size>>()))::component_type >
    [[nodiscard]] constexpr mat<U, Size> not_equal_to(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return map_join([](const vec<T, Size>& x, const vec<T, Size>& y){ return not_equal_to(x, y); }, xs, ys);
    }
}

//
// Matrix Functions
//

namespace vmath_hpp
{
    //
    // transpose
    //

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> transpose(const mat<T, 2>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1],
                c = _m[1][0], d = _m[1][1];
        return {
            a, c,
            b, d};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> transpose(const mat<T, 3>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1], c = _m[0][2],
                d = _m[1][0], e = _m[1][1], f = _m[1][2],
                g = _m[2][0], h = _m[2][1], i = _m[2][2];
        return {
            a, d, g,
            b, e, h,
            c, f, i};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> transpose(const mat<T, 4>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1], c = _m[0][2], d = _m[0][3],
                e = _m[1][0], f = _m[1][1], g = _m[1][2], h = _m[1][3],
                i = _m[2][0], j = _m[2][1], k = _m[2][2], l = _m[2][3],
                m = _m[3][0], n = _m[3][1], o = _m[3][2], p = _m[3][3];
        return {
            a, e, i, m,
            b, f, j, n,
            c, g, k, o,
            d, h, l, p};
    }

    //
    // adjugate
    //

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> adjugate(const mat<T, 2>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1],
                c = _m[1][0], d = _m[1][1];
        return {
            +d,
            -b,
            -c,
            +a};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> adjugate(const mat<T, 3>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1], c = _m[0][2],
                d = _m[1][0], e = _m[1][1], f = _m[1][2],
                g = _m[2][0], h = _m[2][1], i = _m[2][2];
        return {
            e * i - f * h,
            c * h - b * i,
            b * f - c * e,
            f * g - d * i,
            a * i - c * g,
            c * d - a * f,
            d * h - e * g,
            b * g - a * h,
            a * e - b * d};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> adjugate(const mat<T, 4>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1], c = _m[0][2], d = _m[0][3],
                e = _m[1][0], f = _m[1][1], g = _m[1][2], h = _m[1][3],
                i = _m[2][0], j = _m[2][1], k = _m[2][2], l = _m[2][3],
                m = _m[3][0], n = _m[3][1], o = _m[3][2], p = _m[3][3];
        return {
            f * (k * p - l * o) + g * (l * n - j * p) + h * (j * o - k * n),
            j * (c * p - d * o) + k * (d * n - b * p) + l * (b * o - c * n),
            n * (c * h - d * g) + o * (d * f - b * h) + p * (b * g - c * f),
            b * (h * k - g * l) + c * (f * l - h * j) + d * (g * j - f * k),
            g * (i * p - l * m) + h * (k * m - i * o) + e * (l * o - k * p),
            k * (a * p - d * m) + l * (c * m - a * o) + i * (d * o - c * p),
            o * (a * h - d * e) + p * (c * e - a * g) + m * (d * g - c * h),
            c * (h * i - e * l) + d * (e * k - g * i) + a * (g * l - h * k),
            h * (i * n - j * m) + e * (j * p - l * n) + f * (l * m - i * p),
            l * (a * n - b * m) + i * (b * p - d * n) + j * (d * m - a * p),
            p * (a * f - b * e) + m * (b * h - d * f) + n * (d * e - a * h),
            d * (f * i - e * j) + a * (h * j - f * l) + b * (e * l - h * i),
            e * (k * n - j * o) + f * (i * o - k * m) + g * (j * m - i * n),
            i * (c * n - b * o) + j * (a * o - c * m) + k * (b * m - a * n),
            m * (c * f - b * g) + n * (a * g - c * e) + o * (b * e - a * f),
            a * (f * k - g * j) + b * (g * i - e * k) + c * (e * j - f * i)};
    }

    //
    // determinant
    //

    template < typename T >
    [[nodiscard]] constexpr T determinant(const mat<T, 2>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1],
                c = _m[1][0], d = _m[1][1];
        return
            a * d - b * c;
    }

    template < typename T >
    [[nodiscard]] constexpr T determinant(const mat<T, 3>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1], c = _m[0][2],
                d = _m[1][0], e = _m[1][1], f = _m[1][2],
                g = _m[2][0], h = _m[2][1], i = _m[2][2];
        return
            + a * (e * i - f * h)
            - b * (d * i - f * g)
            + c * (d * h - e * g);
    }

    template < typename T >
    [[nodiscard]] constexpr T determinant(const mat<T, 4>& _m) {
        // NOLINTNEXTLINE(*-isolate-declaration)
        const T a = _m[0][0], b = _m[0][1], c = _m[0][2], d = _m[0][3],
                e = _m[1][0], f = _m[1][1], g = _m[1][2], h = _m[1][3],
                i = _m[2][0], j = _m[2][1], k = _m[2][2], l = _m[2][3],
                m = _m[3][0], n = _m[3][1], o = _m[3][2], p = _m[3][3];
        return
            + a * (f * (k * p - l * o) - (j * (g * p - h * o)) + (n * (g * l - h * k)))
            - b * (e * (k * p - l * o) - (i * (g * p - h * o)) + (m * (g * l - h * k)))
            + c * (e * (j * p - l * n) - (i * (f * p - h * n)) + (m * (f * l - h * j)))
            - d * (e * (j * o - k * n) - (i * (f * o - g * n)) + (m * (f * k - g * j)));
    }

    //
    // inverse
    //

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> inverse(const mat<T, Size>& m) {
        return adjugate(m) * rcp(determinant(m));
    }
}

namespace vmath_hpp::detail
{
    template < typename T >
    class qua_base {
    public:
        vec<T, 3> v{no_init};
        T s;
    public:
        constexpr qua_base()
        : qua_base(identity_init) {}

        constexpr qua_base(no_init_t) {}
        constexpr qua_base(zero_init_t) : qua_base{zero_init, T{0}} {}
        constexpr qua_base(identity_init_t) : qua_base{zero_init, T{1}} {}

        constexpr qua_base(T vx, T vy, T vz, T s): v{vx, vy, vz}, s{s} {}
        constexpr qua_base(const vec<T, 3>& v, T s): v{v}, s{s} {}
        constexpr explicit qua_base(const vec<T, 4>& vs): v{vs[0], vs[1], vs[2]}, s{vs[3]} {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr qua_base(const qua_base<U>& other): qua_base(other.v, other.s) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<T, U>, int> = 0 >
        constexpr explicit operator vec<U, 4>() const { return vec<U, 4>(v, s); }

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        // NOLINTNEXTLINE(*-pointer-arithmetic)
        constexpr explicit qua_base(const U* p): qua_base(p[0], p[1], p[2], p[3]) {}

        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return v.x;
            case 1: return v.y;
            case 2: return v.z;
            case 3: return s;
            }
        }

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return v.x;
            case 1: return v.y;
            case 2: return v.z;
            case 3: return s;
            }
        }
    };
}

namespace vmath_hpp
{
    template < typename T >
    class qua final : public detail::qua_base<T> {
    public:
        using self_type = qua;
        using base_type = detail::qua_base<T>;
        using component_type = T;

        using imag_type = vec<T, 3>;
        using real_type = T;

        using pointer = component_type*;
        using const_pointer = const component_type*;

        using reference = component_type&;
        using const_reference = const component_type&;

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        static inline constexpr std::size_t size = 4;
    public:
        using base_type::qua_base;
        using base_type::operator[];

        // NOLINTNEXTLINE(*-noexcept-swap)
        void swap(qua& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < size; ++i ) {
                using std::swap;
                swap((*this)[i], other[i]);
            }
        }

        [[nodiscard]] iterator begin() noexcept { return iterator(data()); }
        [[nodiscard]] const_iterator begin() const noexcept { return const_iterator(data()); }
        [[nodiscard]] iterator end() noexcept { return iterator(data() + size); }
        [[nodiscard]] const_iterator end() const noexcept { return const_iterator(data() + size); }

        [[nodiscard]] reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        [[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        [[nodiscard]] reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        [[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        [[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }
        [[nodiscard]] const_iterator cend() const noexcept { return end(); }
        [[nodiscard]] const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        [[nodiscard]] const_reverse_iterator crend() const noexcept { return rend(); }

        [[nodiscard]] pointer data() noexcept {
            return &(*this)[0];
        }

        [[nodiscard]] const_pointer data() const noexcept {
            return &(*this)[0];
        }

        [[nodiscard]] constexpr reference at(std::size_t index) {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("qua::at"));
            return (*this)[index];
        }

        [[nodiscard]] constexpr const_reference at(std::size_t index) const {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("qua::at"));
            return (*this)[index];
        }
    };
}

namespace vmath_hpp
{
    // vec

    template < typename T >
    vec(const qua<T>&) -> vec<T, 4>;

    // qua

    template < typename T >
    qua(T, T, T, T) -> qua<T>;

    template < typename T >
    qua(const vec<T, 3>&, T) -> qua<T>;

    template < typename T >
    qua(const vec<T, 4>&) -> qua<T>;

    template < typename T >
    qua(std::initializer_list<T>) -> qua<T>;

    // swap

    template < typename T >
    // NOLINTNEXTLINE(*-noexcept-swap)
    void swap(qua<T>& l, qua<T>& r) noexcept(noexcept(l.swap(r))) {
        l.swap(r);
    }
}

namespace vmath_hpp::detail
{
    template < typename A, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(F&& f, const qua<A>& a) {
        return qua(map_join(std::forward<F>(f), vec{a}));
    }

    template < typename A, typename B, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join(F&& f, A init, const qua<B>& b) {
        return fold_join(std::forward<F>(f), std::move(init), vec{b});
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
        }

        // use linear interpolation for small angles
        const T xs_scale = T{1} - a;
        const T ys_scale = a * raw_cos_theta_sign;
        return normalize(lerp(unit_xs, unit_ys, xs_scale, ys_scale));
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

//
// Units
//

namespace vmath_hpp
{
    template < typename T > inline constexpr vec<T, 2> zero2{zero_init};
    template < typename T > inline constexpr vec<T, 3> zero3{zero_init};
    template < typename T > inline constexpr vec<T, 4> zero4{zero_init};

    template < typename T > inline constexpr vec<T, 2> unit2{unit_init};
    template < typename T > inline constexpr vec<T, 3> unit3{unit_init};
    template < typename T > inline constexpr vec<T, 4> unit4{unit_init};

    template < typename T > inline constexpr vec<T, 2> unit2_x{T{1}, T{0}};
    template < typename T > inline constexpr vec<T, 2> unit2_y{T{0}, T{1}};

    template < typename T > inline constexpr vec<T, 3> unit3_x{T{1}, T{0}, T{0}};
    template < typename T > inline constexpr vec<T, 3> unit3_y{T{0}, T{1}, T{0}};
    template < typename T > inline constexpr vec<T, 3> unit3_z{T{0}, T{0}, T{1}};

    template < typename T > inline constexpr vec<T, 4> unit4_x{T{1}, T{0}, T{0}, T{0}};
    template < typename T > inline constexpr vec<T, 4> unit4_y{T{0}, T{1}, T{0}, T{0}};
    template < typename T > inline constexpr vec<T, 4> unit4_z{T{0}, T{0}, T{1}, T{0}};
    template < typename T > inline constexpr vec<T, 4> unit4_w{T{0}, T{0}, T{0}, T{1}};

    template < typename T > inline constexpr mat<T, 2> mzero2{zero_init};
    template < typename T > inline constexpr mat<T, 3> mzero3{zero_init};
    template < typename T > inline constexpr mat<T, 4> mzero4{zero_init};

    template < typename T > inline constexpr mat<T, 2> munit2{unit_init};
    template < typename T > inline constexpr mat<T, 3> munit3{unit_init};
    template < typename T > inline constexpr mat<T, 4> munit4{unit_init};

    template < typename T > inline constexpr mat<T, 2> midentity2{identity_init};
    template < typename T > inline constexpr mat<T, 3> midentity3{identity_init};
    template < typename T > inline constexpr mat<T, 4> midentity4{identity_init};

    template < typename T > inline constexpr qua<T> qzero{zero_init};
    template < typename T > inline constexpr qua<T> qidentity{identity_init};
}

//
// Hash
//

namespace vmath_hpp::detail
{
    struct hash_combiner {
        template < typename T >
        [[nodiscard]] std::size_t operator()(std::size_t seed, const T& x) const noexcept {
            return (seed ^= std::hash<T>{}(x) + 0x9e3779b9 + (seed << 6) + ( seed >> 2));
        }
    };

    template < typename T, std::size_t Size >
    [[nodiscard]] std::size_t hash(const vec<T, Size>& v) noexcept {
        return fold_join(hash_combiner{}, std::size_t{}, v);
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] std::size_t hash(const mat<T, Size>& m) noexcept {
        return fold_join(hash_combiner{}, std::size_t{}, m);
    }

    template < typename T >
    [[nodiscard]] std::size_t hash(const qua<T>& q) noexcept {
        return fold_join(hash_combiner{}, std::size_t{}, q);
    }
}

namespace std
{
    template < typename T, size_t Size >
    struct hash<vmath_hpp::vec<T, Size>> {
        size_t operator()(const vmath_hpp::vec<T, Size>& v) const noexcept {
            return vmath_hpp::detail::hash(v);
        }
    };

    template < typename T, size_t Size >
    struct hash<vmath_hpp::mat<T, Size>> {
        size_t operator()(const vmath_hpp::mat<T, Size>& m) const noexcept {
            return vmath_hpp::detail::hash(m);
        }
    };

    template < typename T >
    struct hash<vmath_hpp::qua<T>> {
        size_t operator()(const vmath_hpp::qua<T>& q) const noexcept {
            return vmath_hpp::detail::hash(q);
        }
    };
}

//
// Cast
//

namespace vmath_hpp
{
    template < typename To, typename From >
    [[nodiscard]] std::enable_if_t<
        std::is_arithmetic_v<To> && std::is_arithmetic_v<From>
    , To>
    constexpr cast_to(From x) noexcept {
        return static_cast<To>(x);
    }

    template < typename To, typename From, std::size_t Size >
    [[nodiscard]] constexpr vec<To, Size> cast_to(const vec<From, Size>& v) {
        return map_join([](From x){ return cast_to<To>(x); }, v);
    }

    template < typename To, typename From, std::size_t Size >
    [[nodiscard]] constexpr mat<To, Size> cast_to(const mat<From, Size>& m) {
        return map_join([](const vec<From, Size>& v){ return cast_to<To>(v); }, m);
    }

    template < typename To, typename From >
    [[nodiscard]] constexpr qua<To> cast_to(const qua<From>& q) {
        return map_join([](From x){ return cast_to<To>(x); }, q);
    }
}

//
// Access
//

namespace vmath_hpp
{
    // component

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T component(const vec<T, Size>& v, std::size_t index) {
        return v[index];
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> component(const vec<T, Size>& v, std::size_t index, T component) {
        vec vv = v;
        vv[index] = component;
        return vv;
    }

    // row

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> row(const mat<T, Size>& m, std::size_t index) {
        return m.rows[index];
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> row(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& row) {
        mat mm = m;
        mm[index] = row;
        return mm;
    }

    // column

    namespace impl
    {
        template < typename T, std::size_t Size, std::size_t... Is >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        vec<T, Size> column_impl(const mat<T, Size>& m, std::size_t index, std::index_sequence<Is...>) {
            return { m[Is][index]... };
        }

        template < typename T, std::size_t Size, std::size_t... Is >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        mat<T, Size> column_impl(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& column, std::index_sequence<Is...>) {
            return { component(m[Is], index, column[Is])... };
        }
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> column(const mat<T, Size>& m, std::size_t index) {
        return impl::column_impl(m, index, std::make_index_sequence<Size>{});
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> column(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& column) {
        return impl::column_impl(m, index, column, std::make_index_sequence<Size>{});
    }

    // diagonal

    namespace impl
    {
        template < typename T, std::size_t Size, std::size_t... Is >
        [[nodiscard]] constexpr vec<T, Size> diagonal_impl(const mat<T, Size>& m, std::index_sequence<Is...>) {
            return { m[Is][Is]... };
        }

        template < typename T, std::size_t Size, std::size_t... Is >
        [[nodiscard]] constexpr mat<T, Size> diagonal_impl(const mat<T, Size>& m, const vec<T, Size>& diagonal, std::index_sequence<Is...>) {
            return { component(m[Is], Is, diagonal[Is])... };
        }
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> diagonal(const mat<T, Size>& m) {
        return impl::diagonal_impl(m, std::make_index_sequence<Size>{});
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> diagonal(const mat<T, Size>& m, const vec<T, Size>& diagonal) {
        return impl::diagonal_impl(m, diagonal, std::make_index_sequence<Size>{});
    }

    // real

    template < typename T >
    [[nodiscard]] constexpr T real(const qua<T>& q) {
        return q.s;
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> real(qua<T> q, T real) {
        q.s = real;
        return q;
    }

    // imag

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> imag(const qua<T>& q) {
        return q.v;
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> imag(qua<T> q, const vec<T, 3>& imag) {
        q.v = imag;
        return q;
    }
}

//
// Matrix Transform 3D
//

namespace vmath_hpp
{
    // trs

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> trs(const vec<T, 3>& t, const mat<T, 3>& r) {
        return {
            { r[0], T{0} },
            { r[1], T{0} },
            { r[2], T{0} },
            { t,    T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> trs(const vec<T, 3>& t, const mat<T, 3>& r, const vec<T, 3>& s) {
        return {
            { r[0] * s[0], T{0} },
            { r[1] * s[1], T{0} },
            { r[2] * s[2], T{0} },
            { t,           T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> trs(const vec<T, 3>& t, const qua<T>& r) {
        return trs(t, rotate(r));
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> trs(const vec<T, 3>& t, const qua<T>& r, const vec<T, 3>& s) {
        return trs(t, rotate(r), s);
    }

    // translate

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> translate(const vec<T, 3>& v) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Translation_(geometry)

        return {
            { T{1}, T{0}, T{0}, T{0} },
            { T{0}, T{1}, T{0}, T{0} },
            { T{0}, T{0}, T{1}, T{0} },
            { v.x,  v.y,  v.z,  T{1} }};
    }

    // rotate

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate(const qua<T>& q) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/

        const auto [qv, qs] = normalize(q);

        const T x2 = qv.x * T{2};
        const T y2 = qv.y * T{2};
        const T z2 = qv.z * T{2};

        const T sx2 = qs * x2;
        const T sy2 = qs * y2;
        const T sz2 = qs * z2;

        const T xx2 = qv.x * x2;
        const T xy2 = qv.x * y2;
        const T xz2 = qv.x * z2;

        const T yy2 = qv.y * y2;
        const T yz2 = qv.y * z2;
        const T zz2 = qv.z * z2;

        return {
            { T{1} - (yy2 + zz2), (xy2 + sz2),        (xz2 - sy2)        },
            { (xy2 - sz2),        T{1} - (xx2 + zz2), (yz2 + sx2)        },
            { (xz2 + sy2),        (yz2 - sx2),        T{1} - (xx2 + yy2) }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> rotate4(const qua<T>& q) {
        return mat<T, 4>(rotate(q));
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate(T angle, const vec<T, 3>& axis) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/

        const auto [s, c] = sincos(angle);
        const auto [x, y, z] = normalize(axis);

        const T xx = x * x;
        const T yy = y * y;
        const T zz = z * z;

        const T xs = x * s;
        const T ys = y * s;
        const T zs = z * s;

        const T ic = T{1} - c;

        const T xxm = xx * ic;
        const T yym = yy * ic;
        const T zzm = zz * ic;

        const T xym = x * y * ic;
        const T xzm = x * z * ic;
        const T yzm = y * z * ic;

        return {
            { xxm + c,  xym + zs, xzm - ys },
            { xym - zs, yym + c,  yzm + xs },
            { xzm + ys, yzm - xs, zzm + c  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> rotate4(T angle, const vec<T, 3>& axis) {
        return mat<T, 4>(rotate(angle, axis));
    }

    // rotate_x

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_x(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);

        return {
            { T{1}, T{0}, T{0} },
            { T{0},   c,    s  },
            { T{0},  -s,    c  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> rotate4_x(T angle) {
        return mat<T, 4>(rotate_x(angle));
    }

    // rotate_y

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_y(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);

        return {
            {   c,  T{0},  -s  },
            { T{0}, T{1}, T{0} },
            {   s,  T{0},   c  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> rotate4_y(T angle) {
        return mat<T, 4>(rotate_y(angle));
    }

    // rotate_z

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_z(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);

        return {
            {   c,    s,  T{0} },
            {  -s,    c,  T{0} },
            { T{0}, T{0}, T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> rotate4_z(T angle) {
        return mat<T, 4>(rotate_z(angle));
    }

    // scale

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(const vec<T, 3>& v) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Scaling_(geometry)

        return {
            { v.x,  T{0}, T{0} },
            { T{0}, v.y,  T{0} },
            { T{0}, T{0}, v.z  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> scale4(const vec<T, 3>& v) {
        return mat<T, 4>(scale(v));
    }

    // look_at

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> look_at_lh(
        const vec<T, 3>& dir,
        const vec<T, 3>& up)
    {
        /// REFERENCE:
        /// https://www.euclideanspace.com/maths/algebra/vectors/lookat/

        const vec az = normalize(dir);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        return {
            { ax.x, ay.x, az.x },
            { ax.y, ay.y, az.y },
            { ax.z, ay.z, az.z }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> look_at_lh(
        const vec<T, 3>& eye,
        const vec<T, 3>& at,
        const vec<T, 3>& up)
    {
        /// REFERENCE:
        /// https://www.euclideanspace.com/maths/algebra/vectors/lookat/

        const vec az = normalize(at - eye);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        const T dx = dot(ax, eye);
        const T dy = dot(ay, eye);
        const T dz = dot(az, eye);

        return {
            { ax.x, ay.x, az.x, T{0} },
            { ax.y, ay.y, az.y, T{0} },
            { ax.z, ay.z, az.z, T{0} },
            { -dx,  -dy,  -dz,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> look_at_rh(
        const vec<T, 3>& dir,
        const vec<T, 3>& up)
    {
        /// REFERENCE:
        /// https://www.euclideanspace.com/maths/algebra/vectors/lookat/

        const vec az = normalize(-dir);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        return {
            { ax.x, ay.x, az.x },
            { ax.y, ay.y, az.y },
            { ax.z, ay.z, az.z }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> look_at_rh(
        const vec<T, 3>& eye,
        const vec<T, 3>& at,
        const vec<T, 3>& up)
    {
        /// REFERENCE:
        /// https://www.euclideanspace.com/maths/algebra/vectors/lookat/

        const vec az = normalize(eye - at);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        const T dx = dot(ax, eye);
        const T dy = dot(ay, eye);
        const T dz = dot(az, eye);

        return {
            { ax.x, ay.x, az.x, T{0} },
            { ax.y, ay.y, az.y, T{0} },
            { ax.z, ay.z, az.z, T{0} },
            { -dx,  -dy,  -dz,  T{1} }};
    }
}

//
// Matrix Transform 2D
//

namespace vmath_hpp
{
    // trs

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> trs(const vec<T, 2>& t, const mat<T, 2>& r) {
        return {
            { r[0], T{0} },
            { r[1], T{0} },
            { t,    T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> trs(const vec<T, 2>& t, const mat<T, 2>& r, const vec<T, 2>& s) {
        return {
            { r[0] * s[0], T{0} },
            { r[1] * s[1], T{0} },
            { t,           T{1} }};
    }

    // translate

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> translate(const vec<T, 2>& v) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Translation_(geometry)

        return {
            { T{1}, T{0}, T{0} },
            { T{0}, T{1}, T{0} },
            { v.x,  v.y,  T{1} }};
    }

    // rotate

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> rotate(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);

        return {
            {  c, s },
            { -s, c }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate3(T angle) {
        return mat<T, 3>(rotate(angle));
    }

    // scale

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> scale(const vec<T, 2>& v) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Scaling_(geometry)

        return {
            { v.x,  T{0} },
            { T{0}, v.y  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale3(const vec<T, 2>& v) {
        return mat<T, 3>(scale(v));
    }

    // shear

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear(const vec<T, 2>& v) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Shear_matrix

        return {
            { T{1}, v.y  },
            { v.x,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear3(const vec<T, 2>& v) {
        return mat<T, 3>(shear(v));
    }
}

//
// Matrix Projections
//

namespace vmath_hpp
{
    // orthographic

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> orthographic_lh(T width, T height, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixortholh

        const T rwidth = rcp(width);
        const T rheight = rcp(height);
        const T frange = rcp(zfar - znear);

        const T sx = T{2} * rwidth;
        const T sy = T{2} * rheight;
        const T sz = frange;
        const T tz = -frange * znear;

        return {
            {  sx,   T{0},  T{0},  T{0} },
            { T{0},   sy,   T{0},  T{0} },
            { T{0},  T{0},   sz,   T{0} },
            { T{0},  T{0},   tz,   T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> orthographic_rh(T width, T height, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixorthorh

        const T rwidth = rcp(width);
        const T rheight = rcp(height);
        const T frange = rcp(znear - zfar);

        const T sx = T{2} * rwidth;
        const T sy = T{2} * rheight;
        const T sz = frange;
        const T tz = frange * znear;

        return {
            {  sx,  T{0}, T{0}, T{0} },
            { T{0},  sy,  T{0}, T{0} },
            { T{0}, T{0},  sz,  T{0} },
            { T{0}, T{0},  tz,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> orthographic_lh(T left, T right, T bottom, T top, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixorthooffcenterlh

        const T rwidth = rcp(right - left);
        const T rheight = rcp(top - bottom);
        const T frange = rcp(zfar - znear);

        return {
            { T{2} * rwidth,            T{0},                      T{0},            T{0} },
            { T{0},                     T{2} * rheight,            T{0},            T{0} },
            { T{0},                     T{0},                      frange,          T{0} },
            { -(left + right) * rwidth, -(top + bottom) * rheight, -frange * znear, T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> orthographic_rh(T left, T right, T bottom, T top, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixorthooffcenterrh

        const T rwidth = rcp(right - left);
        const T rheight = rcp(top - bottom);
        const T frange = rcp(znear - zfar);

        return {
            { T{2} * rwidth,            T{0},                      T{0},           T{0} },
            { T{0},                     T{2} * rheight,            T{0},           T{0} },
            { T{0},                     T{0},                      frange,         T{0} },
            { -(left + right) * rwidth, -(top + bottom) * rheight, frange * znear, T{1} }};
    }

    // perspective

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_lh(T width, T height, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectivelh

        const T sx = T{2} * znear * rcp(width);
        const T sy = T{2} * znear * rcp(height);
        const T sz = zfar * rcp(zfar - znear);
        const T tz = (znear * zfar) * rcp(znear - zfar);

        return {
            { T{sx}, T{0},  T{0},  T{0} },
            { T{0},  T{sy}, T{0},  T{0} },
            { T{0},  T{0},  T{sz}, T{1} },
            { T{0},  T{0},  T{tz}, T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_rh(T width, T height, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectiverh

        const T sx = T{2} * znear * rcp(width);
        const T sy = T{2} * znear * rcp(height);
        const T sz = zfar * rcp(znear - zfar);
        const T tz = (znear * zfar) * rcp(znear - zfar);

        return {
            {  sx,  T{0}, T{0},  T{0} },
            { T{0},  sy,  T{0},  T{0} },
            { T{0}, T{0},  sz,  -T{1} },
            { T{0}, T{0},  tz,   T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_lh(T left, T right, T bottom, T top, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectiveoffcenterlh

        const T znear2 = T{2} * znear;
        const T rwidth = rcp(right - left);
        const T rheight = rcp(top - bottom);
        const T frange = zfar * rcp(zfar - znear);

        return {
            { znear2 * rwidth,          T{0},                      T{0},            T{0} },
            { T{0},                     znear2 * rheight,          T{0},            T{0} },
            { -(left + right) * rwidth, -(top + bottom) * rheight, frange,          T{1} },
            { T{0},                     T{0},                      -frange * znear, T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_rh(T left, T right, T bottom, T top, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectiveoffcenterrh

        const T znear2 = T{2} * znear;
        const T rwidth = rcp(right - left);
        const T rheight = rcp(top - bottom);
        const T frange = zfar * rcp(znear - zfar);

        return {
            { znear2 * rwidth,         T{0},                     T{0},            T{0} },
            { T{0},                    znear2 * rheight,         T{0},            T{0} },
            { (left + right) * rwidth, (top + bottom) * rheight, frange,         -T{1} },
            { T{0},                    T{0},                     frange * znear,  T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_fov_lh(T fovy, T aspect, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectivefovlh

        const T sy = rcp(tan(fovy * T{0.5f}));
        const T sx = sy * rcp(aspect);
        const T sz = zfar * rcp(zfar - znear);
        const T tz = (znear * zfar) * rcp(znear - zfar);

        return {
            {  sx,  T{0}, T{0}, T{0} },
            { T{0},  sy,  T{0}, T{0} },
            { T{0}, T{0},  sz,  T{1} },
            { T{0}, T{0},  tz,  T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_fov_rh(T fovy, T aspect, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectivefovrh

        const T sy = rcp(tan(fovy * T{0.5f}));
        const T sx = sy * rcp(aspect);
        const T sz = zfar * rcp(znear - zfar);
        const T tz = (znear * zfar) * rcp(znear - zfar);
        return  {
            {  sx,  T{0}, T{0},  T{0} },
            { T{0},  sy,  T{0},  T{0} },
            { T{0}, T{0},  sz,  -T{1} },
            { T{0}, T{0},  tz,   T{0} }};
    }
}

//
// Vector Transform
//

namespace vmath_hpp
{
    // angle

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T angle(const vec<T, Size>& x, const vec<T, Size>& y) {
        const T rs = rsqrt(length2(x) * length2(y));
        return acos(clamp(dot(x, y) * rs, -T{1}, T{1}));
    }

    // rotate

    template < typename T >
    [[nodiscard]] constexpr vec<T, 2> rotate(const vec<T, 2>& v, T angle) {
        return v * rotate(angle);
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate_x(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_x<T>);
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate_y(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_y<T>);
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate_z(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_z<T>);
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate(const vec<T, 3>& v, T angle, const vec<T, 3>& axis) {
        return v * qrotate(angle, axis);
    }

    // project

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> project(const vec<T, Size>& v, const vec<T, Size>& normal) {
        return dot(v, normal) * rlength2(normal) * normal;
    }

    // perpendicular

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> perpendicular(const vec<T, Size>& v, const vec<T, Size>& normal) {
        return v - project(v, normal);
    }
}

//
// Quaternion Transform
//

namespace vmath_hpp
{
    // qrotate

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(const mat<T, 3>& m) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/

        auto xyzw = T{0.5f} * sqrt(max(T{0}, vec{
            T{1} + m[0][0] - m[1][1] - m[2][2],
            T{1} - m[0][0] + m[1][1] - m[2][2],
            T{1} - m[0][0] - m[1][1] + m[2][2],
            T{1} + m[0][0] + m[1][1] + m[2][2]}));

        return qua(copysign(xyzw, {
            m[1][2] - m[2][1],
            m[2][0] - m[0][2],
            m[0][1] - m[1][0],
            T{1}}));
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(const vec<T, 3>& from, const vec<T, 3>& to) {
        /// REFERENCE:
        /// http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final

        const T n = sqrt(length2(from) * length2(to));
        const T s = dot(from, to) + n;

        if ( s < T{0.000001f} * n ) {
            return abs(from.z) < abs(from.x)
                ? normalize(qua{vec{-from.y, from.x, T{0}}, T{0}})
                : normalize(qua{vec{T{0}, -from.z, from.y}, T{0}});
        }

        return normalize(qua{cross(from, to), s});
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(T angle, const vec<T, 3>& axis) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T{0.5f});
        const auto [x, y, z] = normalize(axis);

        return {vec{x, y, z} * s, c};
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_x(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T{0.5f});

        return {vec{s, T{0}, T{0}}, c};
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_y(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T{0.5f});

        return {vec{T{0}, s, T{0}}, c};
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_z(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T{0.5f});

        return {vec{T{0}, T{0}, s}, c};
    }

    // qlook_at

    template < typename T >
    [[nodiscard]] constexpr qua<T> qlook_at_lh(const vec<T, 3>& dir, const vec<T, 3>& up) {
        return qrotate(look_at_lh(dir, up));
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qlook_at_rh(const vec<T, 3>& dir, const vec<T, 3>& up) {
        return qrotate(look_at_rh(dir, up));
    }
}
