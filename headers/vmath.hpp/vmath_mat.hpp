/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_vec.hpp"
#include "vmath_vec_fun.hpp"

namespace vmath_hpp::detail
{
    template < typename T, std::size_t Size >
    class mat_base;

    template < typename T >
    class mat_base<T, 2> {
    public:
        using row_type = vec<T, 2>;
        row_type rows[2];
    public:
        constexpr mat_base()
        : mat_base(identity_init) {}

        constexpr explicit mat_base(uninit_t) {}

        constexpr explicit mat_base(zero_init_t)
        : rows{
            {T{0}, T{0}},
            {T{0}, T{0}}} {}

        constexpr explicit mat_base(identity_init_t)
        : rows{
            {T{1}, T{0}},
            {T{0}, T{1}}} {}

        constexpr explicit mat_base(T d)
        : rows{
            {d, T{0}},
            {T{0}, d}} {}

        constexpr explicit mat_base(const row_type& d)
        : rows{
            {d[0], T{0}},
            {T{0}, d[1]}} {}

        constexpr mat_base(
            T m11, T m12,
            T m21, T m22)
        : rows{
            {m11, m12},
            {m21, m22}} {}

        constexpr mat_base(
            const row_type& row0,
            const row_type& row1)
        : rows{row0, row1} {}
    };

    template < typename T >
    class mat_base<T, 3> {
    public:
        using row_type = vec<T, 3>;
        row_type rows[3];
    public:
        constexpr mat_base()
        : mat_base(identity_init) {}

        constexpr explicit mat_base(uninit_t) {}

        constexpr explicit mat_base(zero_init_t)
        : rows{
            {T{0}, T{0}, T{0}},
            {T{0}, T{0}, T{0}},
            {T{0}, T{0}, T{0}}} {}

        constexpr explicit mat_base(identity_init_t)
        : rows{
            {T{1}, T{0}, T{0}},
            {T{0}, T{1}, T{0}},
            {T{0}, T{0}, T{1}}} {}

        constexpr explicit mat_base(T d)
        : rows{
            {d, T{0}, T{0}},
            {T{0}, d, T{0}},
            {T{0}, T{0}, d}} {}

        constexpr explicit mat_base(const row_type& d)
        : rows{
            {d[0], T{0}, T{0}},
            {T{0}, d[1], T{0}},
            {T{0}, T{0}, d[2]}} {}

        constexpr mat_base(
            T m11, T m12, T m13,
            T m21, T m22, T m23,
            T m31, T m32, T m33)
        : rows{
            {m11, m12, m13},
            {m21, m22, m23},
            {m31, m32, m33}} {}

        constexpr mat_base(
            const row_type& row0,
            const row_type& row1,
            const row_type& row2)
        : rows{row0, row1, row2} {}

        constexpr mat_base(
            const mat_base<T, 2>& m,
            const vec_base<T, 2>& v)
        : rows{
            {m.rows[0], T{0}},
            {m.rows[1], T{0}},
            {v, T{1}}} {}

        constexpr explicit mat_base(
            const mat_base<T, 2>& other)
        : rows{
            {other.rows[0], T{0}},
            {other.rows[1], T{0}},
            {T{0}, T{0}, T{1}}} {}

        constexpr explicit operator mat<T, 2>() const {
            return {
                vec<T, 2>{rows[0]},
                vec<T, 2>{rows[1]}};
        }
    };

    template < typename T >
    class mat_base<T, 4> {
    public:
        using row_type = vec<T, 4>;
        row_type rows[4];
    public:
        constexpr mat_base()
        : mat_base(identity_init) {}

        constexpr explicit mat_base(uninit_t) {}

        constexpr explicit mat_base(zero_init_t)
        : rows{
            {T{0}, T{0}, T{0}, T{0}},
            {T{0}, T{0}, T{0}, T{0}},
            {T{0}, T{0}, T{0}, T{0}},
            {T{0}, T{0}, T{0}, T{0}}} {}

        constexpr explicit mat_base(identity_init_t)
        : rows{
            {T{1}, T{0}, T{0}, T{0}},
            {T{0}, T{1}, T{0}, T{0}},
            {T{0}, T{0}, T{1}, T{0}},
            {T{0}, T{0}, T{0}, T{1}}} {}

        constexpr explicit mat_base(T d)
        : rows{
            {d, T{0}, T{0}, T{0}},
            {T{0}, d, T{0}, T{0}},
            {T{0}, T{0}, d, T{0}},
            {T{0}, T{0}, T{0}, d}} {}

