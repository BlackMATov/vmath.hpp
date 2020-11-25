/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_mat_fun.hpp>
#include <vmath.hpp/vmath_mat_ext.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "vmath_tests.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;

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

        {
            mat2i v{1,2,3,4};
            REQUIRE(&v == &(v += 3));
            REQUIRE(v == mat2i{4,5,6,7});
            REQUIRE(&v == &(v += mat2i{1,2,3,4}));
            REQUIRE(v == mat2i{5,7,9,11});
        }
        {
            mat2i v{4,5,6,7};
            REQUIRE(&v == &(v -= 3));
            REQUIRE(v == mat2i{1,2,3,4});
            REQUIRE(&v == &(v -= mat2i{2,4,6,8}));
            REQUIRE(v == mat2i{-1,-2,-3,-4});
        }
        {
            mat2i v{1,2,3,4};
            REQUIRE(&v == &(v *= 3));
            REQUIRE(v == mat2i{3,6,9,12});
        }
        {
            mat2i v{6,18,36,60};
            REQUIRE(&v == &(v /= 2));
            REQUIRE(v == mat2i{3,9,18,30});
            REQUIRE(&v == &(v /= mat2i{3,4,3,10}));
            REQUIRE(v == mat2i{1,2,6,3});
        }

        {
            vec4f v{0.f, 0.f, 0.f, 1.f};
            REQUIRE(&v == &(v *= translate(1.f,2.f,3.f)));
            REQUIRE(v == approx4(1.f,2.f,3.f,1.f));
        }
        {
            vec3f v{1.f, 2.f, 3.f};
            REQUIRE(&v == &(v *= mat3f(scale(2.f,3.f,4.f))));
            REQUIRE(v == approx3(2.f,6.f,12.f));
        }
        {
            mat4f v = translate(1.f, 2.f, 3.f);
            REQUIRE(&v == &(v *= translate(1.f,2.f,3.f)));
            REQUIRE(v == approx4x4(translate(2.f,4.f,6.f)));
        }
        {
            mat3f v = mat3f(scale(1.f, 2.f, 3.f));
            REQUIRE(&v == &(v *= mat3f(scale(2.f,3.f,4.f))));
            REQUIRE(v == approx3x3(mat3f(scale(2.f,6.f,12.f))));
        }
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
        {
            STATIC_REQUIRE(inverse(mat2i()) == mat2i());
            STATIC_REQUIRE(inverse(mat3i()) == mat3i());
            STATIC_REQUIRE(inverse(mat4i()) == mat4i());

            STATIC_REQUIRE(inverse(mat2f(0.5)) == mat2f(2.f));
            STATIC_REQUIRE(inverse(mat3f(0.5)) == mat3f(2.f));
            STATIC_REQUIRE(inverse(mat4f(0.5)) == mat4f(2.f));

            STATIC_REQUIRE(inverse(translate(1.f,2.f,3.f)) == approx4x4(translate(-1.f,-2.f,-3.f)));

            REQUIRE(inverse(rotate(0.5f,normalize(vec3f{1.f,2.f,3.f}))) == approx4x4(rotate(-0.5f,normalize(vec3f{1.f,2.f,3.f}))));
            REQUIRE(inverse(mat3f(rotate(0.5f,normalize(vec3f{1.f,2.f,3.f})))) == approx3x3(mat3f(rotate(-0.5f,normalize(vec3f{1.f,2.f,3.f})))));
            REQUIRE(inverse(mat2f(rotate(0.5f,vec3f{0,0,1}))) == approx2x2(mat2f(rotate(-0.5f,vec3f{0,0,1}))));
        }
    }
}
