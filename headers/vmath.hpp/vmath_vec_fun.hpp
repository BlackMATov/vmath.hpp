/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_vec.hpp"

namespace vmath_hpp::detail
{
    namespace impl
    {
        template < typename A, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto map_impl(F&& f, const vec<A, Size>& v, std::index_sequence<Is...>)
            -> vec<std::invoke_result_t<F, A>, Size>
        {
            return { f(v[Is])... };
        }

        template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto zip_impl(F&& f, const vec<A, Size>& a, const vec<B, Size>& b, std::index_sequence<Is...>)
            -> vec<std::invoke_result_t<F, A, B>, Size>
        {
            return { f(a[Is], b[Is])... };
        }

        template < typename A, typename B, typename C, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto zip_impl(F&& f, const vec<A, Size>& a, const vec<B, Size>& b, const vec<C, Size>& c, std::index_sequence<Is...>)
            -> vec<std::invoke_result_t<F, A, B, C>, Size>
        {
            return { f(a[Is], b[Is], c[Is])... };
        }

        template < typename A, typename B, std::size_t Size, typename F, std::size_t... Is >
        constexpr auto fold_impl(F&& f, A init, const vec<B, Size>& v, std::index_sequence<Is...>)
            -> A
        {
            return ((init = f(std::move(init), v[Is])), ...);
        }
    }

