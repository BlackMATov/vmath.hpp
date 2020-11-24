/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_mat_fun.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
    using namespace vmath_hpp;

    template < typename T, int Size >
    constexpr mat<T, Size> generate_frank_matrix() {
        mat<T, Size> m;
        for ( int i = 1; i <= Size; ++i ) {
            for ( int j = 1; j <= Size; ++j ) {
                if ( j < i - Size ) {
                    m[i - 1][j - 1] = 0;
                } else if ( j == (i - 1) ) {
                    m[i - 1][j - 1] = Size + 1 - i;
                } else {
                    m[i - 1][j - 1] = Size + 1 - j;
                }
            }
        }
        return m;
    }
}

TEST_CASE("vmath/mat_fun") {
    SECTION("Operators") {
        STATIC_REQUIRE(-mat2i(1,2,3,4) == mat2i(-1,-2,-3,-4));

        STATIC_REQUIRE(mat2i(1,2,3,4) + 2 == mat2i(3,4,5,6));
        STATIC_REQUIRE(mat2i(1,2,3,4) - 2 == mat2i(-1,0,1,2));
        STATIC_REQUIRE(mat2i(1,2,3,4) * 2 == mat2i(2,4,6,8));
        STATIC_REQUIRE(mat2i(1,2,3,4) / 2 == mat2i(0,1,1,2));

        STATIC_REQUIRE(4 + mat2i(1,2,3,4) == mat2i(5,6,7,8));
        STATIC_REQUIRE(4 - mat2i(1,2,3,4) == mat2i(3,2,1,0));
        STATIC_REQUIRE(4 * mat2i(1,2,3,4) == mat2i(4,8,12,16));
        STATIC_REQUIRE(4 / mat2i(1,2,3,4) == mat2i(4,2,1,1));

        STATIC_REQUIRE(mat2i(1,2,3,4) + mat2i(5,6,7,8) == mat2i(6,8,10,12));
        STATIC_REQUIRE(mat2i(1,2,3,4) - mat2i(5,6,7,8) == mat2i(-4,-4,-4,-4));
        STATIC_REQUIRE(mat2i(5,6,7,8) / mat2i(1,2,3,4) == mat2i(5,3,2,2));

        STATIC_REQUIRE(mat2i() * mat2i() == mat2i());
        STATIC_REQUIRE(mat3i() * mat3i() == mat3i());

        STATIC_REQUIRE(vec2i(1,2) * mat2i() == vec2i(1,2));
        STATIC_REQUIRE(vec3i(1,2,3) * mat3i() == vec3i(1,2,3));
        STATIC_REQUIRE(vec4i(1,2,3,4) * mat4i() == vec4i(1,2,3,4));
    }

    SECTION("Matrix Functions") {
        {
            STATIC_REQUIRE(transpose(mat2i(
                1, 2,
                3, 4
            )) == mat2i(
                1, 3,
                2, 4
            ));

            STATIC_REQUIRE(transpose(mat3i(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            )) == mat3i(
                1, 4, 7,
                2, 5, 8,
                3, 6, 9
            ));

            STATIC_REQUIRE(transpose(mat4i(
                1,  2,  3,  4,
                5,  6,  7,  8,
                9,  10, 11, 12,
                13, 14, 15, 16
            )) == mat4i(
                1, 5, 9,  13,
                2, 6, 10, 14,
                3, 7, 11, 15,
                4, 8, 12, 16
            ));
        }
        {
            constexpr mat2i m2{1,2,3,4};
            constexpr mat3i m3{1,2,3,4,5,6,7,8,9};
            constexpr mat4i m4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
            STATIC_REQUIRE(determinant(m2) == determinant(transpose(m2)));
            STATIC_REQUIRE(determinant(m3) == determinant(transpose(m3)));
            STATIC_REQUIRE(determinant(m4) == determinant(transpose(m4)));

            STATIC_REQUIRE(determinant(generate_frank_matrix<int, 2>()) == 1);
            STATIC_REQUIRE(determinant(generate_frank_matrix<int, 3>()) == 1);
            STATIC_REQUIRE(determinant(generate_frank_matrix<int, 4>()) == 1);

            STATIC_REQUIRE(determinant(transpose(generate_frank_matrix<int, 2>())) == 1);
            STATIC_REQUIRE(determinant(transpose(generate_frank_matrix<int, 3>())) == 1);
            STATIC_REQUIRE(determinant(transpose(generate_frank_matrix<int, 4>())) == 1);
        }
    }
}
