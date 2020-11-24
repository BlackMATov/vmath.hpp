/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_mat.hpp"

namespace vmath_hpp::detail
{
    namespace impl
    {
        template < typename A, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto map_impl(F&& f, const mat<A, Size>& a, std::index_sequence<Is...>)
            -> mat<typename std::invoke_result_t<F, vec<A, Size>>::value_type, Size>
        {
            return { f(a[Is])... };
        }

        template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto zip_impl(F&& f, const mat<A, Size>& a, const mat<B, Size>& b, std::index_sequence<Is...>)
            -> mat<typename std::invoke_result_t<F, vec<A, Size>, vec<B, Size>>::value_type, Size>
        {
            return { f(a[Is], b[Is])... };
        }

        template < typename A, typename B, typename C, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto zip_impl(F&& f, const mat<A, Size>& a, const mat<B, Size>& b, const mat<C, Size>& c, std::index_sequence<Is...>)
            -> mat<typename std::invoke_result_t<F, vec<A, Size>, vec<B, Size>, vec<C, Size>>::value_type, Size>
        {
            return { f(a[Is], b[Is], c[Is])... };
        }

        template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto fold_impl(F&& f, A init, const mat<B, Size>& b, std::index_sequence<Is...>)
            -> A
        {
            return ((init = f(std::move(init), b[Is])), ...);
        }

        template < typename A, typename B, typename C, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto fold_impl(F&& f, A init, const mat<B, Size>& b, const mat<C, Size>& c, std::index_sequence<Is...>)
            -> A
        {
            return ((init = f(std::move(init), b[Is], c[Is])), ...);
        }
    }

