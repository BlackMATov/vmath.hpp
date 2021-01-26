/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"
#include "catch/catch.hpp"

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
    SECTION("detail") {
        STATIC_REQUIRE(map_join([](const int2& x){
            return x * 2;
        }, int2x2{}) == int2x2(2,0,0,2));

        STATIC_REQUIRE(map_join([](const int2& x, const int2& y){
            return x + y;
        }, int2x2{}, int2x2{}) == int2x2(2,0,0,2));

        STATIC_REQUIRE(map_join([](const int2& x, const int2& y, const int2& z){
            return x + y + z;
        }, int2x2{}, int2x2{}, int2x2{}) == int2x2(3,0,0,3));

        STATIC_REQUIRE(fold_join([](int acc, const int2& x){
            return acc + x.x;
        }, 0, int2x2{}) == 1);

        STATIC_REQUIRE(fold_join([](int acc, const int2& x, const int2& y){
            return acc + x.x + y.x;
        }, 0, int2x2{}, int2x2{}) == 2);

        STATIC_REQUIRE(fold1_join([](const int2& acc, const int2& x){
            return acc + x;
        }, int2x2{}) == int2(1,1));
    }

    SECTION("operators") {
        STATIC_REQUIRE(-int2x2(1,2,3,4) == int2x2(-1,-2,-3,-4));
        STATIC_REQUIRE(~uint2x2(0xF0F0F0F0,0x0F0F0F0F,0xF0F0F0F0,0x0F0F0F0F) == uint2x2(0x0F0F0F0F,0xF0F0F0F0,0x0F0F0F0F,0xF0F0F0F0));
        STATIC_REQUIRE(!int2x2(-1,0,1,2) == bool2x2(false,true,false,false));

        STATIC_REQUIRE(int2x2(1,2,3,4) + 2 == int2x2(3,4,5,6));
        STATIC_REQUIRE(int2x2(1,2,3,4) - 2 == int2x2(-1,0,1,2));
        STATIC_REQUIRE(int2x2(1,2,3,4) * 2 == int2x2(2,4,6,8));
        STATIC_REQUIRE(int2x2(1,2,3,4) / 2 == int2x2(0,1,1,2));
        STATIC_REQUIRE((int2x2(11,12,11,12) & 6) == int2x2(2,4,2,4));
        STATIC_REQUIRE((int2x2(11,12,11,12) | 6) == int2x2(15,14,15,14));
        STATIC_REQUIRE((int2x2(11,12,11,12) ^ 6) == int2x2(13,10,13,10));
        STATIC_REQUIRE((int2x2(1,0,1,0) && 1) == bool2x2(1,0,1,0));
        STATIC_REQUIRE((int2x2(1,0,1,0) || 1) == bool2x2(1,1,1,1));

        STATIC_REQUIRE(4 + int2x2(1,2,3,4) == int2x2(5,6,7,8));
        STATIC_REQUIRE(4 - int2x2(1,2,3,4) == int2x2(3,2,1,0));
        STATIC_REQUIRE(4 * int2x2(1,2,3,4) == int2x2(4,8,12,16));
        STATIC_REQUIRE(4 / int2x2(1,2,3,4) == int2x2(4,2,1,1));
        STATIC_REQUIRE((6 &int2x2(11,12,11,12)) == int2x2(2,4,2,4));
        STATIC_REQUIRE((6 |int2x2(11,12,11,12)) == int2x2(15,14,15,14));
        STATIC_REQUIRE((6 ^ int2x2(11,12,11,12)) == int2x2(13,10,13,10));
        STATIC_REQUIRE((1 && int2x2(1,0,1,0)) == bool2x2(1,0,1,0));
        STATIC_REQUIRE((1 || int2x2(1,0,1,0)) == bool2x2(1,1,1,1));

        STATIC_REQUIRE(int2x2(1,2,3,4) + int2x2(5,6,7,8) == int2x2(6,8,10,12));
        STATIC_REQUIRE(int2x2(1,2,3,4) - int2x2(5,6,7,8) == int2x2(-4,-4,-4,-4));

        STATIC_REQUIRE(int2x2() * int2x2() == int2x2());
        STATIC_REQUIRE(int3x3() * int3x3() == int3x3());

        STATIC_REQUIRE(int2(1,2) * int2x2() == int2(1,2));
        STATIC_REQUIRE(int3(1,2,3) * int3x3() == int3(1,2,3));
        STATIC_REQUIRE(int4(1,2,3,4) * int4x4() == int4(1,2,3,4));

        STATIC_REQUIRE((int2x2(6,7,6,7) & int2x2(11,12,11,12)) == int2x2(2,4,2,4));
        STATIC_REQUIRE((int2x2(6,7,6,7) | int2x2(11,12,11,12)) == int2x2(15,15,15,15));
        STATIC_REQUIRE((int2x2(6,7,6,7) ^ int2x2(11,12,11,12)) == int2x2(13,11,13,11));
        STATIC_REQUIRE((int2x2(0,1,0,1) && int2x2(1,0,1,0)) == bool2x2(0,0,0,0));
        STATIC_REQUIRE((int2x2(0,1,0,1) || int2x2(1,0,1,0)) == bool2x2(1,1,1,1));

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
            int4 v{0, 0, 0, 1};
            REQUIRE(&v == &(v *= translate(int3{1,2,3})));
            REQUIRE(v == uapprox4(1,2,3,1));
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
        {
            int2x2 v1{11,12,11,12};
            REQUIRE(&v1 == &(v1 &= 6));
            REQUIRE(v1 == int2x2(2,4,2,4));
            int2x2 v2{6,7,6,7};
            REQUIRE(&v2 == &(v2 &= int2x2(11,12,11,12)));
            REQUIRE(v2 == int2x2(2,4,2,4));
        }
        {
            int2x2 v1{11,12,11,12};
            REQUIRE(&v1 == &(v1 |= 6));
            REQUIRE(v1 == int2x2(15,14,15,14));
            int2x2 v2{6,7,6,7};
            REQUIRE(&v2 == &(v2 |= int2x2(11,12,11,12)));
            REQUIRE(v2 == int2x2(15,15,15,15));
        }
        {
            int2x2 v1{11,12,11,12};
            REQUIRE(&v1 == &(v1 ^= 6));
            REQUIRE(v1 == int2x2(13,10,13,10));
            int2x2 v2{6,7,6,7};
            REQUIRE(&v2 == &(v2 ^= int2x2(11,12,11,12)));
            REQUIRE(v2 == int2x2(13,11,13,11));
        }
    }

    SECTION("relational functions") {
        STATIC_REQUIRE_FALSE(any(bool2x2(false, false, false, false)));
        STATIC_REQUIRE(any(bool2x2(true, false, true, false)));
        STATIC_REQUIRE(any(bool2x2(false, true, false, true)));
        STATIC_REQUIRE(any(bool2x2(true, true, true, true)));

        STATIC_REQUIRE_FALSE(any(int2x2(0, 0, 0, 0)));
        STATIC_REQUIRE(any(int2x2(1, 0, 1, 0)));
        STATIC_REQUIRE(any(int2x2(0, 1, 0, 1)));
        STATIC_REQUIRE(any(int2x2(1, 1, 1, 1)));

        STATIC_REQUIRE_FALSE(all(bool2x2(false, false, false, false)));
        STATIC_REQUIRE_FALSE(all(bool2x2(true, false, true, false)));
        STATIC_REQUIRE_FALSE(all(bool2x2(false, true, false, true)));
        STATIC_REQUIRE(all(bool2x2(true, true, true, true)));

        STATIC_REQUIRE_FALSE(all(int2x2(0, 0, 0, 0)));
        STATIC_REQUIRE_FALSE(all(int2x2(1, 0, 1, 0)));
        STATIC_REQUIRE_FALSE(all(int2x2(0, 1, 0, 1)));
        STATIC_REQUIRE(all(int2x2(1, 1, 1, 1)));

        STATIC_REQUIRE(approx(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(false, true, false, false));
        STATIC_REQUIRE(approx(int2x2(1,1,1,1), int2x2(0,1,2,3), 0) == bool2x2(false, true, false, false));
        STATIC_REQUIRE(approx(int2x2(1,1,1,1), int2x2(0,1,2,3), 1) == bool2x2(true, true, true, false));
        STATIC_REQUIRE(approx(int2x2(1,1,1,1), int2x2(0,1,2,3), 2) == bool2x2(true, true, true, true));

        STATIC_REQUIRE(less(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(false, false, true, true));
        STATIC_REQUIRE(less_equal(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(false, true, true, true));
        STATIC_REQUIRE(greater(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(true, false, false, false));
        STATIC_REQUIRE(greater_equal(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(true, true, false, false));

        STATIC_REQUIRE(equal_to(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(false, true, false, false));
        STATIC_REQUIRE(not_equal_to(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(true, false, true, true));
    }

    SECTION("transpose") {
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

    SECTION("determinant") {
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

    SECTION("inverse") {
        STATIC_REQUIRE(inverse(float2x2()) == float2x2());
        STATIC_REQUIRE(inverse(float3x3()) == float3x3());
        STATIC_REQUIRE(inverse(float4x4()) == float4x4());

        STATIC_REQUIRE(inverse(float2x2(0.5)) == float2x2(2.f));
        STATIC_REQUIRE(inverse(float3x3(0.5)) == float3x3(2.f));
        STATIC_REQUIRE(inverse(float4x4(0.5)) == float4x4(2.f));

        {
            constexpr float4x4 m1 = translate(float3(1.f, 2.f, 3.f));
            constexpr float4x4 rm1 = inverse(m1);
            STATIC_REQUIRE(all(approx(
                unit4_z<float> * m1 * rm1,
                unit4_z<float>,
                uapprox_epsilon_v<float>)));
        }

        {
            const float3 axis2 = normalize(float3(1.f, 2.f, 3.f));
            const float4x4 m2 = rotate(0.5f,axis2);
            const float4x4 rm2 = inverse(m2);
            REQUIRE(all(approx(
                unit4_z<float> * m2 * rm2,
                unit4_z<float>,
                uapprox_epsilon_v<float>)));
        }

        {
            const float3 axis3 = normalize(float3(1.f, 2.f, 3.f));
            const float3x3 m3 = float3x3(rotate(0.5f,axis3));
            const float3x3 rm3 = inverse(m3);
            REQUIRE(all(approx(
                unit3_z<float> * m3 * rm3,
                unit3_z<float>,
                uapprox_epsilon_v<float>)));
        }

        {
            const float3 axis4 = normalize(float3(0.f, 0.f, 3.f));
            const float2x2 m4 = float2x2(rotate(0.5f,axis4));
            const float2x2 rm4 = inverse(m4);
            REQUIRE(all(approx(
                unit2_y<float> * m4 * rm4,
                unit2_y<float>,
                uapprox_epsilon_v<float>)));
        }
    }
}