    template < typename T, std::size_t Size, typename F >
    constexpr auto map(F&& f, const vec<T, Size>& v) {
        return impl::map_impl(std::forward<F>(f), v, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    constexpr auto zip(F&& f, const vec<A, Size>& a, const vec<B, Size>& b) {
        return impl::zip_impl(std::forward<F>(f), a, b, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, typename C, std::size_t Size, typename F >
    constexpr auto zip(F&& f, const vec<A, Size>& a, const vec<B, Size>& b, const vec<C, Size>& c) {
        return impl::zip_impl(std::forward<F>(f), a, b, c, std::make_index_sequence<Size>{});
    }

    template < typename A, typename B, std::size_t Size, typename F >
    constexpr auto fold(F&& f, A init, const vec<B, Size>& v) {
        return impl::fold_impl(std::forward<F>(f), std::move(init), v, std::make_index_sequence<Size>{});
    }
}

//
// Operators
//

namespace vmath_hpp
{
    // -operator

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator-(const vec<T, Size>& xs) {
        return map(std::negate<>(), xs);
    }

    // operator+

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator+(const vec<T, Size>& xs, T y) {
        return map([y](T x){ return x + y; }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator+(T x, const vec<T, Size>& ys) {
        return map([x](T y){ return x + y; }, ys);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator+(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return zip(std::plus<>(), xs, ys);
    }

    // operator-

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator-(const vec<T, Size>& xs, T y) {
        return map([y](T x){ return x - y; }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator-(T x, const vec<T, Size>& ys) {
        return map([x](T y){ return x - y; }, ys);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator-(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return zip(std::minus<>(), xs, ys);
    }

    // operator*

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator*(const vec<T, Size>& xs, T y) {
        return map([y](T x){ return x * y; }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator*(T x, const vec<T, Size>& ys) {
        return map([x](T y){ return x * y; }, ys);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator*(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return zip(std::multiplies<>(), xs, ys);
    }

    // operator/

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator/(const vec<T, Size>& xs, T y) {
        return map([y](T x){ return x / y; }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator/(T x, const vec<T, Size>& ys) {
        return map([x](T y){ return x / y; }, ys);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> operator/(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return zip(std::divides<>(), xs, ys);
    }
}

//
// Angle and Trigonometry Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    constexpr vec<T, Size> radians(const vec<T, Size>& degrees) {
        return map([](T x) { return radians(x); }, degrees);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> degrees(const vec<T, Size>& radians) {
        return map([](T x) { return degrees(x); }, radians);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> sin(const vec<T, Size>& xs) {
        return map([](T x) { return sin(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> cos(const vec<T, Size>& xs) {
        return map([](T x) { return cos(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> tan(const vec<T, Size>& xs) {
        return map([](T x) { return tan(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> asin(const vec<T, Size>& xs) {
        return map([](T x) { return asin(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> acos(const vec<T, Size>& xs) {
        return map([](T x) { return acos(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> atan(const vec<T, Size>& xs) {
        return map([](T x) { return atan(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> atan2(const vec<T, Size>& ys, const vec<T, Size>& xs) {
        return zip([](T y, T x) { return atan2(y, x); }, ys, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> sinh(const vec<T, Size>& xs) {
        return map([](T x) { return sinh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> cosh(const vec<T, Size>& xs) {
        return map([](T x) { return cosh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> tanh(const vec<T, Size>& xs) {
        return map([](T x) { return tanh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> asinh(const vec<T, Size>& xs) {
        return map([](T x) { return asinh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> acosh(const vec<T, Size>& xs) {
        return map([](T x) { return acosh(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> atanh(const vec<T, Size>& xs) {
        return map([](T x) { return atanh(x); }, xs);
    }
}

//
// Exponential Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    vec<T, Size> pow(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return zip([](T x, T y) { return pow(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> exp(const vec<T, Size>& xs) {
        return map([](T x) { return exp(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> log(const vec<T, Size>& xs) {
        return map([](T x) { return log(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> exp2(const vec<T, Size>& xs) {
        return map([](T x) { return exp2(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> log2(const vec<T, Size>& xs) {
        return map([](T x) { return log2(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> sqrt(const vec<T, Size>& xs) {
        return map([](T x) { return sqrt(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> invsqrt(const vec<T, Size>& xs) {
        return map([](T x) { return invsqrt(x); }, xs);
    }
}

//
// Common Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    vec<T, Size> abs(const vec<T, Size>& xs) {
        return map([](T x) { return abs(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> sign(const vec<T, Size>& xs) {
        return map([](T x) { return sign(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> floor(const vec<T, Size>& xs) {
        return map([](T x) { return floor(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> trunc(const vec<T, Size>& xs) {
        return map([](T x) { return trunc(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> round(const vec<T, Size>& xs) {
        return map([](T x) { return round(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> ceil(const vec<T, Size>& xs) {
        return map([](T x) { return ceil(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> fract(const vec<T, Size>& xs) {
        return map([](T x) { return fract(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> fmod(const vec<T, Size>& xs, T y) {
        return map([y](T x) { return fmod(x, y); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> fmod(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return zip([](T x, T y) { return fmod(x, y); }, xs, ys);
    }

    namespace impl
    {
        template < typename T, std::size_t Size, std::size_t... Is >
        vec<T, Size> modf_impl(const vec<T, Size>& xs, vec<T, Size>* is, std::index_sequence<Is...>) {
            return { modf(xs[Is], &(*is)[Is])... };
        }
    }

    template < typename T, std::size_t Size >
    vec<T, Size> modf(const vec<T, Size>& xs, vec<T, Size>* is) {
        return impl::modf_impl(xs, is, std::make_index_sequence<Size>{});
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> min(const vec<T, Size>& xs, T y) {
        return map([y](T x) { return min(x, y); }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> min(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return zip([](T x, T y) { return min(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> max(const vec<T, Size>& xs, T y) {
        return map([y](T x) { return max(x, y); }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> max(const vec<T, Size>& xs, const vec<T, Size>& ys) {
        return zip([](T x, T y) { return max(x, y); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> clamp(const vec<T, Size>& xs, T min_x, T max_x) {
        return map([min_x, max_x](T x) { return clamp(x, min_x, max_x); }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> clamp(const vec<T, Size>& xs, const vec<T, Size>& min_xs, const vec<T, Size>& max_xs) {
        return zip([](T x, T min_x, T max_x) { return clamp(x, min_x, max_x); }, xs, min_xs, max_xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> mix(const vec<T, Size>& xs, const vec<T, Size>& ys, T a) {
        return zip([a](T x, T y) { return mix(x, y, a); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> mix(const vec<T, Size>& xs, const vec<T, Size>& ys, bool a) {
        return zip([a](T x, T y) { return mix(x, y, a); }, xs, ys);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> mix(const vec<T, Size>& xs, const vec<T, Size>& ys, const vec<T, Size>& as) {
        return zip([](T x, T y, T a) { return mix(x, y, a); }, xs, ys, as);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> mix(const vec<T, Size>& xs, const vec<T, Size>& ys, const vec<bool, Size>& as) {
        return zip([](T x, T y, bool a) { return mix(x, y, a); }, xs, ys, as);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> step(T edge, const vec<T, Size>& xs) {
        return map([edge](T x) { return step(edge, x); }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> step(const vec<T, Size>& edges, const vec<T, Size>& xs) {
        return zip([](T edge, T x) { return step(edge, x); }, edges, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> smoothstep(T edge0, T edge1, const vec<T, Size>& xs) {
        return map([edge0, edge1](T x) { return smoothstep(edge0, edge1, x); }, xs);
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> smoothstep(const vec<T, Size>& edges0, const vec<T, Size>& edges1, const vec<T, Size>& xs) {
        return zip([](T edge0, T edge1, T x) { return smoothstep(edge0, edge1, x); }, edges0, edges1, xs);
    }

    template < typename T, std::size_t Size >
    vec<bool, Size> isnan(const vec<T, Size>& xs) {
        return map([](T x) { return isnan(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<bool, Size> isinf(const vec<T, Size>& xs) {
        return map([](T x) { return isinf(x); }, xs);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> fma(const vec<T, Size>& as, const vec<T, Size>& bs, const vec<T, Size>& cs) {
        return zip([](T a, T b, T c) { return fma(a, b, c); }, as, bs, cs);
    }

    namespace impl
    {
        template < typename T, std::size_t Size, std::size_t... Is >
        vec<T, Size> frexp_impl(const vec<T, Size>& xs, vec<int, Size>* exps, std::index_sequence<Is...>) {
            return { frexp(xs.data[Is], &exps->data[Is])... };
        }
    }

    template < typename T, std::size_t Size >
    vec<T, Size> frexp(const vec<T, Size>& xs, vec<int, Size>* exps) {
        return impl::frexp_impl(xs, exps, std::make_index_sequence<Size>{});
    }

    template < typename T, std::size_t Size >
    vec<T, Size> ldexp(const vec<T, Size>& xs, const vec<int, Size>& exps) {
        return zip([](T x, int exp) { return ldexp(x, exp); }, xs, exps);
    }
}

//
// Geometric Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    T length(const vec<T, Size>& x) noexcept {
        return sqrt(dot(x, x));
    }

    template < typename T, std::size_t Size >
    T distance(const vec<T, Size>& p0, const vec<T, Size>& p1) noexcept {
        return length(p0 - p1);
    }

    template < typename T, std::size_t Size >
    constexpr T dot(const vec<T, Size>& x, const vec<T, Size>& y) noexcept {
        return fold(std::plus<>(), T(0), zip(std::multiplies<>(), x, y));
    }

    template < typename T >
    constexpr vec<T, 3> cross(const vec<T, 3>& x, const vec<T, 3>& y) noexcept {
        return {
            x.y * y.z - x.z * y.y,
            x.z * y.x - x.x * y.z,
            x.x * y.y - x.y * y.x};
    }

    template < typename T, std::size_t Size >
    vec<T, Size> normalize(const vec<T, Size>& x) noexcept {
        return x * invsqrt(dot(x, x));
    }

    template < typename T, std::size_t Size >
    vec<T, Size> faceforward(const vec<T, Size>& n, const vec<T, Size>& i, const vec<T, Size>& nref) noexcept {
        return dot(nref, i) < T(0) ? n : -n;
    }

    template < typename T, std::size_t Size >
    vec<T, Size> reflect(const vec<T, Size>& i, const vec<T, Size>& n) noexcept {
        return i - n * dot(n, i) * T(2);
    }

    template < typename T, std::size_t Size >
    vec<T, Size> refract(const vec<T, Size>& i, const vec<T, Size>& n, T eta) noexcept {
        const T d = dot(n, i);
        const T k = T(1) - eta * eta * (T(1) - d * d);
        return T(k >= T(0)) * (eta * i - (eta * d + sqrt(k)) * n);
    }
}

//
// Vector Relational Functions
//

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> less(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(std::less<>(), x, y);
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> less_equal(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(std::less_equal<>(), x, y);
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> greater(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(std::greater<>(), x, y);
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> greater_equal(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(std::greater_equal<>(), x, y);
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> equal_to(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(std::equal_to<>(), x, y);
    }

    template < typename T, std::size_t Size >
    constexpr vec<bool, Size> not_equal_to(const vec<T, Size>& x, const vec<T, Size>& y) {
        return detail::zip(std::not_equal_to<>(), x, y);
    }

    template < std::size_t Size >
    constexpr bool any(const vec<bool, Size>& x) {
        return detail::fold(std::logical_or<>(), false, x);
    }

    template < std::size_t Size >
    constexpr bool all(const vec<bool, Size>& x) {
        return detail::fold(std::logical_and<>(), true, x);
    }

    template < std::size_t Size >
    constexpr vec<bool, Size> not_(const vec<bool, Size>& x) {
        return detail::map(std::logical_not<>(), x);
    }
}
