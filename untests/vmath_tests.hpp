/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_vec.hpp>
#include <vmath.hpp/vmath_vec_fun.hpp>

#include <limits>

namespace vmath_tests
{
    using namespace vmath_hpp;

    template < typename T >
    inline constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;

    template < typename T >
    struct approx {
        T value;
        explicit constexpr approx(T v) : value(v) {}

        friend constexpr bool operator==(const T& l, const approx& r) {
            return (r.value < l + epsilon<T>)
                && (l < r.value + epsilon<T>);
        }
    };

    template < typename T >
    struct approx2 {
        vec<T, 2> value;
        constexpr explicit approx2(T v) : value(v) {}
        constexpr explicit approx2(T x, T y) : value(x, y) {}
        constexpr explicit approx2(const vec<T, 2>& v) : value(v) {}

        friend constexpr bool operator==(const vec<T, 2>& l, const approx2& r) {
            return l[0] == approx(r.value[0])
                && l[1] == approx(r.value[1]);
        }
    };

    template < typename T >
    struct approx3 {
        vec<T, 3> value;
        constexpr explicit approx3(T v) : value(v) {}
        constexpr explicit approx3(T x, T y, T z) : value(x, y, z) {}
        constexpr explicit approx3(const vec<T, 3>& v) : value(v) {}

        friend constexpr bool operator==(const vec<T, 3>& l, const approx3& r) {
            return l[0] == approx(r.value[0])
                && l[1] == approx(r.value[1])
                && l[2] == approx(r.value[2]);
        }
    };

    template < typename T >
    struct approx4 {
        vec<T, 4> value;
        constexpr explicit approx4(T v) : value(v) {}
        constexpr explicit approx4(T x, T y, T z, T w) : value(x, y, z, w) {}
        constexpr explicit approx4(const vec<T, 4>& v) : value(v) {}

        friend constexpr bool operator==(const vec<T, 4>& l, const approx4& r) {
            return l[0] == approx(r.value[0])
                && l[1] == approx(r.value[1])
                && l[2] == approx(r.value[2])
                && l[3] == approx(r.value[3]);
        }
    };

    template < typename T >
    struct approx2x2 {
        mat<T, 2> value;
        constexpr explicit approx2x2(const mat<T, 2>& v) : value(v) {}

        friend constexpr bool operator==(const mat<T, 2>& l, const approx2x2& r) {
            return l[0] == approx2(r.value[0])
                && l[1] == approx2(r.value[1]);
        }
    };

    template < typename T >
    struct approx3x3 {
        mat<T, 3> value;
        constexpr explicit approx3x3(const mat<T, 3>& v) : value(v) {}

        friend constexpr bool operator==(const mat<T, 3>& l, const approx3x3& r) {
            return l[0] == approx3(r.value[0])
                && l[1] == approx3(r.value[1])
                && l[2] == approx3(r.value[2]);
        }
    };

    template < typename T >
    struct approx4x4 {
        mat<T, 4> value;
        constexpr explicit approx4x4(const mat<T, 4>& v) : value(v) {}

        friend constexpr bool operator==(const mat<T, 4>& l, const approx4x4& r) {
            return l[0] == approx4(r.value[0])
                && l[1] == approx4(r.value[1])
                && l[2] == approx4(r.value[2])
                && l[3] == approx4(r.value[3]);
        }
    };
}
