/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath.hpp>

#include <cfloat>

namespace vmath_tests
{
    using namespace vmath_hpp;

    template < typename T >
    struct uapprox_epsilon;

    template <>
    struct uapprox_epsilon<int> {
        static constexpr int value = 0;
    };

    template <>
    struct uapprox_epsilon<float> {
        static constexpr float value = FLT_EPSILON * 100;
    };

    template <>
    struct uapprox_epsilon<double> {
        static constexpr float value = DBL_EPSILON * 100;
    };

    template < typename T >
    inline constexpr T uapprox_epsilon_v = uapprox_epsilon<T>::value;

    //
    //
    //

    template < typename T >
    struct uapprox {
        T value;
        explicit constexpr uapprox(T v) : value(v) {}
    };

    template < typename T >
    struct uapprox2 {
        vec<T, 2> value;
        constexpr explicit uapprox2(T v) : value(v) {}
        constexpr explicit uapprox2(T x, T y) : value(x, y) {}
        constexpr explicit uapprox2(const vec<T, 2>& v) : value(v) {}
    };

    template < typename T >
    struct uapprox3 {
        vec<T, 3> value;
        constexpr explicit uapprox3(T v) : value(v) {}
        constexpr explicit uapprox3(T x, T y, T z) : value(x, y, z) {}
        constexpr explicit uapprox3(const vec<T, 3>& v) : value(v) {}
    };

    template < typename T >
    struct uapprox4 {
        vec<T, 4> value;
        constexpr explicit uapprox4(T v) : value(v) {}
        constexpr explicit uapprox4(T x, T y, T z, T w) : value(x, y, z, w) {}
        constexpr explicit uapprox4(const vec<T, 4>& v) : value(v) {}
    };

    //
    //
    //

    template < typename T >
    constexpr bool operator==(const T& l, const uapprox<T>& r) {
        return approx(l, r.value, uapprox_epsilon_v<T>);
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 2>& l, const uapprox2<T>& r) {
        return all(approx(l, r.value, uapprox_epsilon_v<T>));
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 3>& l, const uapprox3<T>& r) {
        return all(approx(l, r.value, uapprox_epsilon_v<T>));
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 4>& l, const uapprox4<T>& r) {
        return all(approx(l, r.value, uapprox_epsilon_v<T>));
    }
}
