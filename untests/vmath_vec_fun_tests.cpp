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
}

TEST_CASE("vmath/vec_fun") {
    SUBCASE("Detail") {
        STATIC_CHECK(map_join([](const int& x){
            return x * 2;
        }, vec{1,2,3,4}) == vec{2,4,6,8});

        STATIC_CHECK(map_join([](const int& x, const int& y){
            return x + y;
        }, vec{1,2,3,4}, vec{2,3,4,5}) == vec{3,5,7,9});

        STATIC_CHECK(map_join([](const int& x, const int& y, const int& z){
            return x + y + z;
        }, vec{1,2,3,4}, vec{2,3,4,5}, vec{3,4,5,6}) == vec{6,9,12,15});

        STATIC_CHECK(map_join([](const int& x, const int& y, const int& z, const int& w){
            return x + y + z + w;
        }, vec{1,2,3,4}, vec{2,3,4,5}, vec{3,4,5,6}, vec{4,5,6,7}) == vec{10,14,18,22});

        STATIC_CHECK(fold_join([](int acc, const int& x){
            return acc - x;
        }, 0, vec{1,2,3,4}) == -10);

        STATIC_CHECK(fold_join([](int acc, const int& x, const int& y){
            return acc - x - y;
        }, 0, vec{1,2,3,4}, vec{2,3,4,5}) == -24);

        STATIC_CHECK(fold1_join([](const int& acc, const int& x){
            return acc - x;
        }, vec{1,2,3,4}) == -8);
    }

    SUBCASE("Operators") {
        STATIC_CHECK(+int2(1,-2) == int2(1,-2));
        STATIC_CHECK(-int2(1,-2) == int2(-1,2));
        STATIC_CHECK(~uint2(0xF0F0F0F0,0x0F0F0F0F) == uint2(0x0F0F0F0F,0xF0F0F0F0));
        STATIC_CHECK((!int3(-1,0,1)) == bool3(false, true, false));

        STATIC_CHECK(int2(1,2) + 3 == int2(4,5));
        STATIC_CHECK(int2(1,2) - 3 == int2(-2,-1));
        STATIC_CHECK(int2(1,2) * 3 == int2(3,6));
        STATIC_CHECK(int2(2,4) / 2 == int2(1,2));
        STATIC_CHECK((int2(11,12) & 6) == int2(2,4));
        STATIC_CHECK((int2(11,12) | 6) == int2(15,14));
        STATIC_CHECK((int2(11,12) ^ 6) == int2(13,10));
        STATIC_CHECK((int2(1,0) && 1) == bool2(1,0));
        STATIC_CHECK((int2(1,0) || 1) == bool2(1,1));

        STATIC_CHECK(3 + int2(1,2) == int2(4,5));
        STATIC_CHECK(3 - int2(1,2) == int2(2,1));
        STATIC_CHECK(3 * int2(1,2) == int2(3,6));
        STATIC_CHECK(4 / int2(2,4) == int2(2,1));
        STATIC_CHECK((6 & int2(11,12)) == int2(2,4));
        STATIC_CHECK((6 | int2(11,12)) == int2(15,14));
        STATIC_CHECK((6 ^ int2(11,12)) == int2(13,10));
        STATIC_CHECK((1 && int2(1,0)) == bool2(1,0));
        STATIC_CHECK((1 || int2(1,0)) == bool2(1,1));

        STATIC_CHECK(int2(1,2) + int2(3,4) == int2(4,6));
        STATIC_CHECK(int2(1,2) - int2(3,4) == int2(-2,-2));
        STATIC_CHECK(int2(1,2) * int2(3,4) == int2(3,8));
        STATIC_CHECK(int2(3,4) / int2(1,2) == int2(3,2));
        STATIC_CHECK((int2(6,7) & int2(11,12)) == int2(2,4));
        STATIC_CHECK((int2(6,7) | int2(11,12)) == int2(15,15));
        STATIC_CHECK((int2(6,7) ^ int2(11,12)) == int2(13,11));
        STATIC_CHECK((int2(0,1) && int2(1,0)) == bool2(0,0));
        STATIC_CHECK((int2(0,1) || int2(1,0)) == bool2(1,1));

        {
            int2 v{1,2};
            CHECK(&v == &(v += 3));
            CHECK(v == int2{4,5});
            CHECK(&v == &(v += int2{1,2}));
            CHECK(v == int2{5,7});
        }
        {
            int2 v{4,5};
            CHECK(&v == &(v -= 3));
            CHECK(v == int2{1,2});
            CHECK(&v == &(v -= int2{2,4}));
            CHECK(v == int2{-1,-2});
        }
        {
            int2 v{1,2};
            CHECK(&v == &(v *= 3));
            CHECK(v == int2{3,6});
            CHECK(&v == &(v *= int2{2,3}));
            CHECK(v == int2{6,18});
        }
        {
            int2 v{6,18};
            CHECK(&v == &(v /= 2));
            CHECK(v == int2{3,9});
            CHECK(&v == &(v /= int2{3,4}));
            CHECK(v == int2{1,2});
        }
        {
            int2 v1{11,12};
            CHECK(&v1 == &(v1 &= 6));
            CHECK(v1 == int2(2,4));
            int2 v2{6,7};
            CHECK(&v2 == &(v2 &= int2(11,12)));
            CHECK(v2 == int2(2,4));
        }
        {
            int2 v1{11,12};
            CHECK(&v1 == &(v1 |= 6));
            CHECK(v1 == int2(15,14));
            int2 v2{6,7};
            CHECK(&v2 == &(v2 |= int2(11,12)));
            CHECK(v2 == int2(15,15));
        }
        {
            int2 v1{11,12};
            CHECK(&v1 == &(v1 ^= 6));
            CHECK(v1 == int2(13,10));
            int2 v2{6,7};
            CHECK(&v2 == &(v2 ^= int2(11,12)));
            CHECK(v2 == int2(13,11));
        }
    }

    SUBCASE("Angle and Trigonometric Functions") {
        STATIC_CHECK(radians(degrees(float2(12.13f))) == uapprox2(12.13f));
        STATIC_CHECK(degrees(radians(float2(12.13f))) == uapprox2(12.13f));

        (void)sin(float2(1.f));
        (void)cos(float2(1.f));
        (void)tan(float2(1.f));

        (void)asin(float2(1.f));
        (void)acos(float2(1.f));
        (void)atan(float2(1.f));
        (void)atan2(float2(1.f), float2(1.f));

        (void)sinh(float2(1.f));
        (void)cosh(float2(1.f));
        (void)tanh(float2(1.f));

        (void)asinh(float2(1.f));
        (void)acosh(float2(1.f));
        (void)atanh(float2(1.f));

        {
            float2 out_ss{}, out_cs{};
            sincos(float2(10.f,15.f), &out_ss, &out_cs);
            CHECK(out_ss == uapprox2(sin(10.f), sin(15.f)));
            CHECK(out_cs == uapprox2(cos(10.f), cos(15.f)));
            const auto [out_ss2, out_cs2] = sincos(float2(10.f,15.f));
            CHECK(out_ss2 == uapprox2(sin(10.f), sin(15.f)));
            CHECK(out_cs2 == uapprox2(cos(10.f), cos(15.f)));
        }
    }

    SUBCASE("Exponential Functions") {
        (void)pow(float2(1.f), float2(2.f));
        (void)exp(float2(1.f));
        (void)log(float2(1.f));
        (void)exp2(float2(1.f));
        (void)log2(float2(1.f));
        (void)sqrt(float2(1.f));
        (void)rsqrt(float2(1.f));
    }

    SUBCASE("Common Functions") {
        STATIC_CHECK(abs(float2(1.f, -1.f)) == uapprox2(1.f,1.f));
        STATIC_CHECK(sqr(float2(2.f, -3.f)) == uapprox2(4.f,9.f));
        STATIC_CHECK(sign(float3(1.f, -1.f, 0.f)) == uapprox3(1.f,-1.f,0.f));
        STATIC_CHECK(rcp(float2(2.f, 4.f)) == uapprox2(0.5f,0.25f));

        CHECK(copysign(
            float4(2.f, -4.f, 2.f, -4.f),
            5.f)
        == uapprox4(2.f, 4.f, 2.f, 4.f));

        CHECK(copysign(
            float4(2.f, -4.f, 2.f, -4.f),
            -5.f)
        == uapprox4(-2.f, -4.f, -2.f, -4.f));

        CHECK(copysign(
            float4(2.f, -4.f, 2.f, -4.f),
            float4(10.f, 5.f, -4.f, -0.4f))
        == uapprox4(2.f, 4.f, -2.f, -4.f));

        (void)floor(float2(1.f, -1.f));
        (void)trunc(float2(1.f, -1.f));
        (void)round(float2(1.f, -1.f));
        (void)ceil(float2(1.f, -1.f));
        (void)fract(float2(1.f, -1.f));

        CHECK(fmod(float2(1.7f), 1.2f) == uapprox2(0.5f));
        CHECK(fmod(float2(1.7f), float2(1.2f)) == uapprox2(0.5f));

        {
            float2 out_i{};
            CHECK(modf(float2(1.7f), &out_i) == uapprox2(0.7f));
            CHECK(out_i.x == uapprox(1.f));
        }

        STATIC_CHECK(min(int2(1,2)) == 1);
        STATIC_CHECK(min(int2(1,2), 1) == int2(1,1));
        STATIC_CHECK(min(1, int2(1,2)) == int2(1,1));
        STATIC_CHECK(min(int2(1,1), int2(0,2)) == int2(0,1));

        STATIC_CHECK(max(int2(1,2)) == 2);
        STATIC_CHECK(max(int2(1,2), 1) == int2(1,2));
        STATIC_CHECK(max(1, int2(1,2)) == int2(1,2));
        STATIC_CHECK(max(int2(1,1), int2(0,2)) == int2(1,2));

        STATIC_CHECK(clamp(int2(1,2), 0, 1) == int2(1,1));
        STATIC_CHECK(clamp(int2(1,2), int2(0), int2(1)) == int2(1,1));

        STATIC_CHECK(saturate(float3(-1.f,0.5,1.5f)) == uapprox3(0.f,0.5f,1.f));

        STATIC_CHECK(lerp(float2(2.f), float2(10.f), 0.f) == uapprox2(2.f));
        STATIC_CHECK(lerp(float2(2.f), float2(10.f), 0.5f) == uapprox2(6.f));
        STATIC_CHECK(lerp(float2(2.f), float2(10.f), 1.f) == uapprox2(10.f));

        STATIC_CHECK(lerp(float2(2.f), float2(10.f), 0.f, 1.f) == uapprox2(10.f));
        STATIC_CHECK(lerp(float2(2.f), float2(10.f), 1.f, 0.f) == uapprox2(2.f));
        STATIC_CHECK(lerp(float2(2.f), float2(10.f), 0.5f, 0.2f) == uapprox2(3.f));

        STATIC_CHECK(lerp(float2(2.f), float2(10.f), float2(0.f)) == uapprox2(2.f));
        STATIC_CHECK(lerp(float2(2.f), float2(10.f), float2(0.5f)) == uapprox2(6.f));
        STATIC_CHECK(lerp(float2(2.f), float2(10.f), float2(1.f)) == uapprox2(10.f));

        STATIC_CHECK(lerp(float2(2.f), float2(10.f), float2(0.f), float2(1.f)) == uapprox2(10.f));
        STATIC_CHECK(lerp(float2(2.f), float2(10.f), float2(1.f), float2(0.f)) == uapprox2(2.f));
        STATIC_CHECK(lerp(float2(2.f), float2(10.f), float2(0.5f), float2(0.2f)) == uapprox2(3.f));

        STATIC_CHECK(step(0.5f, float2(0.4f)) == uapprox2(0.f));
        STATIC_CHECK(step(0.5f, float2(0.6f)) == uapprox2(1.f));
        STATIC_CHECK(step(float2(0.5f), float2(0.4f)) == uapprox2(0.f));
        STATIC_CHECK(step(float2(0.5f), float2(0.6f)) == uapprox2(1.f));

        STATIC_CHECK(smoothstep(0.f, 1.f, float2(0.1f)) == uapprox2(0.028f));
        STATIC_CHECK(smoothstep(float2(0.f), float2(1.f), float2(0.1f)) == uapprox2(0.028f));

        CHECK_FALSE(fma(float2(2.f), float2(3.f), float2(4.f)).x == uapprox(12.f));
    }

    SUBCASE("Geometric Functions") {
        CHECK(length(float2(10.f,0.f)) == uapprox(10.f));
        CHECK(length(float2(-10.f,0.f)) == uapprox(10.f));

        CHECK(rlength(float2(10.f,0.f)) == uapprox(0.1f));
        CHECK(rlength(float2(-10.f,0.f)) == uapprox(0.1f));

        STATIC_CHECK(length2(float2(10.f,0.f)) == uapprox(100.f));
        STATIC_CHECK(length2(float2(-10.f,0.f)) == uapprox(100.f));

        STATIC_CHECK(rlength2(float2(10.f,0.f)) == uapprox(0.01f));
        STATIC_CHECK(rlength2(float2(-10.f,0.f)) == uapprox(0.01f));

        CHECK(distance(float2(5.f,0.f), float2(10.f,0.f)) == uapprox(5.f));
        CHECK(distance(float2(-5.f,0.f), float2(-10.f,0.f)) == uapprox(5.f));

        STATIC_CHECK(distance2(float2(5.f,0.f), float2(10.f,0.f)) == uapprox(25.f));
        STATIC_CHECK(distance2(float2(-5.f,0.f), float2(-10.f,0.f)) == uapprox(25.f));

        STATIC_CHECK(dot(int2(1,2),int2(3,4)) == 11);
        STATIC_CHECK(cross(int2(1,0),int2(0,1)) == 1);
        STATIC_CHECK(cross(int3(1,0,0),int3(0,1,0)) == int3(0,0,1));
        CHECK(normalize(float2(0.5f,0.f)).x == uapprox(1.f));

        STATIC_CHECK(faceforward(float2(1.f), float2(2.f), float2(3.f)).x == uapprox(-1.f));
        STATIC_CHECK(reflect(float2(1.f), float2(2.f)).x == uapprox(-15.f));
        CHECK(refract(float2(1.f), float2(2.f), 1.f).x == uapprox(-15.f));
    }

    SUBCASE("Relational Functions") {
        STATIC_CHECK_FALSE(any(bool2(false, false)));
        STATIC_CHECK(any(bool2(true, false)));
        STATIC_CHECK(any(bool2(false, true)));
        STATIC_CHECK(any(bool2(true, true)));

        STATIC_CHECK_FALSE(any(int2(0, 0)));
        STATIC_CHECK(any(int2(1, 0)));
        STATIC_CHECK(any(int2(0, 1)));
        STATIC_CHECK(any(int2(1, 1)));

        STATIC_CHECK_FALSE(all(bool2(false, false)));
        STATIC_CHECK_FALSE(all(bool2(true, false)));
        STATIC_CHECK_FALSE(all(bool2(false, true)));
        STATIC_CHECK(all(bool2(true, true)));

        STATIC_CHECK_FALSE(all(int2(0, 0)));
        STATIC_CHECK_FALSE(all(int2(1, 0)));
        STATIC_CHECK_FALSE(all(int2(0, 1)));
        STATIC_CHECK(all(int2(1, 1)));

        STATIC_CHECK(approx(int3(1,1,1), int3(0,1,2)) == bool3(false, true, false));
        STATIC_CHECK(approx(int4(1,1,1,1), int4(0,1,2,3), 0) == bool4(false, true, false, false));
        STATIC_CHECK(approx(int4(1,1,1,1), int4(0,1,2,3), 1) == bool4(true, true, true, false));
        STATIC_CHECK(approx(int4(1,1,1,1), int4(0,1,2,3), 2) == bool4(true, true, true, true));

        STATIC_CHECK(less(int3(1,1,1), int3(0,1,2)) == bool3(false, false, true));
        STATIC_CHECK(less_equal(int3(1,1,1), int3(0,1,2)) == bool3(false, true, true));
        STATIC_CHECK(greater(int3(1,1,1), int3(0,1,2)) == bool3(true, false, false));
        STATIC_CHECK(greater_equal(int3(1,1,1), int3(0,1,2)) == bool3(true, true, false));

        STATIC_CHECK(equal_to(int3(1,1,1), int3(0,1,2)) == bool3(false, true, false));
        STATIC_CHECK(not_equal_to(int3(1,1,1), int3(0,1,2)) == bool3(true, false, true));
    }
}
