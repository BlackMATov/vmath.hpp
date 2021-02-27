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
    template < typename T >
    class qua_base {
    public:
        vec<T, 3> v;
        T s;
    public:
        constexpr qua_base()
        : qua_base(identity_init) {}

        constexpr qua_base(uninit_t) {}
        constexpr qua_base(zero_init_t) : qua_base{zero_init, T{0}} {}
        constexpr qua_base(identity_init_t) : qua_base{zero_init, T{1}} {}

        constexpr qua_base(T vx, T vy, T vz, T s): v{vx, vy, vz}, s{s} {}
        constexpr qua_base(const vec<T, 3>& v, T s): v{v}, s{s} {}
        constexpr explicit qua_base(const vec<T, 4>& vs): v{vs[0], vs[1], vs[2]}, s{vs[3]} {}

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr qua_base(const qua_base<U>& other): qua_base(other.v, other.s) {}

        template < typename U, std::enable_if_t<std::is_convertible_v<T, U>, int> = 0 >
        constexpr explicit operator vec<U, 4>() const { return vec<U, 4>(v, s); }

        template < typename U, std::enable_if_t<std::is_convertible_v<U, T>, int> = 0 >
        constexpr explicit qua_base(const U* p): qua_base(p[0], p[1], p[2], p[3]) {}

        [[nodiscard]] constexpr T& operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return v.x;
            case 1: return v.y;
            case 2: return v.z;
            case 3: return s;
            }
        }

        [[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return v.x;
            case 1: return v.y;
            case 2: return v.z;
            case 3: return s;
            }
        }
    };
}

namespace vmath_hpp
{
    template < typename T >
    class qua final : public detail::qua_base<T> {
    public:
        using self_type = qua;
        using base_type = detail::qua_base<T>;
        using component_type = T;

        using imag_type = vec<T, 3>;
        using real_type = T;

        using pointer = component_type*;
        using const_pointer = const component_type*;

        using reference = component_type&;
        using const_reference = const component_type&;

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        static inline constexpr std::size_t size = 4;
    public:
        using base_type::qua_base;
        using base_type::operator[];

        void swap(qua& other) noexcept(std::is_nothrow_swappable_v<T>) {
            for ( std::size_t i = 0; i < size; ++i ) {
                using std::swap;
                swap((*this)[i], other[i]);
            }
        }

        [[nodiscard]] iterator begin() noexcept { return iterator(data()); }
        [[nodiscard]] const_iterator begin() const noexcept { return const_iterator(data()); }
        [[nodiscard]] iterator end() noexcept { return iterator(data() + size); }
        [[nodiscard]] const_iterator end() const noexcept { return const_iterator(data() + size); }

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
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("qua::at"));
            return (*this)[index];
        }

        [[nodiscard]] constexpr const_reference at(std::size_t index) const {
            VMATH_HPP_THROW_IF(index >= size, std::out_of_range("qua::at"));
            return (*this)[index];
        }
    };
}

namespace vmath_hpp
{
    // vec

    template < typename T >
    vec(const qua<T>&) -> vec<T, 4>;

    // qua

    template < typename T >
    qua(T, T, T, T) -> qua<T>;

    template < typename T >
    qua(const vec<T, 3>&, T) -> qua<T>;

    template < typename T >
    qua(const vec<T, 4>&) -> qua<T>;

    template < typename T >
    qua(std::initializer_list<T>) -> qua<T>;

    // swap

    template < typename T >
    void swap(qua<T>& l, qua<T>& r) noexcept(noexcept(l.swap(r))) {
        l.swap(r);
    }
}
