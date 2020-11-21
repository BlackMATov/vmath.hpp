/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"
#include "vmath_vec.hpp"

namespace vmath_hpp::detail
{
    template < typename T, std::size_t Size, typename F >
    constexpr auto map(const vec<T, Size>& v, F&& f) {
        vec<std::invoke_result_t<F, T>, Size> result;
        for ( std::size_t i = 0; i < Size; ++i ) {
            result[i] = f(v[i]);
        }
        return result;
    }

    template < typename T, typename U, std::size_t Size, typename F >
    constexpr auto zip(const vec<T, Size>& l, const vec<U, Size>& r, F&& f) {
        vec<std::invoke_result_t<F, T, U>, Size> result;
        for ( std::size_t i = 0; i < Size; ++i ) {
            result[i] = f(l[i], r[i]);
        }
        return result;
    }

    template < typename T, typename U, std::size_t Size, typename F >
    constexpr auto fold(const vec<T, Size>& v, U init, F&& f) {
        for ( std::size_t i = 0; i < Size; ++i ) {
            init = f(init, v[i]);
        }
        return init;
    }
}

//
// Vector Relational Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> less(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(x, y, std::less<>());
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> less_equal(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(x, y, std::less_equal<>());
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> greater(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(x, y, std::greater<>());
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> greater_equal(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(x, y, std::greater_equal<>());
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> equal(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(x, y, std::equal_to<>());
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> not_equal(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(x, y, std::not_equal_to<>());
    }

    template < std::size_t Size >
    constexpr bool any(const vec<bool, Size>& x) {
        return detail::fold(x, false, std::logical_or<>());
    }

    template < std::size_t Size >
    constexpr bool all(const vec<bool, Size>& x) {
        return detail::fold(x, true, std::logical_and<>());
    }

    template < std::size_t Size >
    constexpr vec<bool, Size> not_(const vec<bool, Size>& x) {
        return detail::map(x, std::logical_not<>());
    }
}
