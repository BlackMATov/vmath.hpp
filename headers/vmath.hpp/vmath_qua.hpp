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
        T x{0}, y{0}, z{0}, w{1};
    public:
        constexpr qua_base() = default;

        constexpr explicit qua_base(T w)
        : x{0}, y{0}, z{0}, w{w} {}

        constexpr qua_base(T x, T y, T z, T w)
        : x{x}, y{y}, z{z}, w{w} {}

        constexpr qua_base(const vec<T, 3>& xyz, T w)
        : x{xyz[0]}, y{xyz[1]}, z{xyz[2]}, w{w} {}

        constexpr qua_base(const vec<T, 4>& xyzw)
        : x{xyzw[0]}, y{xyzw[1]}, z{xyzw[2]}, w{xyzw[3]} {}

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
    template < typename T >
    class qua final : public detail::qua_base<T> {
    public:
        using self_type = qua;
        using base_type = detail::qua_base<T>;
    public:
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
        using base_type::qua_base;
        using base_type::operator[];

        constexpr qua() = default;
        constexpr qua(const qua&) = default;
        constexpr qua& operator=(const qua&) = default;

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
            if ( index >= size ) {
                throw std::out_of_range("qua::at");
            }
            return (*this)[index];
        }

        [[nodiscard]] constexpr const_reference at(std::size_t index) const {
            if ( index >= size ) {
                throw std::out_of_range("qua::at");
            }
            return (*this)[index];
        }
    };
}

namespace vmath_hpp
{
    // qua

    template < typename T >
    qua(T) -> qua<T>;

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
