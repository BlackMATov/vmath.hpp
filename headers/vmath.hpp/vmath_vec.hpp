/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2023, by Matvey Cherevko (blackmatov@gmail.com)
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
        T x, y;
    public:
        constexpr vec_base()
        : vec_base{zero_init} {}

        constexpr vec_base(no_init_t) {}
        constexpr vec_base(zero_init_t): vec_base{T{0}} {}
        constexpr vec_base(unit_init_t): vec_base{T{1}} {}

        constexpr explicit vec_base(T v): x{v}, y{v} {}
        constexpr vec_base(T x, T y): x{x}, y{y} {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr vec_base(const vec_base<U, 2>& other): vec_base(other[0], other[1]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const vec_base<U, 3>& other): vec_base(other[0], other[1]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const vec_base<U, 4>& other): vec_base(other[0], other[1]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const U* p): vec_base(p[0], p[1]) {}

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
        T x, y, z;
    public:
        constexpr vec_base()
        : vec_base{zero_init} {}

        constexpr vec_base(no_init_t) {}
        constexpr vec_base(zero_init_t): vec_base{T{0}} {}
        constexpr vec_base(unit_init_t): vec_base{T{1}} {}

        constexpr explicit vec_base(T v): x{v}, y{v}, z{v} {}
        constexpr vec_base(T x, T y, T z): x{x}, y{y}, z{z} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z): vec_base(xy[0], xy[1], z) {}
        constexpr vec_base(T x, const vec_base<T, 2>& yz): vec_base(x, yz[0], yz[1]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr vec_base(const vec_base<U, 3>& other): vec_base(other[0], other[1], other[2]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const vec_base<U, 4>& other): vec_base(other[0], other[1], other[2]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const U* p): vec_base(p[0], p[1], p[2]) {}

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
        T x, y, z, w;
    public:
        constexpr vec_base()
        : vec_base{zero_init} {}

        constexpr vec_base(no_init_t) {}
        constexpr vec_base(zero_init_t) : vec_base{T{0}} {}
        constexpr vec_base(unit_init_t) : vec_base{T{1}} {}

        constexpr explicit vec_base(T v): x{v}, y{v}, z{v}, w{v} {}
        constexpr vec_base(T x, T y, T z, T w): x{x}, y{y}, z{z}, w{w} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z, T w): vec_base(xy[0], xy[1], z, w) {}
        constexpr vec_base(T x, const vec_base<T, 2>& yz, T w): vec_base(x, yz[0], yz[1], w) {}
        constexpr vec_base(T x, T y, const vec_base<T, 2>& zw): vec_base(x, y, zw[0], zw[1]) {}
        constexpr vec_base(const vec_base<T, 2>& xy, const vec_base<T, 2>& zw): vec_base(xy[0], xy[1], zw[0], zw[1]) {}

        constexpr vec_base(const vec_base<T, 3>& xyz, T w): vec_base(xyz[0], xyz[1], xyz[2], w) {}
        constexpr vec_base(T x, const vec_base<T, 3>& yzw): vec_base(x, yzw[0], yzw[1], yzw[2]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr vec_base(const vec_base<U, 4>& other): vec_base(other[0], other[1], other[2], other[3]) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit vec_base(const U* p): vec_base(p[0], p[1], p[2], p[3]) {}

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
        using component_type = T;

        using pointer = component_type*;
        using const_pointer = const component_type*;

        using reference = component_type&;
        using const_reference = const component_type&;

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        static inline constexpr std::size_t size = Size;
    public:
        using base_type::vec_base;
        using base_type::operator[];

        void swap(vec& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < Size; ++i ) {
                using std::swap;
                swap((*this)[i], other[i]);
            }
        }

        [[nodiscard]] iterator begin() noexcept { return iterator(data()); }
        [[nodiscard]] const_iterator begin() const noexcept { return const_iterator(data()); }
        [[nodiscard]] iterator end() noexcept { return iterator(data() + Size); }
        [[nodiscard]] const_iterator end() const noexcept { return const_iterator(data() + Size); }

        [[nodiscard]] reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        [[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        [[nodiscard]] reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        [[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        [[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }
        [[nodiscard]] const_iterator cend() const noexcept { return end(); }
        [[nodiscard]] const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        [[nodiscard]] const_reverse_iterator crend() const noexcept { return rend(); }

        [[nodiscard]] pointer data() noexcept {
            return &(*this)[0];
        }

        [[nodiscard]] const_pointer data() const noexcept {
            return &(*this)[0];
        }

        [[nodiscard]] constexpr reference at(std::size_t index) {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("vec::at"));
            return (*this)[index];
        }

        [[nodiscard]] constexpr const_reference at(std::size_t index) const {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("vec::at"));
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
