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
        T data[2];
    public:
        constexpr vec_base() : data{} {}
        constexpr explicit vec_base(uninit_t) {}

        constexpr explicit vec_base(T v)
        : data{v, v} {}

        constexpr vec_base(T x, T y)
        : data{x, y} {}

        constexpr explicit vec_base(const vec_base<T, 3>& xy)
        : data{xy.data[0], xy.data[1]} {}

        constexpr explicit vec_base(const vec_base<T, 4>& xy)
        : data{xy.data[0], xy.data[1]} {}

        constexpr T& x() noexcept { return data[0]; }
        constexpr const T& x() const noexcept { return data[0]; }

        constexpr T& y() noexcept { return data[1]; }
        constexpr const T& y() const noexcept { return data[1]; }
    };

    template < typename T >
    class vec_base<T, 3> {
    public:
        T data[3];
    public:
        constexpr vec_base() : data{} {}
        constexpr explicit vec_base(uninit_t) {}

        constexpr explicit vec_base(T v)
        : data{v, v, v} {}

        constexpr vec_base(T x, T y, T z)
        : data{x, y, z} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z)
        : data{xy.data[0], xy.data[1], z} {}

        constexpr vec_base(T x, const vec_base<T, 2>& yz)
        : data{x, yz.data[0], yz.data[1]} {}

        constexpr explicit vec_base(const vec_base<T, 4>& xyz)
        : data{xyz.data[0], xyz.data[1], xyz.data[2]} {}

        constexpr T& x() noexcept { return data[0]; }
        constexpr const T& x() const noexcept { return data[0]; }

        constexpr T& y() noexcept { return data[1]; }
        constexpr const T& y() const noexcept { return data[1]; }

        constexpr T& z() noexcept { return data[2]; }
        constexpr const T& z() const noexcept { return data[2]; }
    };

    template < typename T >
    class vec_base<T, 4> {
    public:
        T data[4];
    public:
        constexpr vec_base() : data{} {}
        constexpr explicit vec_base(uninit_t) {}

        constexpr explicit vec_base(T v)
        : data{v, v, v, v} {}

        constexpr vec_base(T x, T y, T z, T w)
        : data{x, y, z, w} {}

        constexpr vec_base(const vec_base<T, 2>& xy, T z, T w)
        : data{xy.data[0], xy.data[1], z, w} {}

        constexpr vec_base(T x, const vec_base<T, 2>& yz, T w)
        : data{x, yz.data[0], yz.data[1], w} {}

        constexpr vec_base(T x, T y, const vec_base<T, 2>& zw)
        : data{x, y, zw.data[0], zw.data[1]} {}

        constexpr vec_base(const vec_base<T, 2>& xy, const vec_base<T, 2>& zw)
        : data{xy.data[0], xy.data[1], zw.data[0], zw.data[1]} {}

        constexpr vec_base(const vec_base<T, 3>& xyz, T w)
        : data{xyz.data[0], xyz.data[1], xyz.data[2], w} {}

        constexpr vec_base(T x, const vec_base<T, 3>& yzw)
        : data{x, yzw.data[0], yzw.data[1], yzw.data[2]} {}

        constexpr T& x() noexcept { return data[0]; }
        constexpr const T& x() const noexcept { return data[0]; }

        constexpr T& y() noexcept { return data[1]; }
        constexpr const T& y() const noexcept { return data[1]; }

        constexpr T& z() noexcept { return data[2]; }
        constexpr const T& z() const noexcept { return data[2]; }

        constexpr T& w() noexcept { return data[3]; }
        constexpr const T& w() const noexcept { return data[3]; }
    };
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class vec final : public detail::vec_base<T, Size> {
    public:
        using self_type = vec;
        using base_type = detail::vec_base<T, Size>;
        using value_type = T;

        using pointer = value_type*;
        using const_pointer = const value_type*;

        using reference = value_type&;
        using const_reference = const value_type&;

        using iterator = value_type*;
        using const_iterator = const value_type*;

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
    public:
        using base_type::data;
        using base_type::vec_base;

        vec(vec&&) = default;
        vec& operator=(vec&&) = default;

        vec(const vec&) = default;
        vec& operator=(const vec&) = default;

        void swap(vec& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < Size; ++i ) {
                using std::swap;
                swap(data[i], other.data[i]);
            }
        }

        constexpr iterator begin() noexcept { return iterator(data); }
        constexpr const_iterator begin() const noexcept { return const_iterator(data); }
        constexpr const_iterator cbegin() const noexcept { return const_iterator(data); }

        constexpr iterator end() noexcept { return iterator(data + Size); }
        constexpr const_iterator end() const noexcept { return const_iterator(data + Size); }
        constexpr const_iterator cend() const noexcept { return const_iterator(data + Size); }

        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

        constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

        constexpr size_type size() const noexcept { return Size; }
        constexpr size_type max_size() const noexcept { return Size; }
        constexpr bool empty() const noexcept { return !Size; }

        constexpr reference operator[](size_type index) noexcept {
            return data[index];
        }

        constexpr const_reference operator[](size_type index) const noexcept {
            return data[index];
        }

        constexpr reference at(size_type index) {
            if ( index >= Size ) {
                throw std::out_of_range("vec::at");
            }
            return data[index];
        }

        constexpr const_reference at(size_type index) const {
            if ( index >= Size ) {
                throw std::out_of_range("vec::at");
            }
            return data[index];
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
