/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_vec.hpp"
#include "vmath_vec_fun.hpp"

namespace vmath_hpp
{
    template < typename T >
    class qua final {
    public:
        vec<T, 3> v{0};
        T s{1};
    public:
        using self_type = qua;
        using component_type = T;

        using pointer = component_type*;
        using const_pointer = const component_type*;

        using reference = component_type&;
        using const_reference = const component_type&;

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        static constexpr std::size_t size = 4;
    public:
        constexpr qua() = default;
        constexpr qua(const qua&) = default;
        constexpr qua& operator=(const qua&) = default;

        constexpr qua(T vx, T vy, T vz, T s)
        : v{vx, vy, vz}
        , s{s} {}

        constexpr qua(const vec<T, 3>& v, T s)
        : v{v}
        , s{s} {}

        constexpr explicit qua(const vec<T, 4>& vs)
        : v{vs[0], vs[1], vs[2]}
        , s{vs[3]} {}

        constexpr explicit operator vec<T, 4>() const {
            return {(*this).v, (*this).s};
        }

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

        [[nodiscard]] constexpr reference operator[](std::size_t index) noexcept {
            switch ( index ) {
            default:
            case 0: return v.x;
            case 1: return v.y;
            case 2: return v.z;
            case 3: return s;
            }
        }

        [[nodiscard]] constexpr const_reference operator[](std::size_t index) const noexcept {
            switch ( index ) {
            default:
            case 0: return v.x;
            case 1: return v.y;
            case 2: return v.z;
            case 3: return s;
            }
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
