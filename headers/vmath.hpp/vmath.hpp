/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include <cstddef>

#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace vmath_hpp
{
    struct uninit_t {};
    inline constexpr uninit_t uninit;
}

namespace vmath_hpp::detail
{
    template < typename T, std::size_t Size >
    class vec_base;

    template < typename T >
    class vec_base<T, 2> {
    public:
        T x, y;
    public:
        constexpr vec_base() : x{}, y{} {}
        constexpr explicit vec_base(uninit_t) {}

        constexpr explicit vec_base(const T& v)
        : x{v}, y{v} {}

        constexpr vec_base(T x, T y)
        : x{std::move(x)}, y{std::move(y)} {}

        constexpr explicit vec_base(vec_base<T, 3>&& xy)
        : x{std::move(xy.x)} , y{std::move(xy.y)} {}
        constexpr explicit vec_base(const vec_base<T, 3>& xy)
        : x{xy.x} , y{xy.y} {}

        constexpr explicit vec_base(vec_base<T, 4>&& xy)
        : x{std::move(xy.x)} , y{std::move(xy.y)} {}
        constexpr explicit vec_base(const vec_base<T, 4>& xy)
        : x{xy.x} , y{xy.y} {}

        constexpr T* data() noexcept {
            return std::addressof(x);
        }

        constexpr const T* data() const noexcept {
            return std::addressof(x);
        }
    };

    template < typename T >
    class vec_base<T, 3> {
    public:
        T x, y, z;
    public:
        constexpr vec_base() : x{}, y{}, z{} {}
        constexpr explicit vec_base(uninit_t) {}

        constexpr explicit vec_base(const T& v)
        : x{v}, y{v}, z{v} {}

        constexpr vec_base(T x, T y, T z)
        : x{std::move(x)}, y{std::move(y)}, z{std::move(z)} {}

        constexpr explicit vec_base(vec_base<T, 2>&& xy, T z)
        : x{std::move(xy.x)} , y{std::move(xy.y)} , z{std::move(z)} {}
        constexpr explicit vec_base(const vec_base<T, 2>& xy, T z)
        : x{xy.x} , y{xy.y} , z{std::move(z)} {}

        constexpr explicit vec_base(vec_base<T, 4>&& xyz)
        : x{std::move(xyz.x)} , y{std::move(xyz.y)} , z{std::move(xyz.z)} {}
        constexpr explicit vec_base(const vec_base<T, 4>& xyz)
        : x{xyz.x} , y{xyz.y} , z{xyz.z} {}

        constexpr T* data() noexcept {
            return std::addressof(x);
        }

        constexpr const T* data() const noexcept {
            return std::addressof(x);
        }
    };

    template < typename T >
    class vec_base<T, 4> {
    public:
        T x, y, z, w;
    public:
        constexpr vec_base() : x{}, y{}, z{}, w{} {}
        constexpr explicit vec_base(uninit_t) {}

        constexpr explicit vec_base(const T& v)
        : x{v}, y{v}, z{v}, w{v} {}

        constexpr vec_base(T x, T y, T z, T w)
        : x{std::move(x)}, y{std::move(y)}, z{std::move(z)}, w{std::move(w)} {}

        constexpr explicit vec_base(vec_base<T, 2>&& xy, T z, T w)
        : x{std::move(xy.x)} , y{std::move(xy.y)} , z{std::move(z)} , w{std::move(w)} {}
        constexpr explicit vec_base(const vec_base<T, 2>& xy, T z, T w)
        : x{xy.x} , y{xy.y} , z{std::move(z)} , w{std::move(w)} {}

        constexpr explicit vec_base(vec_base<T, 3>&& xyz, T w)
        : x{std::move(xyz.x)} , y{std::move(xyz.y)} , z{std::move(xyz.z)} , w{std::move(w)} {}
        constexpr explicit vec_base(const vec_base<T, 3>& xyz, T w)
        : x{xyz.x} , y{xyz.y} , z{xyz.z} , w{std::move(w)} {}

        constexpr T* data() noexcept {
            return std::addressof(x);
        }

        constexpr const T* data() const noexcept {
            return std::addressof(x);
        }
    };
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class vec final : public detail::vec_base<T, Size> {
    public:
        using self_type = vec;
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
        using detail::vec_base<T, Size>::data;
        using detail::vec_base<T, Size>::vec_base;

        vec(vec&&) = default;
        vec& operator=(vec&&) = default;

        vec(const vec&) = default;
        vec& operator=(const vec&) = default;

        void fill(const value_type& v) {
            std::fill_n(begin(), size(), v);
        }

        void swap(vec& other) noexcept(std::is_nothrow_swappable_v<T>) {
            std::swap_ranges(begin(), end(), other.begin());
        }

        constexpr iterator begin() noexcept { return iterator(data()); }
        constexpr const_iterator begin() const noexcept { return const_iterator(data()); }
        constexpr const_iterator cbegin() const noexcept { return const_iterator(data()); }

        constexpr iterator end() noexcept { return iterator(data() + size()); }
        constexpr const_iterator end() const noexcept { return const_iterator(data() + size()); }
        constexpr const_iterator cend() const noexcept { return const_iterator(data() + size()); }

        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

        constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

        constexpr size_type size() const noexcept { return Size; }
        constexpr size_type max_size() const noexcept { return Size; }
        constexpr bool empty() const noexcept { return !Size; }

        constexpr reference operator[](size_type index) noexcept { return data()[index]; }
        constexpr const_reference operator[](size_type index) const noexcept { return data()[index]; }

        constexpr reference at(size_type index) {
            if ( index >= size() ) {
                throw std::out_of_range("vec::at");
            }
            return data()[index];
        }

        constexpr const_reference at(size_type index) const {
            if ( index >= size() ) {
                throw std::out_of_range("vec::at");
            }
            return data()[index];
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
    bool operator==(const vec<T, Size>& l, const vec<T, Size>& r) {
        return std::equal(l.begin(), l.end(), r.begin());
    }

    template < typename T, std::size_t Size >
    bool operator!=(const vec<T, Size>& l, const vec<T, Size>& r) {
        return !(l == r);
    }

    template < typename T, std::size_t Size >
    bool operator<(const vec<T, Size>& l, const vec<T, Size>& r) {
        return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
    }
}

namespace vmath_hpp
{
    using vec2i = vec<int, 2>;
    using vec3i = vec<int, 3>;
    using vec4i = vec<int, 4>;

    using vec2b = vec<bool, 2>;
    using vec3b = vec<bool, 3>;
    using vec4b = vec<bool, 4>;

    using vec2f = vec<float, 2>;
    using vec3f = vec<float, 3>;
    using vec4f = vec<float, 4>;
}
