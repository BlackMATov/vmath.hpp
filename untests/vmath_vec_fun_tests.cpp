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
}

TEST_CASE("vmath/vec_fun") {
    SECTION("Detail") {
        STATIC_REQUIRE(map_join([](const int& x){
            return x * 2;
        }, int2{1}) == int2{2});

        STATIC_REQUIRE(map_join([](const int& x, const int& y){
            return x + y;
        }, int2{1}, int2{1}) == int2{2});

        STATIC_REQUIRE(map_join([](const int& x, const int& y, const int& z){
            return x + y + z;
        }, int2{1}, int2{1}, int2{1}) == int2(3));

        STATIC_REQUIRE(fold_join([](int acc, const int& x){
            return acc + x;
        }, 0, int2{1}) == 2);

        STATIC_REQUIRE(fold_join([](int acc, const int& x, const int& y){
            return acc + x + y;
        }, 0, int2{1}, int2{1}) == 4);

        STATIC_REQUIRE(fold1_join([](const int& acc, const int& x){
            return acc + x;
        }, int2{1}) == 2);
    }

    SECTION("Operators") {
        STATIC_REQUIRE(+int2(1,-2) == int2(1,-2));
        STATIC_REQUIRE(-int2(1,-2) == int2(-1,2));
        STATIC_REQUIRE(~uint2(0xF0F0F0F0,0x0F0F0F0F) == uint2(0x0F0F0F0F,0xF0F0F0F0));
        STATIC_REQUIRE(!int3(-1,0,1) == bool3(false, true, false));

        STATIC_REQUIRE(int2(1,2) + 3 == int2(4,5));
        STATIC_REQUIRE(int2(1,2) - 3 == int2(-2,-1));
        STATIC_REQUIRE(int2(1,2) * 3 == int2(3,6));
        STATIC_REQUIRE(int2(2,4) / 2 == int2(1,2));
        STATIC_REQUIRE((int2(11,12) & 6) == int2(2,4));
        STATIC_REQUIRE((int2(11,12) | 6) == int2(15,14));
        STATIC_REQUIRE((int2(11,12) ^ 6) == int2(13,10));
        STATIC_REQUIRE((int2(1,0) && 1) == bool2(1,0));
        STATIC_REQUIRE((int2(1,0) || 1) == bool2(1,1));

        STATIC_REQUIRE(3 + int2(1,2) == int2(4,5));
        STATIC_REQUIRE(3 - int2(1,2) == int2(2,1));
        STATIC_REQUIRE(3 * int2(1,2) == int2(3,6));
        STATIC_REQUIRE(4 / int2(2,4) == int2(2,1));
        STATIC_REQUIRE((6 & int2(11,12)) == int2(2,4));
        STATIC_REQUIRE((6 | int2(11,12)) == int2(15,14));
        STATIC_REQUIRE((6 ^ int2(11,12)) == int2(13,10));
        STATIC_REQUIRE((1 && int2(1,0)) == bool2(1,0));
        STATIC_REQUIRE((1 || int2(1,0)) == bool2(1,1));

        STATIC_REQUIRE(int2(1,2) + int2(3,4) == int2(4,6));
        STATIC_REQUIRE(int2(1,2) - int2(3,4) == int2(-2,-2));
        STATIC_REQUIRE(int2(1,2) * int2(3,4) == int2(3,8));
        STATIC_REQUIRE(int2(3,4) / int2(1,2) == int2(3,2));
        STATIC_REQUIRE((int2(6,7) & int2(11,12)) == int2(2,4));
        STATIC_REQUIRE((int2(6,7) | int2(11,12)) == int2(15,15));
        STATIC_REQUIRE((int2(6,7) ^ int2(11,12)) == int2(13,11));
        STATIC_REQUIRE((int2(0,1) && int2(1,0)) == bool2(0,0));
        STATIC_REQUIRE((int2(0,1) || int2(1,0)) == bool2(1,1));

        {
            int2 v{1,2};
            REQUIRE(&v == &(v += 3));
            REQUIRE(v == int2{4,5});
            REQUIRE(&v == &(v += int2{1,2}));
            REQUIRE(v == int2{5,7});
        }
        {
            int2 v{4,5};
            REQUIRE(&v == &(v -= 3));
            REQUIRE(v == int2{1,2});
            REQUIRE(&v == &(v -= int2{2,4}));
            REQUIRE(v == int2{-1,-2});
        }
        {
            int2 v{1,2};
            REQUIRE(&v == &(v *= 3));
            REQUIRE(v == int2{3,6});
            REQUIRE(&v == &(v *= int2{2,3}));
            REQUIRE(v == int2{6,18});
        }
        {
            int2 v{6,18};
            REQUIRE(&v == &(v /= 2));
            REQUIRE(v == int2{3,9});
            REQUIRE(&v == &(v /= int2{3,4}));
            REQUIRE(v == int2{1,2});
        }
        {
            int2 v1{11,12};
            REQUIRE(&v1 == &(v1 &= 6));
            REQUIRE(v1 == int2(2,4));
            int2 v2{6,7};
            REQUIRE(&v2 == &(v2 &= int2(11,12)));
            REQUIRE(v2 == int2(2,4));
        }
        {
            int2 v1{11,12};
            REQUIRE(&v1 == &(v1 |= 6));
            REQUIRE(v1 == int2(15,14));
            int2 v2{6,7};
            REQUIRE(&v2 == &(v2 |= int2(11,12)));
            REQUIRE(v2 == int2(15,15));
        }
        {
            int2 v1{11,12};
            REQUIRE(&v1 == &(v1 ^= 6));
            REQUIRE(v1 == int2(13,10));
            int2 v2{6,7};
            REQUIRE(&v2 == &(v2 ^= int2(11,12)));
            REQUIRE(v2 == int2(13,11));
        }
    }

    SECTION("Angle and Trigonometric Functions") {
        STATIC_REQUIRE(radians(degrees(float2(12.13f))) == uapprox2(12.13f));
        STATIC_REQUIRE(degrees(radians(float2(12.13f))) == uapprox2(12.13f));

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
            REQUIRE(out_ss == uapprox2(sin(10.f), sin(15.f)));
            REQUIRE(out_cs == uapprox2(cos(10.f), cos(15.f)));
        }
    }

    SECTION("Exponential Functions") {
        (void)pow(float2(1.f), float2(2.f));
        (void)exp(float2(1.f));
        (void)log(float2(1.f));
        (void)exp2(float2(1.f));
        (void)log2(float2(1.f));
        (void)sqrt(float2(1.f));
        (void)rsqrt(float2(1.f));
    }

    SECTION("Common Functions") {
        STATIC_REQUIRE(abs(float2(1.f, -1.f)) == uapprox2(1.f,1.f));
        STATIC_REQUIRE(sign(float3(1.f, -1.f, 0.f)) == uapprox3(1.f,-1.f,0.f));
        STATIC_REQUIRE(rcp(float2(2.f, 4.f)) == uapprox2(0.5f,0.25f));

        (void)floor(float2(1.f, -1.f));
        (void)trunc(float2(1.f, -1.f));
        (void)round(float2(1.f, -1.f));
        (void)ceil(float2(1.f, -1.f));
        (void)fract(float2(1.f, -1.f));

        REQUIRE(fmod(float2(1.7f), 1.2f) == uapprox2(0.5f));
        REQUIRE(fmod(float2(1.7f), float2(1.2f)) == uapprox2(0.5f));

        {
            float2 out_i{};
            REQUIRE(modf(float2(1.7f), &out_i) == uapprox2(0.7f));
            REQUIRE(out_i.x == uapprox(1.f));
        }

        STATIC_REQUIRE(min(int2(1,2)) == 1);
        STATIC_REQUIRE(min(int2(1,2), 1) == int2(1,1));
        STATIC_REQUIRE(min(int2(1,1), int2(0,2)) == int2(0,1));

        STATIC_REQUIRE(max(int2(1,2)) == 2);
        STATIC_REQUIRE(max(int2(1,2), 1) == int2(1,2));
        STATIC_REQUIRE(max(int2(1,1), int2(0,2)) == int2(1,2));

        STATIC_REQUIRE(clamp(int2(1,2), 0, 1) == int2(1,1));
        STATIC_REQUIRE(clamp(int2(1,2), int2(0), int2(1)) == int2(1,1));

        STATIC_REQUIRE(saturate(float3(-1.f,0.5,1.5f)) == uapprox3(0.f,0.5f,1.f));

        STATIC_REQUIRE(lerp(float2(2.f), float2(10.f), 0.f) == uapprox2(2.f));
        STATIC_REQUIRE(lerp(float2(2.f), float2(10.f), 0.5f) == uapprox2(6.f));
        STATIC_REQUIRE(lerp(float2(2.f), float2(10.f), 1.f) == uapprox2(10.f));

        STATIC_REQUIRE(lerp(float2(2.f), float2(10.f), float2(0.f)) == uapprox2(2.f));
        STATIC_REQUIRE(lerp(float2(2.f), float2(10.f), float2(0.5f)) == uapprox2(6.f));
        STATIC_REQUIRE(lerp(float2(2.f), float2(10.f), float2(1.f)) == uapprox2(10.f));

        STATIC_REQUIRE(step(0.5f, float2(0.4f)) == uapprox2(0.f));
        STATIC_REQUIRE(step(0.5f, float2(0.6f)) == uapprox2(1.f));
        STATIC_REQUIRE(step(float2(0.5f), float2(0.4f)) == uapprox2(0.f));
        STATIC_REQUIRE(step(float2(0.5f), float2(0.6f)) == uapprox2(1.f));

        STATIC_REQUIRE(smoothstep(0.f, 1.f, float2(0.1f)) == uapprox2(0.028f));
        STATIC_REQUIRE(smoothstep(float2(0.f), float2(1.f), float2(0.1f)) == uapprox2(0.028f));

        REQUIRE_FALSE(isnan(float2(1.f)).x);
        REQUIRE_FALSE(isinf(float2(1.f)).x);
        REQUIRE(isfinite(float2(1.f)).x);

        REQUIRE_FALSE(fma(float2(2.f), float2(3.f), float2(4.f)).x == uapprox(12.f));

        {
            int2 out_exp{};
            REQUIRE(frexp(float2(1.7f), &out_exp).x == uapprox(0.85f));
            REQUIRE(out_exp == int2(1));
        }

        REQUIRE(ldexp(float2(0.85f), int2(1)).x == uapprox(1.7f));
    }

    SECTION("Geometric Functions") {
        REQUIRE(length(float2(10.f,0.f)) == uapprox(10.f));
        REQUIRE(length(float2(-10.f,0.f)) == uapprox(10.f));

        STATIC_REQUIRE(length2(float2(10.f,0.f)) == uapprox(100.f));
        STATIC_REQUIRE(length2(float2(-10.f,0.f)) == uapprox(100.f));

        REQUIRE(distance(float2(5.f,0.f), float2(10.f,0.f)) == uapprox(5.f));
        REQUIRE(distance(float2(-5.f,0.f), float2(-10.f,0.f)) == uapprox(5.f));

        STATIC_REQUIRE(distance2(float2(5.f,0.f), float2(10.f,0.f)) == uapprox(25.f));
        STATIC_REQUIRE(distance2(float2(-5.f,0.f), float2(-10.f,0.f)) == uapprox(25.f));

        STATIC_REQUIRE(dot(int2(1,2),int2(3,4)) == 11);
        STATIC_REQUIRE(cross(int2(1,0),int2(0,1)) == 1);
        STATIC_REQUIRE(cross(int3(1,0,0),int3(0,1,0)) == int3(0,0,1));
        REQUIRE(normalize(float2(0.5f,0.f)).x == uapprox(1.f));

        STATIC_REQUIRE(faceforward(float2(1.f), float2(2.f), float2(3.f)).x == uapprox(-1.f));
        STATIC_REQUIRE(reflect(float2(1.f), float2(2.f)).x == uapprox(-15.f));
        REQUIRE(refract(float2(1.f), float2(2.f), 1.f).x == uapprox(-15.f));
    }

    SECTION("Relational Functions") {
        STATIC_REQUIRE_FALSE(any(bool2(false, false)));
        STATIC_REQUIRE(any(bool2(true, false)));
        STATIC_REQUIRE(any(bool2(false, true)));
        STATIC_REQUIRE(any(bool2(true, true)));

        STATIC_REQUIRE_FALSE(any(int2(0, 0)));
        STATIC_REQUIRE(any(int2(1, 0)));
        STATIC_REQUIRE(any(int2(0, 1)));
        STATIC_REQUIRE(any(int2(1, 1)));

        STATIC_REQUIRE_FALSE(all(bool2(false, false)));
        STATIC_REQUIRE_FALSE(all(bool2(true, false)));
        STATIC_REQUIRE_FALSE(all(bool2(false, true)));
        STATIC_REQUIRE(all(bool2(true, true)));

        STATIC_REQUIRE_FALSE(all(int2(0, 0)));
        STATIC_REQUIRE_FALSE(all(int2(1, 0)));
        STATIC_REQUIRE_FALSE(all(int2(0, 1)));
        STATIC_REQUIRE(all(int2(1, 1)));

        STATIC_REQUIRE(approx(int3(1,1,1), int3(0,1,2)) == bool3(false, true, false));
        STATIC_REQUIRE(approx(int4(1,1,1,1), int4(0,1,2,3), 0) == bool4(false, true, false, false));
        STATIC_REQUIRE(approx(int4(1,1,1,1), int4(0,1,2,3), 1) == bool4(true, true, true, false));
        STATIC_REQUIRE(approx(int4(1,1,1,1), int4(0,1,2,3), 2) == bool4(true, true, true, true));

        STATIC_REQUIRE(less(int3(1,1,1), int3(0,1,2)) == bool3(false, false, true));
        STATIC_REQUIRE(less_equal(int3(1,1,1), int3(0,1,2)) == bool3(false, true, true));
        STATIC_REQUIRE(greater(int3(1,1,1), int3(0,1,2)) == bool3(true, false, false));
        STATIC_REQUIRE(greater_equal(int3(1,1,1), int3(0,1,2)) == bool3(true, true, false));

        STATIC_REQUIRE(equal_to(int3(1,1,1), int3(0,1,2)) == bool3(false, true, false));
        STATIC_REQUIRE(not_equal_to(int3(1,1,1), int3(0,1,2)) == bool3(true, false, true));
    }
}
