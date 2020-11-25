/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_ext.hpp"
#include "vmath_fun.hpp"

#include "vmath_vec.hpp"
#include "vmath_vec_fun.hpp"

namespace std
{
    template < typename T, size_t Size >
    struct hash<vmath_hpp::vec<T, Size>> {
        size_t operator()(const vmath_hpp::vec<T, Size>& v) const noexcept {
            return vmath_hpp::detail::fold(vmath_hpp::detail::hash_combiner{}, size_t{}, v);
        }
    };
}

namespace vmath_hpp
{
    // cast_to

    template < typename To, typename From, std::size_t Size >
    constexpr vec<To, Size> cast_to(const vec<From, Size>& v) {
        return detail::map([](From x){ return cast_to<To>(x); }, v);
    }

    // component

    template < typename T, std::size_t Size >
    constexpr T component(const vec<T, Size>& v, std::size_t index) {
        return v[index];
    }

    template < typename T, std::size_t Size >
    constexpr vec<T, Size> component(vec<T, Size> v, std::size_t index, T x) {
        v[index] = x;
        return v;
    }
}
