/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_ext.hpp>

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
    SECTION("Detail") {
        STATIC_REQUIRE(map([](const int2& x){
            return x * 2;
        }, int2x2{}) == int2x2(2,0,0,2));

        STATIC_REQUIRE(zip([](const int2& x, const int2& y){
            return x + y;
        }, int2x2{}, int2x2{}) == int2x2(2,0,0,2));

        STATIC_REQUIRE(zip([](const int2& x, const int2& y, const int2& z){
            return x + y + z;
        }, int2x2{}, int2x2{}, int2x2{}) == int2x2(3,0,0,3));

        STATIC_REQUIRE(fold([](int acc, const int2& x){
            return acc + x.x;
        }, 0, int2x2{}) == 1);

        STATIC_REQUIRE(fold([](int acc, const int2& x, const int2& y){
            return acc + x.x + y.x;
        }, 0, int2x2{}, int2x2{}) == 2);

        STATIC_REQUIRE(fold1([](const int2& acc, const int2& x){
            return acc + x;
        }, int2x2{}) == int2(1,1));
    }

    SECTION("Operators") {
        STATIC_REQUIRE(-int2x2(1,2,3,4) == int2x2(-1,-2,-3,-4));

        STATIC_REQUIRE(int2x2(1,2,3,4) + 2 == int2x2(3,4,5,6));
        STATIC_REQUIRE(int2x2(1,2,3,4) - 2 == int2x2(-1,0,1,2));
        STATIC_REQUIRE(int2x2(1,2,3,4) * 2 == int2x2(2,4,6,8));
        STATIC_REQUIRE(int2x2(1,2,3,4) / 2 == int2x2(0,1,1,2));

        STATIC_REQUIRE(4 + int2x2(1,2,3,4) == int2x2(5,6,7,8));
        STATIC_REQUIRE(4 - int2x2(1,2,3,4) == int2x2(3,2,1,0));
        STATIC_REQUIRE(4 * int2x2(1,2,3,4) == int2x2(4,8,12,16));
        STATIC_REQUIRE(4 / int2x2(1,2,3,4) == int2x2(4,2,1,1));

        STATIC_REQUIRE(int2x2(1,2,3,4) + int2x2(5,6,7,8) == int2x2(6,8,10,12));
        STATIC_REQUIRE(int2x2(1,2,3,4) - int2x2(5,6,7,8) == int2x2(-4,-4,-4,-4));
        STATIC_REQUIRE(int2x2(5,6,7,8) / int2x2(1,2,3,4) == int2x2(5,3,2,2));

        STATIC_REQUIRE(int2x2() * int2x2() == int2x2());
        STATIC_REQUIRE(int3x3() * int3x3() == int3x3());

        STATIC_REQUIRE(int2(1,2) * int2x2() == int2(1,2));
        STATIC_REQUIRE(int3(1,2,3) * int3x3() == int3(1,2,3));
        STATIC_REQUIRE(int4(1,2,3,4) * int4x4() == int4(1,2,3,4));

        {
            int2x2 v{1,2,3,4};
            REQUIRE(&v == &(v += 3));
            REQUIRE(v == int2x2{4,5,6,7});
            REQUIRE(&v == &(v += int2x2{1,2,3,4}));
            REQUIRE(v == int2x2{5,7,9,11});
        }
        {
            int2x2 v{4,5,6,7};
            REQUIRE(&v == &(v -= 3));
            REQUIRE(v == int2x2{1,2,3,4});
            REQUIRE(&v == &(v -= int2x2{2,4,6,8}));
            REQUIRE(v == int2x2{-1,-2,-3,-4});
        }
        {
            int2x2 v{1,2,3,4};
            REQUIRE(&v == &(v *= 3));
            REQUIRE(v == int2x2{3,6,9,12});
        }
        {
            int2x2 v{6,18,36,60};
            REQUIRE(&v == &(v /= 2));
            REQUIRE(v == int2x2{3,9,18,30});
            REQUIRE(&v == &(v /= int2x2{3,4,3,10}));
            REQUIRE(v == int2x2{1,2,6,3});
        }

        {
            int4 v{0, 0, 0, 1};
            REQUIRE(&v == &(v *= translate(int3{1,2,3})));
            REQUIRE(v == approx4(1,2,3,1));
        }
        {
            int3 v{1, 2, 3};
            REQUIRE(&v == &(v *= int3x3(scale(int3{2,3,4}))));
            REQUIRE(v == int3(2,6,12));
        }
        {
            int4x4 v = translate(int3{1, 2, 3});
            REQUIRE(&v == &(v *= translate(int3{1,2,3})));
            REQUIRE(v == translate(int3{2,4,6}));
        }
        {
            int3x3 v = int3x3(scale(int3{1, 2, 3}));
            REQUIRE(&v == &(v *= int3x3(scale(int3{2,3,4}))));
            REQUIRE(v == int3x3(scale(int3{2,6,12})));
        }
    }

    SECTION("Matrix Functions") {
        {
            STATIC_REQUIRE(transpose(int2x2(
                1, 2,
                3, 4
            )) == int2x2(
                1, 3,
                2, 4
            ));

            STATIC_REQUIRE(transpose(int3x3(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            )) == int3x3(
                1, 4, 7,
                2, 5, 8,
                3, 6, 9
            ));

            STATIC_REQUIRE(transpose(int4x4(
                1,  2,  3,  4,
                5,  6,  7,  8,
                9,  10, 11, 12,
                13, 14, 15, 16
            )) == int4x4(
                1, 5, 9,  13,
                2, 6, 10, 14,
                3, 7, 11, 15,
                4, 8, 12, 16
            ));
        }
        {
            constexpr int2x2 m2{1,2,3,4};
            constexpr int3x3 m3{1,2,3,4,5,6,7,8,9};
            constexpr int4x4 m4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
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
            STATIC_REQUIRE(inverse(float2x2()) == float2x2());
            STATIC_REQUIRE(inverse(float3x3()) == float3x3());
            STATIC_REQUIRE(inverse(float4x4()) == float4x4());

            STATIC_REQUIRE(inverse(float2x2(0.5)) == float2x2(2.f));
            STATIC_REQUIRE(inverse(float3x3(0.5)) == float3x3(2.f));
            STATIC_REQUIRE(inverse(float4x4(0.5)) == float4x4(2.f));

            STATIC_REQUIRE(inverse(translate(float3{1.f,2.f,3.f})) == approx4x4(translate(float3{-1.f,-2.f,-3.f})));

            REQUIRE(inverse(rotate(0.5f,normalize(float3{1.f,2.f,3.f}))) == approx4x4(rotate(-0.5f,normalize(float3{1.f,2.f,3.f}))));
            REQUIRE(inverse(float3x3(rotate(0.5f,normalize(float3{1.f,2.f,3.f})))) == approx3x3(float3x3(rotate(-0.5f,normalize(float3{1.f,2.f,3.f})))));
            REQUIRE(inverse(float2x2(rotate(0.5f,float3{0,0,1}))) == approx2x2(float2x2(rotate(-0.5f,float3{0,0,1}))));
        }
    }
}
