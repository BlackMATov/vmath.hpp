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

        constexpr explicit mat_base(T v)
        : rows{
            {v, 0},
            {0, v}} {}

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

        constexpr explicit mat_base(
            const mat_base<T, 3>& other)
        : rows{
            vec<T, 2>{other.rows[0]},
            vec<T, 2>{other.rows[1]}} {}

        constexpr explicit mat_base(
            const mat_base<T, 4>& other)
        : rows{
            vec<T, 2>{other.rows[0]},
            vec<T, 2>{other.rows[1]}} {}
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

        constexpr explicit mat_base(T v)
        : rows{
            {v, 0, 0},
            {0, v, 0},
            {0, 0, v}} {}

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

        constexpr explicit mat_base(
            const mat_base<T, 2>& other)
        : rows{
            {other.rows[0], 0},
            {other.rows[1], 0},
            {0, 0, 1}} {}

        constexpr explicit mat_base(
            const mat_base<T, 4>& other)
        : rows{
            vec<T, 3>{other.rows[0]},
            vec<T, 3>{other.rows[1]},
            vec<T, 3>{other.rows[2]}} {}
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

        constexpr explicit mat_base(T v)
        : rows{
            {v, 0, 0, 0},
            {0, v, 0, 0},
            {0, 0, v, 0},
            {0, 0, 0, v}} {}

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

        constexpr explicit mat_base(
            const mat_base<T, 2>& other)
        : rows{
            {other.rows[0], 0, 0},
            {other.rows[1], 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}} {}

        constexpr explicit mat_base(
            const mat_base<T, 3>& other)
        : rows{
            {other.rows[0], 0},
            {other.rows[1], 0},
            {other.rows[2], 0},
            {0, 0, 0, 1}} {}
    };
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class mat final : public detail::mat_base<T, Size> {
    public:
        using self_type = mat;
        using base_type = detail::mat_base<T, Size>;
    public:
        using value_type = vec<T, Size>;

        using pointer = value_type*;
        using const_pointer = const value_type*;

        using reference = value_type&;
        using const_reference = const value_type&;

        static constexpr std::size_t size = Size;
    public:
        using base_type::rows;
        using base_type::mat_base;

        mat() = default;

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

        constexpr reference operator[](std::size_t index) noexcept {
            return rows[index];
        }

        constexpr const_reference operator[](std::size_t index) const noexcept {
            return rows[index];
        }

        constexpr reference at(std::size_t index) {
            if ( index >= Size ) {
                throw std::out_of_range("mat::at");
            }
            return rows[index];
        }

        constexpr const_reference at(std::size_t index) const {
            if ( index >= Size ) {
                throw std::out_of_range("mat::at");
            }
            return rows[index];
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