        constexpr explicit mat_base(const row_type& d)
        : rows{
            {d[0], T{0}, T{0}, T{0}},
            {T{0}, d[1], T{0}, T{0}},
            {T{0}, T{0}, d[2], T{0}},
            {T{0}, T{0}, T{0}, d[3]}} {}

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
            const row_type& row0,
            const row_type& row1,
            const row_type& row2,
            const row_type& row3)
        : rows{row0, row1, row2, row3} {}

        constexpr mat_base(
            const mat_base<T, 3>& m,
            const vec_base<T, 3>& v)
        : rows{
            {m.rows[0], T{0}},
            {m.rows[1], T{0}},
            {m.rows[2], T{0}},
            {v, T{1}}} {}

        constexpr explicit mat_base(
            const mat_base<T, 2>& other)
        : rows{
            {other.rows[0], T{0}, T{0}},
            {other.rows[1], T{0}, T{0}},
            {T{0}, T{0}, T{1}, T{0}},
            {T{0}, T{0}, T{0}, T{1}}} {}

        constexpr explicit mat_base(
            const mat_base<T, 3>& other)
        : rows{
            {other.rows[0], T{0}},
            {other.rows[1], T{0}},
            {other.rows[2], T{0}},
            {T{0}, T{0}, T{0}, T{1}}} {}

        constexpr explicit operator mat<T, 2>() const {
            return {
                vec<T, 2>{rows[0]},
                vec<T, 2>{rows[1]}};
        }

        constexpr explicit operator mat<T, 3>() const {
            return {
                vec<T, 3>{rows[0]},
                vec<T, 3>{rows[1]},
                vec<T, 3>{rows[2]}};
        }
    };
}

namespace vmath_hpp
{
    template < typename T, std::size_t Size >
    class mat final : public detail::mat_base<T, Size> {
    public:
        using self_type = mat;
        using base_type = detail::mat_base<T, Size>;
        using component_type = T;

        using row_type = vec<T, Size>;

        using pointer = row_type*;
        using const_pointer = const row_type*;

        using reference = row_type&;
        using const_reference = const row_type&;

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        static inline constexpr std::size_t size = Size;
    public:
        using base_type::mat_base;
        using base_type::rows;

        void swap(mat& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < Size; ++i ) {
                using std::swap;
                swap(rows[i], other.rows[i]);
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
            return &rows[0];
        }

        [[nodiscard]] const_pointer data() const noexcept {
            return &rows[0];
        }

        [[nodiscard]] constexpr reference at(std::size_t index) {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("mat::at"));
            return rows[index];
        }

        [[nodiscard]] constexpr const_reference at(std::size_t index) const {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("mat::at"));
            return rows[index];
        }

        [[nodiscard]] constexpr reference operator[](std::size_t index) noexcept {
            return rows[index];
        }

        [[nodiscard]] constexpr const_reference operator[](std::size_t index) const noexcept {
            return rows[index];
        }
    };
}

namespace vmath_hpp
{
    // mat2

    template < typename T >
    mat(T, T, T, T) -> mat<T, 2>;

    template < typename T >
    mat(const vec<T, 2>&, const vec<T, 2>&) -> mat<T, 2>;

    template < typename T >
    mat(std::initializer_list<T>, std::initializer_list<T>) -> mat<T, 2>;

    // mat3

    template < typename T >
    mat(T, T, T, T, T, T, T, T, T) -> mat<T, 3>;

    template < typename T >
    mat(const vec<T, 3>&, const vec<T, 3>&, const vec<T, 3>&) -> mat<T, 3>;

    template < typename T >
    mat(const mat<T, 2>&, const vec<T, 2>&) -> mat<T, 3>;

    template < typename T >
    mat(std::initializer_list<T>, std::initializer_list<T>, std::initializer_list<T>) -> mat<T, 3>;

    // mat4

    template < typename T >
    mat(T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T) -> mat<T, 4>;

    template < typename T >
    mat(const vec<T, 4>&, const vec<T, 4>&, const vec<T, 4>&, const vec<T, 4>&) -> mat<T, 4>;

    template < typename T >
    mat(const mat<T, 3>&, const vec<T, 3>&) -> mat<T, 4>;

    template < typename T >
    mat(std::initializer_list<T>, std::initializer_list<T>, std::initializer_list<T>, std::initializer_list<T>) -> mat<T, 4>;

    // swap

    template < typename T, std::size_t Size >
    void swap(mat<T, Size>& l, mat<T, Size>& r) noexcept(noexcept(l.swap(r))) {
        l.swap(r);
    }
}
