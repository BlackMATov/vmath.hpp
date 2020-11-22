/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_mat.hpp"

//
// Operators
//

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
