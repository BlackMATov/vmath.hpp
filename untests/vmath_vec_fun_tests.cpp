/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"
#include "doctest/doctest.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/vec_fun") {
    SUBCASE("Detail") {
        STATIC_REQUIRE(map([](const int& x){
            return x * 2;
        }, int2{1}) == int2{2});

        STATIC_REQUIRE(zip([](const int& x, const int& y){
            return x + y;
        }, int2{1}, int2{1}) == int2{2});

        STATIC_REQUIRE(zip([](const int& x, const int& y, const int& z){
            return x + y + z;
        }, int2{1}, int2{1}, int2{1}) == int2(3));

        STATIC_REQUIRE(fold([](int acc, const int& x){
            return acc + x;
        }, 0, int2{1}) == 2);

        STATIC_REQUIRE(fold([](int acc, const int& x, const int& y){
            return acc + x + y;
        }, 0, int2{1}, int2{1}) == 4);

        STATIC_REQUIRE(fold1([](const int& acc, const int& x){
            return acc + x;
        }, int2{1}) == 2);
    }

    SUBCASE("Operators") {
        STATIC_REQUIRE(-int2(1,-2) == int2(-1,2));

        STATIC_REQUIRE(int2(1,2) + 3 == int2(4,5));
        STATIC_REQUIRE(int2(1,2) - 3 == int2(-2,-1));
        STATIC_REQUIRE(int2(1,2) * 3 == int2(3,6));
        STATIC_REQUIRE(int2(2,4) / 2 == int2(1,2));

        STATIC_REQUIRE(3 + int2(1,2) == int2(4,5));
        STATIC_REQUIRE(3 - int2(1,2) == int2(2,1));
        STATIC_REQUIRE(3 * int2(1,2) == int2(3,6));
        STATIC_REQUIRE(4 / int2(2,4) == int2(2,1));

        STATIC_REQUIRE(int2(1,2) + int2(3,4) == int2(4,6));
        STATIC_REQUIRE(int2(1,2) - int2(3,4) == int2(-2,-2));
        STATIC_REQUIRE(int2(1,2) * int2(3,4) == int2(3,8));
        STATIC_REQUIRE(int2(3,4) / int2(1,2) == int2(3,2));

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
    }

    SUBCASE("Angle and Trigonometry Functions") {
        STATIC_REQUIRE(radians(degrees(float2(12.13f))) == approx2(12.13f));
        STATIC_REQUIRE(degrees(radians(float2(12.13f))) == approx2(12.13f));

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
        STATIC_REQUIRE(abs(float2(1.f, -1.f)) == approx2(1.f,1.f));
        STATIC_REQUIRE(sign(float3(1.f, -1.f, 0.f)) == approx3(1.f,-1.f,0.f));
        STATIC_REQUIRE(reciprocal(float2(2.f, 4.f)) == approx2(0.5f,0.25f));

        (void)floor(float2(1.f, -1.f));
        (void)trunc(float2(1.f, -1.f));
        (void)round(float2(1.f, -1.f));
        (void)ceil(float2(1.f, -1.f));
        (void)fract(float2(1.f, -1.f));

        REQUIRE(fmod(float2(1.7f), 1.2f) == approx2(0.5f));
        REQUIRE(fmod(float2(1.7f), float2(1.2f)) == approx2(0.5f));

        {
            float2 out_i{};
            REQUIRE(modf(float2(1.7f), &out_i) == approx2(0.7f));
            REQUIRE(out_i.x == approx(1.f));
        }

        STATIC_REQUIRE(min(int2(1,2)) == 1);
        STATIC_REQUIRE(min(int2(1,2), 1) == int2(1,1));
        STATIC_REQUIRE(min(int2(1,1), int2(0,2)) == int2(0,1));

        STATIC_REQUIRE(max(int2(1,2)) == 2);
        STATIC_REQUIRE(max(int2(1,2), 1) == int2(1,2));
        STATIC_REQUIRE(max(int2(1,1), int2(0,2)) == int2(1,2));

        STATIC_REQUIRE(clamp(int2(1,2), 0, 1) == int2(1,1));
        STATIC_REQUIRE(clamp(int2(1,2), int2(0), int2(1)) == int2(1,1));

        STATIC_REQUIRE(saturate(float3(-1.f,0.5,1.5f)) == approx3(0.f,0.5f,1.f));

        STATIC_REQUIRE(lerp(float2(0.f), float2(10.f), 0.5f) == approx2(5.f));
        STATIC_REQUIRE(lerp(float2(0.f), float2(10.f), float2(0.5f)) == approx2(5.f));

        STATIC_REQUIRE(step(0.5f, float2(0.4f)) == approx2(0.f));
        STATIC_REQUIRE(step(0.5f, float2(0.6f)) == approx2(1.f));
        STATIC_REQUIRE(step(float2(0.5f), float2(0.4f)) == approx2(0.f));
        STATIC_REQUIRE(step(float2(0.5f), float2(0.6f)) == approx2(1.f));

        STATIC_REQUIRE(smoothstep(0.f, 1.f, float2(0.1f)) == approx2(0.028f));
        STATIC_REQUIRE(smoothstep(float2(0.f), float2(1.f), float2(0.1f)) == approx2(0.028f));

        REQUIRE_FALSE(isnan(float2(1.f)).x);
        REQUIRE_FALSE(isinf(float2(1.f)).x);
        REQUIRE(isfinite(float2(1.f)).x);

        REQUIRE_FALSE(fma(float2(2.f), float2(3.f), float2(4.f)).x == approx(12.f));

        {
            int2 out_exp{};
            REQUIRE(frexp(float2(1.7f), &out_exp).x == approx(0.85f));
            REQUIRE(out_exp == int2(1));
        }

        REQUIRE(ldexp(float2(0.85f), int2(1)).x == approx(1.7f));
    }

    SUBCASE("Geometric Functions") {
        REQUIRE(length(float2(10.f,0.f)) == approx(10.f));
        REQUIRE(length(float2(-10.f,0.f)) == approx(10.f));

        STATIC_REQUIRE(length2(float2(10.f,0.f)) == approx(100.f));
        STATIC_REQUIRE(length2(float2(-10.f,0.f)) == approx(100.f));

        REQUIRE(distance(float2(5.f,0.f), float2(10.f,0.f)) == approx(5.f));
        REQUIRE(distance(float2(-5.f,0.f), float2(-10.f,0.f)) == approx(5.f));

        STATIC_REQUIRE(distance2(float2(5.f,0.f), float2(10.f,0.f)) == approx(25.f));
        STATIC_REQUIRE(distance2(float2(-5.f,0.f), float2(-10.f,0.f)) == approx(25.f));

        STATIC_REQUIRE(dot(int2(1,2),int2(3,4)) == 11);
        STATIC_REQUIRE(cross(int2(1,0),int2(0,1)) == 1);
        STATIC_REQUIRE(cross(int3(1,0,0),int3(0,1,0)) == int3(0,0,1));
        REQUIRE(normalize(float2(0.5f,0.f)).x == approx(1.f));

        STATIC_REQUIRE(faceforward(float2(1.f), float2(2.f), float2(3.f)).x == approx(-1.f));
        STATIC_REQUIRE(reflect(float2(1.f), float2(2.f)).x == approx(-15.f));
        REQUIRE(refract(float2(1.f), float2(2.f), 1.f).x == approx(-15.f));
    }

    SUBCASE("Vector Relational Functions") {
        STATIC_REQUIRE(less(int3(1,1,1), int3(0,1,2)) == bool3(false, false, true));
        STATIC_REQUIRE(less_equal(int3(1,1,1), int3(0,1,2)) == bool3(false, true, true));

        STATIC_REQUIRE(greater(int3(1,1,1), int3(0,1,2)) == bool3(true, false, false));
        STATIC_REQUIRE(greater_equal(int3(1,1,1), int3(0,1,2)) == bool3(true, true, false));

        STATIC_REQUIRE(equal_to(int3(1,1,1), int3(0,1,2)) == bool3(false, true, false));
        STATIC_REQUIRE(equal_to(int4(1,1,1,1), int4(0,1,2,3), 0) == bool4(false, true, false, false));
        STATIC_REQUIRE(equal_to(int4(1,1,1,1), int4(0,1,2,3), 1) == bool4(true, true, true, false));
        STATIC_REQUIRE(equal_to(int4(1,1,1,1), int4(0,1,2,3), 2) == bool4(true, true, true, true));

        STATIC_REQUIRE(not_equal_to(int3(1,1,1), int3(0,1,2)) == bool3(true, false, true));
        STATIC_REQUIRE(not_equal_to(int4(1,1,1,1), int4(0,1,2,3), 0) == bool4(true, false, true, true));
        STATIC_REQUIRE(not_equal_to(int4(1,1,1,1), int4(0,1,2,3), 1) == bool4(false, false, false, true));
        STATIC_REQUIRE(not_equal_to(int4(1,1,1,1), int4(0,1,2,3), 2) == bool4(false, false, false, false));

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
    }
}
