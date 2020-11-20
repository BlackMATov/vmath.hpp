/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"
#include "vmath_vec.hpp"

namespace vmath_hpp::detail
{
    template < typename T, std::size_t Size >
    class mat_base;

    template < typename T >
    class mat_base<T, 2> {
    public:
        vec<T, 2> rows[2];
    public:
        constexpr mat_base() : rows{
            {1, 0},
            {0, 1},
        } {}

        constexpr explicit mat_base(uninit_t) {}

        constexpr mat_base(
            T m11, T m12,
            T m21, T m22)
        : rows{
            {m11, m12},
            {m21, m22}} {}

        constexpr mat_base(
            const vec<T, 2>& row0,
            const vec<T, 2>& row1)
        : rows{row0, row1} {}
    };

    template < typename T >
    class mat_base<T, 3> {
    public:
        vec<T, 3> rows[3];
    public:
        constexpr mat_base() : rows{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1},
        } {}

        constexpr explicit mat_base(uninit_t) {}

        constexpr mat_base(
            T m11, T m12, T m13,
            T m21, T m22, T m23,
            T m31, T m32, T m33)
        : rows{
            {m11, m12, m13},
            {m21, m22, m23},
            {m31, m32, m33}} {}

        constexpr mat_base(
            const vec<T, 3>& row0,
            const vec<T, 3>& row1,
            const vec<T, 3>& row2)
        : rows{row0, row1, row2} {}
    };

    template < typename T >
    class mat_base<T, 4> {
    public:
        vec<T, 4> rows[4];
    public:
        constexpr mat_base() : rows{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
        } {}

        constexpr explicit mat_base(uninit_t) {}

        constexpr mat_base(
            T m11, T m12, T m13, T m14,
            T m21, T m22, T m23, T m24,
            T m31, T m32, T m33, T m34,
            T m41, T m42, T m43, T m44)
        : rows{
            {m11, m12, m13, m14},
            {m21, m22, m23, m24},
            {m31, m32, m33, m34},
            {m41, m42, m43, m44}} {}

        constexpr mat_base(
            const vec<T, 4>& row0,
            const vec<T, 4>& row1,
            const vec<T, 4>& row2,
            const vec<T, 4>& row3)
        : rows{row0, row1, row2, row3} {}
    };
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class mat final : public detail::mat_base<T, Size> {
    public:
        using self_type = mat;
        using base_type = detail::mat_base<T, Size>;
        using value_type = vec<T, Size>;

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
        using base_type::rows;
        using base_type::mat_base;

        mat(mat&&) = default;
        mat& operator=(mat&&) = default;

        mat(const mat&) = default;
        mat& operator=(const mat&) = default;

        void swap(mat& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < Size; ++i ) {
                using std::swap;
                swap(rows[i], other.rows[i]);
            }
        }

        constexpr iterator begin() noexcept { return iterator(rows); }
        constexpr const_iterator begin() const noexcept { return const_iterator(rows); }
        constexpr const_iterator cbegin() const noexcept { return const_iterator(rows); }

        constexpr iterator end() noexcept { return iterator(rows + Size); }
        constexpr const_iterator end() const noexcept { return const_iterator(rows + Size); }
        constexpr const_iterator cend() const noexcept { return const_iterator(rows + Size); }

        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

        constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
        constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

        constexpr size_type size() const noexcept { return Size; }
        constexpr size_type max_size() const noexcept { return Size; }
        constexpr bool empty() const noexcept { return !Size; }

        constexpr value_type& operator[](size_type index) noexcept {
            return rows[index];
        }

        constexpr const value_type& operator[](size_type index) const noexcept {
            return rows[index];
        }

        constexpr value_type& at(size_type index) {
            if ( index < Size ) {
                return rows[index];
            }
            throw std::out_of_range("mat::at");
        }

        constexpr const value_type& at(size_type index) const {
            if ( index < Size ) {
                return rows[index];
            }
            throw std::out_of_range("mat::at");
        }
    };

    template < typename T, std::size_t Size >
    void swap(mat<T, Size>& l, mat<T, Size>& r) noexcept(noexcept(l.swap(r))) {
        l.swap(r);
    }
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    constexpr bool operator==(const mat<T, Size>& l, const mat<T, Size>& r) {
        for ( std::size_t i = 0; i < Size; ++i ) {
            if ( !(l[i] == r[i]) ) {
                return false;
            }
        }
        return true;
    }

    template < typename T, std::size_t Size >
    constexpr bool operator!=(const mat<T, Size>& l, const mat<T, Size>& r) {
        return !(l == r);
    }

    template < typename T, std::size_t Size >
    constexpr bool operator<(const mat<T, Size>& l, const mat<T, Size>& r) {
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