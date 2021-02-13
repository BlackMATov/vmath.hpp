/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

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
    SUBCASE("detail") {
        STATIC_CHECK(map_join([](const int2& x){
            return x * 2;
        }, int2x2{}) == int2x2(2,0,0,2));

        STATIC_CHECK(map_join([](const int2& x, const int2& y){
            return x + y;
        }, int2x2{}, int2x2{}) == int2x2(2,0,0,2));

        STATIC_CHECK(map_join([](const int2& x, const int2& y, const int2& z){
            return x + y + z;
        }, int2x2{}, int2x2{}, int2x2{}) == int2x2(3,0,0,3));

        STATIC_CHECK(fold_join([](int acc, const int2& x){
            return acc + x.x;
        }, 0, int2x2{}) == 1);

        STATIC_CHECK(fold_join([](int acc, const int2& x, const int2& y){
            return acc + x.x + y.x;
        }, 0, int2x2{}, int2x2{}) == 2);

        STATIC_CHECK(fold1_join([](const int2& acc, const int2& x){
            return acc + x;
        }, int2x2{}) == int2(1,1));
    }

    SUBCASE("operators") {
        STATIC_CHECK(+int2x2(1,-2,3,-4) == int2x2(1,-2,3,-4));
        STATIC_CHECK(-int2x2(1,-2,3,-4) == int2x2(-1,2,-3,4));
        STATIC_CHECK(~uint2x2(0xF0F0F0F0,0x0F0F0F0F,0xF0F0F0F0,0x0F0F0F0F) == uint2x2(0x0F0F0F0F,0xF0F0F0F0,0x0F0F0F0F,0xF0F0F0F0));
        STATIC_CHECK((!int2x2(-1,0,1,2)) == bool2x2(false,true,false,false));

        STATIC_CHECK(int2x2(1,2,3,4) + 2 == int2x2(3,4,5,6));
        STATIC_CHECK(int2x2(1,2,3,4) - 2 == int2x2(-1,0,1,2));
        STATIC_CHECK(int2x2(1,2,3,4) * 2 == int2x2(2,4,6,8));
        STATIC_CHECK(int2x2(1,2,3,4) / 2 == int2x2(0,1,1,2));
        STATIC_CHECK((int2x2(11,12,11,12) & 6) == int2x2(2,4,2,4));
        STATIC_CHECK((int2x2(11,12,11,12) | 6) == int2x2(15,14,15,14));
        STATIC_CHECK((int2x2(11,12,11,12) ^ 6) == int2x2(13,10,13,10));
        STATIC_CHECK((int2x2(1,0,1,0) && 1) == bool2x2(1,0,1,0));
        STATIC_CHECK((int2x2(1,0,1,0) || 1) == bool2x2(1,1,1,1));

        STATIC_CHECK(4 + int2x2(1,2,3,4) == int2x2(5,6,7,8));
        STATIC_CHECK(4 - int2x2(1,2,3,4) == int2x2(3,2,1,0));
        STATIC_CHECK(4 * int2x2(1,2,3,4) == int2x2(4,8,12,16));
        STATIC_CHECK(4 / int2x2(1,2,3,4) == int2x2(4,2,1,1));
        STATIC_CHECK((6 &int2x2(11,12,11,12)) == int2x2(2,4,2,4));
        STATIC_CHECK((6 |int2x2(11,12,11,12)) == int2x2(15,14,15,14));
        STATIC_CHECK((6 ^ int2x2(11,12,11,12)) == int2x2(13,10,13,10));
        STATIC_CHECK((1 && int2x2(1,0,1,0)) == bool2x2(1,0,1,0));
        STATIC_CHECK((1 || int2x2(1,0,1,0)) == bool2x2(1,1,1,1));

        STATIC_CHECK(int2x2(1,2,3,4) + int2x2(5,6,7,8) == int2x2(6,8,10,12));
        STATIC_CHECK(int2x2(1,2,3,4) - int2x2(5,6,7,8) == int2x2(-4,-4,-4,-4));

        STATIC_CHECK(int2x2() * int2x2() == int2x2());
        STATIC_CHECK(int3x3() * int3x3() == int3x3());

        STATIC_CHECK(int2(1,2) * int2x2() == int2(1,2));
        STATIC_CHECK(int3(1,2,3) * int3x3() == int3(1,2,3));
        STATIC_CHECK(int4(1,2,3,4) * int4x4() == int4(1,2,3,4));

        STATIC_CHECK((int2x2(6,7,6,7) & int2x2(11,12,11,12)) == int2x2(2,4,2,4));
        STATIC_CHECK((int2x2(6,7,6,7) | int2x2(11,12,11,12)) == int2x2(15,15,15,15));
        STATIC_CHECK((int2x2(6,7,6,7) ^ int2x2(11,12,11,12)) == int2x2(13,11,13,11));
        STATIC_CHECK((int2x2(0,1,0,1) && int2x2(1,0,1,0)) == bool2x2(0,0,0,0));
        STATIC_CHECK((int2x2(0,1,0,1) || int2x2(1,0,1,0)) == bool2x2(1,1,1,1));

        {
            int2x2 v{1,2,3,4};
            CHECK(&v == &(v += 3));
            CHECK(v == int2x2{4,5,6,7});
            CHECK(&v == &(v += int2x2{1,2,3,4}));
            CHECK(v == int2x2{5,7,9,11});
        }
        {
            int2x2 v{4,5,6,7};
            CHECK(&v == &(v -= 3));
            CHECK(v == int2x2{1,2,3,4});
            CHECK(&v == &(v -= int2x2{2,4,6,8}));
            CHECK(v == int2x2{-1,-2,-3,-4});
        }
        {
            int2x2 v{1,2,3,4};
            CHECK(&v == &(v *= 3));
            CHECK(v == int2x2{3,6,9,12});
        }
        {
            int4 v{0, 0, 0, 1};
            CHECK(&v == &(v *= translate(int3{1,2,3})));
            CHECK(v == uapprox4(1,2,3,1));
        }
        {
            int3 v{1, 2, 3};
            CHECK(&v == &(v *= int3x3(scale(int3{2,3,4}))));
            CHECK(v == int3(2,6,12));
        }
        {
            int4x4 v = translate(int3{1, 2, 3});
            CHECK(&v == &(v *= translate(int3{1,2,3})));
            CHECK(v == translate(int3{2,4,6}));
        }
        {
            int3x3 v = int3x3(scale(int3{1, 2, 3}));
            CHECK(&v == &(v *= int3x3(scale(int3{2,3,4}))));
            CHECK(v == int3x3(scale(int3{2,6,12})));
        }
        {
            int2x2 v1{11,12,11,12};
            CHECK(&v1 == &(v1 &= 6));
            CHECK(v1 == int2x2(2,4,2,4));
            int2x2 v2{6,7,6,7};
            CHECK(&v2 == &(v2 &= int2x2(11,12,11,12)));
            CHECK(v2 == int2x2(2,4,2,4));
        }
        {
            int2x2 v1{11,12,11,12};
            CHECK(&v1 == &(v1 |= 6));
            CHECK(v1 == int2x2(15,14,15,14));
            int2x2 v2{6,7,6,7};
            CHECK(&v2 == &(v2 |= int2x2(11,12,11,12)));
            CHECK(v2 == int2x2(15,15,15,15));
        }
        {
            int2x2 v1{11,12,11,12};
            CHECK(&v1 == &(v1 ^= 6));
            CHECK(v1 == int2x2(13,10,13,10));
            int2x2 v2{6,7,6,7};
            CHECK(&v2 == &(v2 ^= int2x2(11,12,11,12)));
            CHECK(v2 == int2x2(13,11,13,11));
        }
    }

    SUBCASE("relational functions") {
        STATIC_CHECK_FALSE(any(bool2x2(false, false, false, false)));
        STATIC_CHECK(any(bool2x2(true, false, true, false)));
        STATIC_CHECK(any(bool2x2(false, true, false, true)));
        STATIC_CHECK(any(bool2x2(true, true, true, true)));

        STATIC_CHECK_FALSE(any(int2x2(0, 0, 0, 0)));
        STATIC_CHECK(any(int2x2(1, 0, 1, 0)));
        STATIC_CHECK(any(int2x2(0, 1, 0, 1)));
        STATIC_CHECK(any(int2x2(1, 1, 1, 1)));

        STATIC_CHECK_FALSE(all(bool2x2(false, false, false, false)));
        STATIC_CHECK_FALSE(all(bool2x2(true, false, true, false)));
        STATIC_CHECK_FALSE(all(bool2x2(false, true, false, true)));
        STATIC_CHECK(all(bool2x2(true, true, true, true)));

        STATIC_CHECK_FALSE(all(int2x2(0, 0, 0, 0)));
        STATIC_CHECK_FALSE(all(int2x2(1, 0, 1, 0)));
        STATIC_CHECK_FALSE(all(int2x2(0, 1, 0, 1)));
        STATIC_CHECK(all(int2x2(1, 1, 1, 1)));

        STATIC_CHECK(approx(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(false, true, false, false));
        STATIC_CHECK(approx(int2x2(1,1,1,1), int2x2(0,1,2,3), 0) == bool2x2(false, true, false, false));
        STATIC_CHECK(approx(int2x2(1,1,1,1), int2x2(0,1,2,3), 1) == bool2x2(true, true, true, false));
        STATIC_CHECK(approx(int2x2(1,1,1,1), int2x2(0,1,2,3), 2) == bool2x2(true, true, true, true));

        STATIC_CHECK(less(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(false, false, true, true));
        STATIC_CHECK(less_equal(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(false, true, true, true));
        STATIC_CHECK(greater(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(true, false, false, false));
        STATIC_CHECK(greater_equal(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(true, true, false, false));

        STATIC_CHECK(equal_to(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(false, true, false, false));
        STATIC_CHECK(not_equal_to(int2x2(1,1,1,1), int2x2(0,1,2,3)) == bool2x2(true, false, true, true));
    }

    SUBCASE("transpose") {
        STATIC_CHECK(transpose(int2x2(
            1, 2,
            3, 4
        )) == int2x2(
            1, 3,
            2, 4
        ));

        STATIC_CHECK(transpose(int3x3(
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        )) == int3x3(
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
        ));

        STATIC_CHECK(transpose(int4x4(
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

    SUBCASE("determinant") {
        constexpr int2x2 m2{1,2,3,4};
        constexpr int3x3 m3{1,2,3,4,5,6,7,8,9};
        constexpr int4x4 m4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        STATIC_CHECK(determinant(m2) == determinant(transpose(m2)));
        STATIC_CHECK(determinant(m3) == determinant(transpose(m3)));
        STATIC_CHECK(determinant(m4) == determinant(transpose(m4)));

        STATIC_CHECK(determinant(generate_frank_matrix<int, 2>()) == 1);
        STATIC_CHECK(determinant(generate_frank_matrix<int, 3>()) == 1);
        STATIC_CHECK(determinant(generate_frank_matrix<int, 4>()) == 1);

        STATIC_CHECK(determinant(transpose(generate_frank_matrix<int, 2>())) == 1);
        STATIC_CHECK(determinant(transpose(generate_frank_matrix<int, 3>())) == 1);
        STATIC_CHECK(determinant(transpose(generate_frank_matrix<int, 4>())) == 1);
    }

    SUBCASE("inverse") {
        STATIC_CHECK(inverse(float2x2()) == float2x2());
        STATIC_CHECK(inverse(float3x3()) == float3x3());
        STATIC_CHECK(inverse(float4x4()) == float4x4());

        STATIC_CHECK(inverse(float2x2(0.5)) == float2x2(2.f));
        STATIC_CHECK(inverse(float3x3(0.5)) == float3x3(2.f));
        STATIC_CHECK(inverse(float4x4(0.5)) == float4x4(2.f));

        {
            constexpr float4x4 m1 = translate(float3(1.f, 2.f, 3.f));
            constexpr float4x4 rm1 = inverse(m1);
            STATIC_CHECK(all(approx(
                unit4_z<float> * m1 * rm1,
                unit4_z<float>)));
        }

        {
            const float3 axis2 = normalize(float3(1.f, 2.f, 3.f));
            const float4x4 m2 = rotate(0.5f,axis2);
            const float4x4 rm2 = inverse(m2);
            CHECK(all(approx(
                unit4_z<float> * m2 * rm2,
                unit4_z<float>)));
        }

        {
            const float3 axis3 = normalize(float3(1.f, 2.f, 3.f));
            const float3x3 m3 = float3x3(rotate(0.5f,axis3));
            const float3x3 rm3 = inverse(m3);
            CHECK(all(approx(
                unit3_z<float> * m3 * rm3,
                unit3_z<float>)));
        }

        {
            const float3 axis4 = normalize(float3(0.f, 0.f, 3.f));
            const float2x2 m4 = float2x2(rotate(0.5f,axis4));
            const float2x2 rm4 = inverse(m4);
            CHECK(all(approx(
                unit2_y<float> * m4 * rm4,
                unit2_y<float>)));
        }
    }
}
