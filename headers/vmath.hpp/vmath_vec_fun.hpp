/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_vec.hpp"

namespace vmath_hpp::detail::impl
{
    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f,
        const vec<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return vec{ f(a[Is])... };
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f,
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return vec{ f(a[Is], b[Is])... };
    }

    template < typename A, typename B, typename C, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f,
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
        F&& f,
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
        F&& f,
        A init,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return ((init = f(std::move(init), b[Is])), ...);
    }

    template < typename A, std::size_t Size, typename F, std::size_t I, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_join_impl(
        F&& f,
        const vec<A, Size>& a,
        std::index_sequence<I, Is...>)
    {
        A init = a[I];
        return ((init = f(std::move(init), a[Is])), ...);
    }

    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join_impl(
        F&& f,
        const vec<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return (... && f(a[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_and_join_impl(
        F&& f,
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... && f(a[Is], b[Is]));
    }

    template < typename A, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join_impl(
        F&& f,
        const vec<A, Size>& a,
        std::index_sequence<Is...>)
    {
        return (... || f(a[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_or_join_impl(
        F&& f,
        const vec<A, Size>& a,
        const vec<B, Size>& b,
        std::index_sequence<Is...>)
    {
        return (... || f(a[Is], b[Is]));
    }

    template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_plus_join_impl(
        F&& f,
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
