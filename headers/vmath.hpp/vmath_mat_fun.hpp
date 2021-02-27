/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_mat.hpp"

#include "vmath_vec.hpp"
#include "vmath_vec_fun.hpp"

namespace vmath_hpp::detail::impl
{
    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f,
        const mat<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return mat{ f(a[Is])... };
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f,
        const mat<A, Size>& a,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return mat{ f(a[Is], b[Is])... };
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join_impl(
        F&& f,
        A init,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return ((init = f(std::move(init), b[Is])), ...);
    }

    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join_impl(
        F&& f,
        const mat<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return (... && f(a[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join_impl(
        F&& f,
        const mat<A, Size>& a,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... && f(a[Is], b[Is]));
    }

    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join_impl(
        F&& f,
        const mat<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return (... || f(a[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join_impl(
        F&& f,
        const mat<A, Size>& a,
        const mat<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... || f(a[Is], b[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_plus_join_impl(
        F&& f,
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

    namespace impl
    {
        template < typename T >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        mat<T, 2> transpose_2x2_impl(
            T a, T c,
            T b, T d)
        {
            return {
                a, b,
                c, d};
        }

        template < typename T >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        mat<T, 3> transpose_3x3_impl(
            T a, T d, T g,
            T b, T e, T h,
            T c, T f, T i)
        {
            return {
                a, b, c,
                d, e, f,
                g, h, i};
        }

        template < typename T >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        mat<T, 4> transpose_4x4_impl(
            T a, T e, T i, T m,
            T b, T f, T j, T n,
            T c, T g, T k, T o,
            T d, T h, T l, T p)
        {
            return {
                a, b, c, d,
                e, f, g, h,
                i, j, k, l,
                m, n, o, p};
        }
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> transpose(const mat<T, 2>& m) {
        return impl::transpose_2x2_impl(
            m[0][0], m[0][1],
            m[1][0], m[1][1]);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> transpose(const mat<T, 3>& m) {
        return impl::transpose_3x3_impl(
            m[0][0], m[0][1], m[0][2],
            m[1][0], m[1][1], m[1][2],
            m[2][0], m[2][1], m[2][2]);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> transpose(const mat<T, 4>& m) {
        return impl::transpose_4x4_impl(
            m[0][0], m[0][1], m[0][2], m[0][3],
            m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3],
            m[3][0], m[3][1], m[3][2], m[3][3]);
    }

    //
    // adjugate
    //

    namespace impl
    {
        template < typename T >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        mat<T, 2> adjugate_2x2_impl(
            T a, T b,
            T c, T d)
        {
            return {
                +d, -b,
                -c, +a};
        }

        template < typename T >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        mat<T, 3> adjugate_3x3_impl(
            T a, T b, T c,
            T d, T e, T f,
            T g, T h, T i)
        {
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
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        mat<T, 4> adjugate_4x4_impl(
            T a, T b, T c, T d,
            T e, T f, T g, T h,
            T i, T j, T k, T l,
            T m, T n, T o, T p)
        {
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
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> adjugate(const mat<T, 2>& m) {
        return impl::adjugate_2x2_impl(
            m[0][0], m[0][1],
            m[1][0], m[1][1]);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> adjugate(const mat<T, 3>& m) {
        return impl::adjugate_3x3_impl(
            m[0][0], m[0][1], m[0][2],
            m[1][0], m[1][1], m[1][2],
            m[2][0], m[2][1], m[2][2]);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> adjugate(const mat<T, 4>& m) {
        return impl::adjugate_4x4_impl(
            m[0][0], m[0][1], m[0][2], m[0][3],
            m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3],
            m[3][0], m[3][1], m[3][2], m[3][3]);
    }

    //
    // determinant
    //

    namespace impl
    {
        template < typename T >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        T determinant_2x2_impl(
            T a, T b,
            T c, T d)
        {
            return a * d - b * c;
        }

        template < typename T >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        T determinant_3x3_impl(
            T a, T b, T c,
            T d, T e, T f,
            T g, T h, T i)
        {
            return
                + a * (e * i - f * h)
                - b * (d * i - f * g)
                + c * (d * h - e * g);
        }

        template < typename T >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        T determinant_4x4_impl(
            T a, T b, T c, T d,
            T e, T f, T g, T h,
            T i, T j, T k, T l,
            T m, T n, T o, T p)
        {
            return
                + a * (f * (k * p - l * o) - (j * (g * p - h * o)) + (n * (g * l - h * k)))
                - b * (e * (k * p - l * o) - (i * (g * p - h * o)) + (m * (g * l - h * k)))
                + c * (e * (j * p - l * n) - (i * (f * p - h * n)) + (m * (f * l - h * j)))
                - d * (e * (j * o - k * n) - (i * (f * o - g * n)) + (m * (f * k - g * j)));
        }
    }

    template < typename T >
    [[nodiscard]] constexpr T determinant(const mat<T, 2>& m) {
        return impl::determinant_2x2_impl(
            m[0][0], m[0][1],
            m[1][0], m[1][1]);
    }

    template < typename T >
    [[nodiscard]] constexpr T determinant(const mat<T, 3>& m) {
        return impl::determinant_3x3_impl(
            m[0][0], m[0][1], m[0][2],
            m[1][0], m[1][1], m[1][2],
            m[2][0], m[2][1], m[2][2]);
    }

    template < typename T >
    [[nodiscard]] constexpr T determinant(const mat<T, 4>& m) {
        return impl::determinant_4x4_impl(
            m[0][0], m[0][1], m[0][2], m[0][3],
            m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3],
            m[3][0], m[3][1], m[3][2], m[3][3]);
    }

    //
    // inverse
    //

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> inverse(const mat<T, Size>& m) {
        return adjugate(m) * rcp(determinant(m));
    }
}