    template < typename A, std::size_t Size, typename F >
    constexpr auto map(F&& f, const mat<A, Size>& a) {
        return impl::map_impl(std::forward<F>(f), a, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    constexpr auto zip(F&& f, const mat<A, Size>& a, const mat<B, Size>& b) {
        return impl::zip_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, typename C, std::size_t Size, typename F >
    constexpr auto zip(F&& f, const mat<A, Size>& a, const mat<B, Size>& b, const mat<C, Size>& c) {
        return impl::zip_impl(std::forward<F>(f), a, b, c, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    constexpr auto fold(F&& f, A init, const mat<B, Size>& b) {
        return impl::fold_impl(std::forward<F>(f), std::move(init), b, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, typename C, std::size_t Size, typename F >
    constexpr auto fold(F&& f, A init, const mat<B, Size>& b, const mat<C, Size>& c) {
        return impl::fold_impl(std::forward<F>(f), std::move(init), b, c, std::make_index_sequence<Size>{});
    }
}

//
// Operators
//

namespace vmath_hpp
{
    // -operator

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator-(const mat<T, Size>& xs) {
        return map(std::negate<>(), xs);
    }

    // operator+

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator+(const mat<T, Size>& xs, T y) {
        return map([y](const vec<T, Size>& x){ return x + y; }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator+(T x, const mat<T, Size>& ys) {
        return map([x](const vec<T, Size>& y){ return x + y; }, ys);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator+(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return zip(std::plus<>(), xs, ys);
    }

    // operator+=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator+=(mat<T, Size>& xs, T y) {
        return (xs = xs + y);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator+=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = xs + ys);
    }

    // operator-

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator-(const mat<T, Size>& xs, T y) {
        return map([y](const vec<T, Size>& x){ return x - y; }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator-(T x, const mat<T, Size>& ys) {
        return map([x](const vec<T, Size>& y){ return x - y; }, ys);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator-(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return zip(std::minus<>(), xs, ys);
    }

    // operator-=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator-=(mat<T, Size>& xs, T y) {
        return (xs = xs - y);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator-=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = xs - ys);
    }

    // operator*

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator*(const mat<T, Size>& xs, T y) {
        return map([y](const vec<T, Size>& x){ return x * y; }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator*(T x, const mat<T, Size>& ys) {
        return map([x](const vec<T, Size>& y){ return x * y; }, ys);
    }

    template < typename T >
    constexpr vec<T, 2> operator*(const vec<T, 2>& xs, const mat<T, 2>& ys) {
        return {
            xs.x * ys[0][0] + xs.y * ys[1][0],
            xs.x * ys[0][1] + xs.y * ys[1][1]};
    }

    template < typename T >
    constexpr mat<T, 2> operator*(const mat<T, 2>& xs, const mat<T, 2>& ys) {
        return {
            xs[0][0] * ys[0][0] + xs[0][1] * ys[1][0],
            xs[0][0] * ys[0][1] + xs[0][1] * ys[1][1],

            xs[1][0] * ys[0][0] + xs[1][1] * ys[1][0],
            xs[1][0] * ys[0][1] + xs[1][1] * ys[1][1]};
    }

    template < typename T >
    constexpr vec<T, 3> operator*(const vec<T, 3>& xs, const mat<T, 3>& ys) {
        return {
            xs.x * ys[0][0] + xs.y * ys[1][0] + xs.z * ys[2][0],
            xs.x * ys[0][1] + xs.y * ys[1][1] + xs.z * ys[2][1],
            xs.x * ys[0][2] + xs.y * ys[1][2] + xs.z * ys[2][2]};
    }

    template < typename T >
    constexpr mat<T, 3> operator*(const mat<T, 3>& xs, const mat<T, 3>& ys) {
        return {
            xs[0][0] * ys[0][0] + xs[0][1] * ys[1][0] + xs[0][2] * ys[2][0],
            xs[0][0] * ys[0][1] + xs[0][1] * ys[1][1] + xs[0][2] * ys[2][1],
            xs[0][0] * ys[0][2] + xs[0][1] * ys[1][2] + xs[0][2] * ys[2][2],

            xs[1][0] * ys[0][0] + xs[1][1] * ys[1][0] + xs[1][2] * ys[2][0],
            xs[1][0] * ys[0][1] + xs[1][1] * ys[1][1] + xs[1][2] * ys[2][1],
            xs[1][0] * ys[0][2] + xs[1][1] * ys[1][2] + xs[1][2] * ys[2][2],

            xs[2][0] * ys[0][0] + xs[2][1] * ys[1][0] + xs[2][2] * ys[2][0],
            xs[2][0] * ys[0][1] + xs[2][1] * ys[1][1] + xs[2][2] * ys[2][1],
            xs[2][0] * ys[0][2] + xs[2][1] * ys[1][2] + xs[2][2] * ys[2][2]};
    }

    template < typename T >
    constexpr vec<T, 4> operator*(const vec<T, 4>& xs, const mat<T, 4>& ys) {
        return {
            xs.x * ys[0][0] + xs.y * ys[1][0] + xs.z * ys[2][0] + xs.w * ys[3][0],
            xs.x * ys[0][1] + xs.y * ys[1][1] + xs.z * ys[2][1] + xs.w * ys[3][1],
            xs.x * ys[0][2] + xs.y * ys[1][2] + xs.z * ys[2][2] + xs.w * ys[3][2],
            xs.x * ys[0][3] + xs.y * ys[1][3] + xs.z * ys[2][3] + xs.w * ys[3][3]};
    }

    template < typename T >
    constexpr mat<T, 4> operator*(const mat<T, 4>& xs, const mat<T, 4>& ys) {
        return {
            xs[0][0] * ys[0][0] + xs[0][1] * ys[1][0] + xs[0][2] * ys[2][0] + xs[0][3] * ys[3][0],
            xs[0][0] * ys[0][1] + xs[0][1] * ys[1][1] + xs[0][2] * ys[2][1] + xs[0][3] * ys[3][1],
            xs[0][0] * ys[0][2] + xs[0][1] * ys[1][2] + xs[0][2] * ys[2][2] + xs[0][3] * ys[3][2],
            xs[0][0] * ys[0][3] + xs[0][1] * ys[1][3] + xs[0][2] * ys[2][3] + xs[0][3] * ys[3][3],

            xs[1][0] * ys[0][0] + xs[1][1] * ys[1][0] + xs[1][2] * ys[2][0] + xs[1][3] * ys[3][0],
            xs[1][0] * ys[0][1] + xs[1][1] * ys[1][1] + xs[1][2] * ys[2][1] + xs[1][3] * ys[3][1],
            xs[1][0] * ys[0][2] + xs[1][1] * ys[1][2] + xs[1][2] * ys[2][2] + xs[1][3] * ys[3][2],
            xs[1][0] * ys[0][3] + xs[1][1] * ys[1][3] + xs[1][2] * ys[2][3] + xs[1][3] * ys[3][3],

            xs[2][0] * ys[0][0] + xs[2][1] * ys[1][0] + xs[2][2] * ys[2][0] + xs[2][3] * ys[3][0],
            xs[2][0] * ys[0][1] + xs[2][1] * ys[1][1] + xs[2][2] * ys[2][1] + xs[2][3] * ys[3][1],
            xs[2][0] * ys[0][2] + xs[2][1] * ys[1][2] + xs[2][2] * ys[2][2] + xs[2][3] * ys[3][2],
            xs[2][0] * ys[0][3] + xs[2][1] * ys[1][3] + xs[2][2] * ys[2][3] + xs[2][3] * ys[3][3],

            xs[3][0] * ys[0][0] + xs[3][1] * ys[1][0] + xs[3][2] * ys[2][0] + xs[3][3] * ys[3][0],
            xs[3][0] * ys[0][1] + xs[3][1] * ys[1][1] + xs[3][2] * ys[2][1] + xs[3][3] * ys[3][1],
            xs[3][0] * ys[0][2] + xs[3][1] * ys[1][2] + xs[3][2] * ys[2][2] + xs[3][3] * ys[3][2],
            xs[3][0] * ys[0][3] + xs[3][1] * ys[1][3] + xs[3][2] * ys[2][3] + xs[3][3] * ys[3][3]};
    }

    // operator*=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator*=(mat<T, Size>& xs, T y) {
        return (xs = xs * y);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size>& operator*=(vec<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = xs * ys);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator*=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = xs * ys);
    }

    // operator/

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator/(const mat<T, Size>& xs, T y) {
        return map([y](const vec<T, Size>& x){ return x / y; }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator/(T x, const mat<T, Size>& ys) {
        return map([x](const vec<T, Size>& y){ return x / y; }, ys);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size> operator/(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return zip(std::divides<>(), xs, ys);
    }

    // operator/=

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator/=(mat<T, Size>& xs, T y) {
        return (xs = xs / y);
    }

    template < typename T, std::size_t Size >
    constexpr mat<T, Size>& operator/=(mat<T, Size>& xs, const mat<T, Size>& ys) {
        return (xs = xs / ys);
    }

    // operator==

    template < typename T, std::size_t Size >
    constexpr bool operator==(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return fold([](bool acc, const vec<T, Size>& x, const vec<T, Size>& y){
            return acc && (x == y);
        }, true, xs, ys);
    }

    template < typename T, std::size_t Size >
    constexpr bool operator!=(const mat<T, Size>& xs, const mat<T, Size>& ys) {
        return fold([](bool acc, const vec<T, Size>& x, const vec<T, Size>& y){
            return acc || (x != y);
        }, false, xs, ys);
    }

    // operator<

    template < typename T, std::size_t Size >
    constexpr bool operator<(const mat<T, Size>& xs, const mat<T, Size>& ys) {
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
// Matrix Functions
//

namespace vmath_hpp
{
    namespace impl
    {
        template < typename T >
        constexpr mat<T, 2> transpose_2x2_impl(
            T a, T c,
            T b, T d)
        {
            return {
                a, b,
                c, d};
        }

        template < typename T >
        constexpr mat<T, 3> transpose_3x3_impl(
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
        constexpr mat<T, 4> transpose_4x4_impl(
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
    constexpr mat<T, 2> transpose(const mat<T, 2>& m) {
        return impl::transpose_2x2_impl(
            m[0][0], m[0][1],
            m[1][0], m[1][1]);
    }

    template < typename T >
    constexpr mat<T, 3> transpose(const mat<T, 3>& m) {
        return impl::transpose_3x3_impl(
            m[0][0], m[0][1], m[0][2],
            m[1][0], m[1][1], m[1][2],
            m[2][0], m[2][1], m[2][2]);
    }

    template < typename T >
    constexpr mat<T, 4> transpose(const mat<T, 4>& m) {
        return impl::transpose_4x4_impl(
            m[0][0], m[0][1], m[0][2], m[0][3],
            m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3],
            m[3][0], m[3][1], m[3][2], m[3][3]);
    }

    namespace impl
    {
        template < typename T >
        constexpr T determinant_2x2_impl(
            T a, T b,
            T c, T d)
        {
            return
                + a * d
                - b * c;
        }

        template < typename T >
        constexpr T determinant_3x3_impl(
            T a, T b, T c,
            T d, T e, T f,
            T g, T h, T i)
        {
            return
                + a * determinant_2x2_impl(e, f, h, i)
                - b * determinant_2x2_impl(d, f, g, i)
                + c * determinant_2x2_impl(d, e, g, h);

        }

        template < typename T >
        constexpr T determinant_4x4_impl(
            T a, T b, T c, T d,
            T e, T f, T g, T h,
            T i, T j, T k, T l,
            T m, T n, T o, T p)
        {
            return
                + a * determinant_3x3_impl(f, g, h, j, k, l, n, o, p)
                - b * determinant_3x3_impl(e, g, h, i, k, l, m, o, p)
                + c * determinant_3x3_impl(e, f, h, i, j, l, m, n, p)
                - d * determinant_3x3_impl(e, f, g, i, j, k, m, n, o);
        }
    }

    template < typename T >
    constexpr T determinant(const mat<T, 2>& m) {
        return impl::determinant_2x2_impl(
            m[0][0], m[0][1],
            m[1][0], m[1][1]);
    }

    template < typename T >
    constexpr T determinant(const mat<T, 3>& m) {
        return impl::determinant_3x3_impl(
            m[0][0], m[0][1], m[0][2],
            m[1][0], m[1][1], m[1][2],
            m[2][0], m[2][1], m[2][2]);
    }

    template < typename T >
    constexpr T determinant(const mat<T, 4>& m) {
        return impl::determinant_4x4_impl(
            m[0][0], m[0][1], m[0][2], m[0][3],
            m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3],
            m[3][0], m[3][1], m[3][2], m[3][3]);
    }

    namespace impl
    {
        template < typename T >
        constexpr mat<T, 2> inverse_2x2_impl(
            T a, T b,
            T c, T d)
        {
            const T inv_det = T(1) / determinant_2x2_impl(
                a, b,
                c, d);

            const mat<T, 2> inv_m(
                d, -b,
                -c, a);

            return inv_m * inv_det;
        }

        template < typename T >
        constexpr mat<T, 3> inverse_3x3_impl(
            T a, T b, T c,
            T d, T e, T f,
            T g, T h, T i)
        {
            const T inv_det = T(1) / determinant_3x3_impl(
                a, b, c,
                d, e, f,
                g, h, i);

            const mat<T, 3> inv_m(
                e * i - f * h,
                c * h - b * i,
                b * f - c * e,
                f * g - d * i,
                a * i - c * g,
                c * d - a * f,
                d * h - e * g,
                b * g - a * h,
                a * e - b * d);

            return inv_m * inv_det;
        }

        template < typename T >
        constexpr mat<T, 4> inverse_4x4_impl(
            T a, T b, T c, T d,
            T e, T f, T g, T h,
            T i, T j, T k, T l,
            T m, T n, T o, T p)
        {
            const T inv_det = T(1) / determinant_4x4_impl(
                a, b, c, d,
                e, f, g, h,
                i, j, k, l,
                m, n, o, p);

            const mat<T, 4> inv_m(
                (f * (k * p - l * o) + g * (l * n - j * p) + h * (j * o - k * n)),
                (j * (c * p - d * o) + k * (d * n - b * p) + l * (b * o - c * n)),
                (n * (c * h - d * g) + o * (d * f - b * h) + p * (b * g - c * f)),
                (b * (h * k - g * l) + c * (f * l - h * j) + d * (g * j - f * k)),
                (g * (i * p - l * m) + h * (k * m - i * o) + e * (l * o - k * p)),
                (k * (a * p - d * m) + l * (c * m - a * o) + i * (d * o - c * p)),
                (o * (a * h - d * e) + p * (c * e - a * g) + m * (d * g - c * h)),
                (c * (h * i - e * l) + d * (e * k - g * i) + a * (g * l - h * k)),
                (h * (i * n - j * m) + e * (j * p - l * n) + f * (l * m - i * p)),
                (l * (a * n - b * m) + i * (b * p - d * n) + j * (d * m - a * p)),
                (p * (a * f - b * e) + m * (b * h - d * f) + n * (d * e - a * h)),
                (d * (f * i - e * j) + a * (h * j - f * l) + b * (e * l - h * i)),
                (e * (k * n - j * o) + f * (i * o - k * m) + g * (j * m - i * n)),
                (i * (c * n - b * o) + j * (a * o - c * m) + k * (b * m - a * n)),
                (m * (c * f - b * g) + n * (a * g - c * e) + o * (b * e - a * f)),
                (a * (f * k - g * j) + b * (g * i - e * k) + c * (e * j - f * i)));

            return inv_m * inv_det;
        }
    }

    template < typename T >
    constexpr mat<T, 2> inverse(const mat<T, 2>& m) {
        return impl::inverse_2x2_impl(
            m[0][0], m[0][1],
            m[1][0], m[1][1]);
    }

    template < typename T >
    constexpr mat<T, 3>inverse(const mat<T, 3>& m) {
        return impl::inverse_3x3_impl(
            m[0][0], m[0][1], m[0][2],
            m[1][0], m[1][1], m[1][2],
            m[2][0], m[2][1], m[2][2]);
    }

    template < typename T >
    constexpr mat<T, 4>inverse(const mat<T, 4>& m) {
        return impl::inverse_4x4_impl(
            m[0][0], m[0][1], m[0][2], m[0][3],
            m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3],
            m[3][0], m[3][1], m[3][2], m[3][3]);
    }
}