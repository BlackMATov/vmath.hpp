/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

namespace vmath_hpp::detail
{
    template < typename T, std::size_t Size >
    class vec_base;

    template < typename T >
    class vec_base<T, 2> {
    public:
        T x{}, y{};
    public:
        constexpr vec_base() = default;

        constexpr explicit vec_base(T v)
        : x{v}, y{v} {}

        constexpr vec_base(T x, T y)
        : x{x}, y{y} {}

        constexpr explicit vec_base(const vec_base<T, 3>& xy)
        : x{xy[0]}, y{xy[1]} {}

        constexpr explicit vec_base(const vec_base<T, 4>& xy)
        : x{xy[0]}, y{xy[1]} {}

        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            }
        }

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            }
        }
    };

    template < typename T >
    class vec_base<T, 3> {
    public:
        T x{}, y{}, z{};
    public:
        constexpr vec_base() = default;

        constexpr explicit vec_base(T v)
        : x{v}, y{v}, z{v} {}

        constexpr vec_base(T x, T y, T z)
        : x{x}, y{y}, z{z} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z)
        : x{xy[0]}, y{xy[1]}, z{z} {}

        constexpr vec_base(T x, const vec_base<T, 2>& yz)
        : x{x}, y{yz[0]}, z{yz[1]} {}

        constexpr explicit vec_base(const vec_base<T, 4>& xyz)
        : x{xyz[0]}, y{xyz[1]}, z{xyz[2]} {}

        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
        }

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
        }
    };

    template < typename T >
    class vec_base<T, 4> {
    public:
        T x{}, y{}, z{}, w{};
    public:
        constexpr vec_base() = default;

        constexpr explicit vec_base(T v)
        : x{v}, y{v}, z{v}, w{v} {}

        constexpr vec_base(T x, T y, T z, T w)
        : x{x}, y{y}, z{z}, w{w} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z, T w)
        : x{xy[0]}, y{xy[1]}, z{z}, w{w} {}

        constexpr vec_base(T x, const vec_base<T, 2>& yz, T w)
        : x{x}, y{yz[0]}, z{yz[1]}, w{w} {}

        constexpr vec_base(T x, T y, const vec_base<T, 2>& zw)
        : x{x}, y{y}, z{zw[0]}, w{zw[1]} {}

        constexpr vec_base(const vec_base<T, 2>& xy, const vec_base<T, 2>& zw)
        : x{xy[0]}, y{xy[1]}, z{zw[0]}, w{zw[1]} {}

        constexpr vec_base(const vec_base<T, 3>& xyz, T w)
        : x{xyz[0]}, y{xyz[1]}, z{xyz[2]}, w{w} {}

        constexpr vec_base(T x, const vec_base<T, 3>& yzw)
        : x{x}, y{yzw[0]}, z{yzw[1]}, w{yzw[2]} {}

        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }
    };
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class vec final : public detail::vec_base<T, Size> {
    public:
        using self_type = vec;
        using base_type = detail::vec_base<T, Size>;
    public:
        using component_type = T;

        using pointer = component_type*;
        using const_pointer = const component_type*;

        using reference = component_type&;
        using const_reference = const component_type&;

        static constexpr std::size_t size = Size;
    public:
        using base_type::vec_base;
        using base_type::operator[];

        constexpr vec() = default;
        constexpr vec(const vec&) = default;
        constexpr vec& operator=(const vec&) = default;

        void swap(vec& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < Size; ++i ) {
                using std::swap;
                swap((*this)[i], other[i]);
            }
        }

        [[nodiscard]] constexpr reference at(std::size_t index) {
            if ( index >= Size ) {
                throw std::out_of_range("vec::at");
            }
            return (*this)[index];
        }

        [[nodiscard]] constexpr const_reference at(std::size_t index) const {
            if ( index >= Size ) {
                throw std::out_of_range("vec::at");
            }
            return (*this)[index];
        }
    };
}

namespace vmath_hpp
{
    // vec2

    template < typename T >
    vec(T, T) -> vec<T, 2>;

    // vec3

    template < typename T >
    vec(T, T, T) -> vec<T, 3>;

    template < typename T >
    vec(const vec<T, 2>&, T) -> vec<T, 3>;

    template < typename T >
    vec(T, const vec<T, 2>&) -> vec<T, 3>;

    // vec4

    template < typename T >
    vec(T, T, T, T) -> vec<T, 4>;

    template < typename T >
    vec(const vec<T, 2>&, T, T) -> vec<T, 4>;

    template < typename T >
    vec(T, const vec<T, 2>&, T) -> vec<T, 4>;

    template < typename T >
    vec(T, T, const vec<T, 2>&) -> vec<T, 4>;

    template < typename T >
    vec(const vec<T, 2>&, const vec<T, 2>&) -> vec<T, 4>;

    template < typename T >
    vec(const vec<T, 3>&, T) -> vec<T, 4>;

    template < typename T >
    vec(T, const vec<T, 3>&) -> vec<T, 4>;

    // swap

    template < typename T, std::size_t Size >
    void swap(vec<T, Size>& l, vec<T, Size>& r) noexcept(noexcept(l.swap(r))) {
        l.swap(r);
    }
}
