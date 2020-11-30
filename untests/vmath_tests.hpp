/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath.hpp>

#include <cfloat>

namespace vmath_tests
{
    using namespace vmath_hpp;

    template < typename T >
    struct approx_epsilon;

    template <>
    struct approx_epsilon<int> {
        static constexpr int value = 0;
    };

    template <>
    struct approx_epsilon<float> {
        static constexpr float value = FLT_EPSILON * 100;
    };

    template <>
    struct approx_epsilon<double> {
        static constexpr float value = DBL_EPSILON * 100;
    };

    template < typename T >
    inline constexpr T approx_epsilon_v = approx_epsilon<T>::value;

    //
    //
    //

    template < typename T >
    struct approx {
        T value;
        explicit constexpr approx(T v) : value(v) {}
    };

    template < typename T >
    struct approx2 {
        vec<T, 2> value;
        constexpr explicit approx2(T v) : value(v) {}
        constexpr explicit approx2(T x, T y) : value(x, y) {}
        constexpr explicit approx2(const vec<T, 2>& v) : value(v) {}
    };

    template < typename T >
    struct approx3 {
        vec<T, 3> value;
        constexpr explicit approx3(T v) : value(v) {}
        constexpr explicit approx3(T x, T y, T z) : value(x, y, z) {}
        constexpr explicit approx3(const vec<T, 3>& v) : value(v) {}
    };

    template < typename T >
    struct approx4 {
        vec<T, 4> value;
        constexpr explicit approx4(T v) : value(v) {}
        constexpr explicit approx4(T x, T y, T z, T w) : value(x, y, z, w) {}
        constexpr explicit approx4(const vec<T, 4>& v) : value(v) {}
    };

    //
    //
    //

    template < typename T >
    constexpr bool operator==(const T& l, const approx<T>& r) {
        return equal_to(l, r.value, approx_epsilon_v<T>);
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 2>& l, const approx2<T>& r) {
        return all(equal_to(l, r.value, approx_epsilon_v<T>));
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 3>& l, const approx3<T>& r) {
        return all(equal_to(l, r.value, approx_epsilon_v<T>));
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 4>& l, const approx4<T>& r) {
        return all(equal_to(l, r.value, approx_epsilon_v<T>));
    }
}
