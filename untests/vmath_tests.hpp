/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2022, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_all.hpp>
#include <doctest/doctest.h>

#define STATIC_CHECK(...)\
    static_assert(__VA_ARGS__, #__VA_ARGS__);\
    CHECK(__VA_ARGS__)

#define STATIC_CHECK_FALSE(...)\
    static_assert(!(__VA_ARGS__), "!(" #__VA_ARGS__ ")");\
    CHECK(!(__VA_ARGS__))

namespace vmath_tests
{
    using namespace vmath_hpp;

    template < typename T >
    struct uapprox_base {
        T epsilon = T{10} * std::numeric_limits<T>::epsilon();
    };

    template < typename T >
    struct uapprox : uapprox_base<T> {
        T value;
        explicit constexpr uapprox(T v) : value(v) {}
    };

    template < typename T >
    struct uapprox2 : uapprox_base<T> {
        vec<T, 2> value;
        constexpr explicit uapprox2(T v) : value(v) {}
        constexpr explicit uapprox2(T x, T y) : value(x, y) {}
        constexpr explicit uapprox2(const vec<T, 2>& v) : value(v) {}
    };

    template < typename T >
    struct uapprox3 : uapprox_base<T> {
        vec<T, 3> value;
        constexpr explicit uapprox3(T v) : value(v) {}
        constexpr explicit uapprox3(T x, T y, T z) : value(x, y, z) {}
        constexpr explicit uapprox3(const vec<T, 3>& v) : value(v) {}
    };

    template < typename T >
    struct uapprox4 : uapprox_base<T> {
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
        return approx(l, r.value, r.epsilon);
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 2>& l, const uapprox2<T>& r) {
        return all(approx(l, r.value, r.epsilon));
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 3>& l, const uapprox3<T>& r) {
        return all(approx(l, r.value, r.epsilon));
    }

    template < typename T >
    constexpr bool operator==(const vec<T, 4>& l, const uapprox4<T>& r) {
        return all(approx(l, r.value, r.epsilon));
    }
}
