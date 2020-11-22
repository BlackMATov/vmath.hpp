/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#if defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wpedantic"
#elif defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#  pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable: 4201)
#endif

namespace vmath_hpp::detail
{
    template < typename T, std::size_t Size >
    class vec_base;

    template < typename T >
    class vec_base<T, 2> {
    public:
        union {
            struct { T x, y; };
            T data[2];
        };
    public:
        constexpr vec_base()
        : x{0}, y{0} {}

        constexpr explicit vec_base(T v)
        : x{v}, y{v} {}

        constexpr vec_base(T x, T y)
        : x{x}, y{y} {}

        constexpr explicit vec_base(const vec_base<T, 3>& xy)
        : x{xy.x}, y{xy.y} {}

        constexpr explicit vec_base(const vec_base<T, 4>& xy)
        : x{xy.x}, y{xy.y} {}

        constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            }
        }

        constexpr const T& operator[](std::size_t index) const noexcept {
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
        union {
            struct { T x, y, z; };
            T data[3];
        };
    public:
        constexpr vec_base()
        : x{0}, y{0}, z{0} {}

        constexpr explicit vec_base(T v)
        : x{v}, y{v}, z{v} {}

        constexpr vec_base(T x, T y, T z)
        : x{x}, y{y}, z{z} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z)
        : x{xy.x}, y{xy.y}, z{z} {}

        constexpr vec_base(T x, const vec_base<T, 2>& yz)
        : x{x}, y{yz.x}, z{yz.y} {}

        constexpr explicit vec_base(const vec_base<T, 4>& xyz)
        : x{xyz.x}, y{xyz.y}, z{xyz.z} {}

        constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            }
        }

        constexpr const T& operator[](std::size_t index) const noexcept {
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
        union {
            struct { T x, y, z, w; };
            T data[4];
        };
    public:
        constexpr vec_base()
        : x{0}, y{0}, z{0}, w{0} {}

        constexpr explicit vec_base(T v)
        : x{v}, y{v}, z{v}, w{v} {}

        constexpr vec_base(T x, T y, T z, T w)
        : x{x}, y{y}, z{z}, w{w} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z, T w)
        : x{xy.x}, y{xy.y}, z{z}, w{w} {}

        constexpr vec_base(T x, const vec_base<T, 2>& yz, T w)
        : x{x}, y{yz.x}, z{yz.y}, w{w} {}

        constexpr vec_base(T x, T y, const vec_base<T, 2>& zw)
        : x{x}, y{y}, z{zw.x}, w{zw.y} {}

        constexpr vec_base(const vec_base<T, 2>& xy, const vec_base<T, 2>& zw)
        : x{xy.x}, y{xy.y}, z{zw.x}, w{zw.y} {}

        constexpr vec_base(const vec_base<T, 3>& xyz, T w)
        : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{w} {}

        constexpr vec_base(T x, const vec_base<T, 3>& yzw)
        : x{x}, y{yzw.x}, z{yzw.y}, w{yzw.z} {}

        constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            }
        }

        constexpr const T& operator[](std::size_t index) const noexcept {
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

#if defined(__GNUC__)
#  pragma GCC diagnostic pop
#elif defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(_MSC_VER)
#  pragma warning(pop)
#endif

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class vec final : public detail::vec_base<T, Size> {
    public:
        using self_type = vec;
        using base_type = detail::vec_base<T, Size>;
    public:
        using value_type = T;

        using pointer = value_type*;
        using const_pointer = const value_type*;

        using reference = value_type&;
        using const_reference = const value_type&;

        static constexpr std::size_t size = Size;
    public:
        using base_type::vec_base;
        using base_type::operator[];

        vec() = default;

        vec(vec&&) = default;
        vec& operator=(vec&&) = default;

        vec(const vec&) = default;
        vec& operator=(const vec&) = default;

        void swap(vec& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < Size; ++i ) {
                using std::swap;
                swap((*this)[i], other[i]);
            }
        }

        constexpr reference at(std::size_t index) {
            if ( index >= Size ) {
                throw std::out_of_range("vec::at");
            }
            return (*this)[index];
        }

        constexpr const_reference at(std::size_t index) const {
            if ( index >= Size ) {
                throw std::out_of_range("vec::at");
            }
            return (*this)[index];
        }
    };

    template < typename T, std::size_t Size >
    void swap(vec<T, Size>& l, vec<T, Size>& r) noexcept(noexcept(l.swap(r))) {
        l.swap(r);
    }
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    constexpr bool operator==(const vec<T, Size>& l, const vec<T, Size>& r) {
        for ( std::size_t i = 0; i < Size; ++i ) {
            if ( !(l[i] == r[i]) ) {
                return false;
            }
        }
        return true;
    }

    template < typename T, std::size_t Size >
    constexpr bool operator!=(const vec<T, Size>& l, const vec<T, Size>& r) {
        return !(l == r);
    }

    template < typename T, std::size_t Size >
    constexpr bool operator<(const vec<T, Size>& l, const vec<T, Size>& r) {
        for ( std::size_t i = 0; i < Size; ++i ) {
            if ( l[i] < r[i] ) {
                return true;
            }
            if ( r[i] < l[i] ) {
                return false;
            }
        }
        return false;
    }
}
