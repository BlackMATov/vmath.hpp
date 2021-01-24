/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_qua.hpp"

namespace vmath_hpp::detail::impl
{
    template < typename A, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f,
        const qua<A>& a,
        std::index_sequence<Is...>
    ) -> qua<decltype(f(
        std::declval<A>()))>
    {
        return { f(a[Is])... };
    }

    template < typename A, typename B, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f,
        const qua<A>& a,
        const qua<B>& b,
        std::index_sequence<Is...>
    ) -> qua<decltype(f(
        std::declval<A>(),
        std::declval<B>()))>
    {
        return { f(a[Is], b[Is])... };
    }

    template < typename A, typename B, typename C, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join_impl(
        F&& f,
        const qua<A>& a,
        const qua<B>& b,
        const qua<C>& c,
        std::index_sequence<Is...>
    ) -> qua<decltype(f(
        std::declval<A>(),
        std::declval<B>(),
        std::declval<C>()))>
    {
        return { f(a[Is], b[Is], c[Is])... };
    }

    template < typename A, typename B, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join_impl(
        F&& f,
        A init,
        const qua<B>& b,
        std::index_sequence<Is...>
    ) -> A {
        return ((init = f(std::move(init), b[Is])), ...);
    }

    template < typename A, typename B, typename C, typename F, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join_impl(
        F&& f,
        A init,
        const qua<B>& b,
        const qua<C>& c,
        std::index_sequence<Is...>
    ) -> A {
        return ((init = f(std::move(init), b[Is], c[Is])), ...);
    }

    template < typename A, typename F, std::size_t I, std::size_t... Is >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_join_impl(
        F&& f,
        const qua<A>& a,
        std::index_sequence<I, Is...>
    ) -> A {
        A init = a[I];
        return ((init = f(std::move(init), a[Is])), ...);
    }
}

namespace vmath_hpp::detail
{
    template < typename A, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(
        F&& f,
        const qua<A>& a
    ) {
        return impl::map_join_impl(
            std::forward<F>(f), a, std::make_index_sequence<4>{});
    }

    template < typename A, typename B, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(
        F&& f,
        const qua<A>& a,
        const qua<B>& b
    ) {
        return impl::map_join_impl(
            std::forward<F>(f), a, b, std::make_index_sequence<4>{});
    }

    template < typename A, typename B, typename C, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto map_join(
        F&& f,
        const qua<A>& a,
        const qua<B>& b,
        const qua<C>& c
    ) {
        return impl::map_join_impl(
            std::forward<F>(f), a, b, c, std::make_index_sequence<4>{});
    }

    template < typename A, typename B, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join(
        F&& f,
        A init,
        const qua<B>& b
    ) {
        return impl::fold_join_impl(
            std::forward<F>(f), std::move(init), b, std::make_index_sequence<4>{});
    }

    template < typename A, typename B, typename C, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold_join(
        F&& f,
        A init,
        const qua<B>& b,
        const qua<C>& c
    ) {
        return impl::fold_join_impl(
            std::forward<F>(f), std::move(init), b, c, std::make_index_sequence<4>{});
    }

    template < typename A, typename F >
    [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
    auto fold1_join(
        F&& f,
        const qua<A>& a
    ) {
        return impl::fold1_join_impl(
            std::forward<F>(f), a, std::make_index_sequence<4>{});
    }
}

//
// Operators
//

namespace vmath_hpp
{
    // operator==

    template < typename T >
    [[nodiscard]] constexpr bool operator==(const qua<T>& xs, const qua<T>& ys) {
        return fold_join([](bool acc, T x, T y){
            return acc && x == y;
        }, true, xs, ys);
    }

    // operator!=

    template < typename T >
    [[nodiscard]] constexpr bool operator!=(const qua<T>& xs, const qua<T>& ys) {
        return fold_join([](bool acc, T x, T y){
            return acc || x != y;
        }, false, xs, ys);
    }

    // operator<

    template < typename T >
    [[nodiscard]] constexpr bool operator<(const qua<T>& xs, const qua<T>& ys) {
        for ( std::size_t i = 0; i < 4; ++i ) {
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
