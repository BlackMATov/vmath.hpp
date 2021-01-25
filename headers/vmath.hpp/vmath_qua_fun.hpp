/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_qua.hpp"

#include "vmath_vec.hpp"
#include "vmath_vec_fun.hpp"

//
// Operators
//

namespace vmath_hpp
{
    // +operator

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator+(const qua<T>& xs) {
        return xs;
    }

    // -operator

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator-(const qua<T>& xs) {
        return qua(-vec<T, 4>{xs});
    }

    // operator+

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator+(const qua<T>& xs, const qua<T>& ys) {
        return qua(vec{xs} + vec{ys});
    }

    // operator+=

    template < typename T >
    constexpr qua<T>& operator+=(qua<T>& xs, const qua<T>& ys) {
        return (xs = (xs + ys));
    }

    // operator-

    template < typename T >
    [[nodiscard]] constexpr qua<T> operator-(const qua<T>& xs, const qua<T>& ys) {
        return qua(vec{xs} - vec{ys});
    }

    // operator-=

    template < typename T >
    constexpr qua<T>& operator-=(qua<T>& xs, const qua<T>& ys) {
        return (xs = (xs - ys));
    }

    // operator==

    template < typename T >
    [[nodiscard]] constexpr bool operator==(const qua<T>& xs, const qua<T>& ys) {
        return vec{xs} == vec{ys};
    }

    // operator!=

    template < typename T >
    [[nodiscard]] constexpr bool operator!=(const qua<T>& xs, const qua<T>& ys) {
        return vec{xs} != vec{ys};
    }

    // operator<

    template < typename T >
    [[nodiscard]] constexpr bool operator<(const qua<T>& xs, const qua<T>& ys) {
        return vec{xs} < vec{ys};
    }
}

    }
}
