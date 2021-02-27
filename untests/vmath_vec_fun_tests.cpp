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
    SUBCASE("Operators") {
        STATIC_CHECK(+ivec2(1,-2) == ivec2(1,-2));
        STATIC_CHECK(-ivec2(1,-2) == ivec2(-1,2));
        STATIC_CHECK(~uvec2(0xF0F0F0F0,0x0F0F0F0F) == uvec2(0x0F0F0F0F,0xF0F0F0F0));
        STATIC_CHECK((!ivec3(-1,0,1)) == bvec3(false, true, false));

        STATIC_CHECK(ivec2(1,2) + 3 == ivec2(4,5));
        STATIC_CHECK(ivec2(1,2) - 3 == ivec2(-2,-1));
        STATIC_CHECK(ivec2(1,2) * 3 == ivec2(3,6));
        STATIC_CHECK(ivec2(2,4) / 2 == ivec2(1,2));
        STATIC_CHECK((ivec2(11,12) & 6) == ivec2(2,4));
        STATIC_CHECK((ivec2(11,12) | 6) == ivec2(15,14));
        STATIC_CHECK((ivec2(11,12) ^ 6) == ivec2(13,10));
        STATIC_CHECK((ivec2(1,0) && 1) == bvec2(1,0));
        STATIC_CHECK((ivec2(1,0) || 1) == bvec2(1,1));

        STATIC_CHECK(3 + ivec2(1,2) == ivec2(4,5));
        STATIC_CHECK(3 - ivec2(1,2) == ivec2(2,1));
        STATIC_CHECK(3 * ivec2(1,2) == ivec2(3,6));
        STATIC_CHECK(4 / ivec2(2,4) == ivec2(2,1));
        STATIC_CHECK((6 & ivec2(11,12)) == ivec2(2,4));
        STATIC_CHECK((6 | ivec2(11,12)) == ivec2(15,14));
        STATIC_CHECK((6 ^ ivec2(11,12)) == ivec2(13,10));
        STATIC_CHECK((1 && ivec2(1,0)) == bvec2(1,0));
        STATIC_CHECK((1 || ivec2(1,0)) == bvec2(1,1));

        STATIC_CHECK(ivec2(1,2) + ivec2(3,4) == ivec2(4,6));
        STATIC_CHECK(ivec2(1,2) - ivec2(3,4) == ivec2(-2,-2));
        STATIC_CHECK(ivec2(1,2) * ivec2(3,4) == ivec2(3,8));
        STATIC_CHECK(ivec2(3,4) / ivec2(1,2) == ivec2(3,2));
        STATIC_CHECK((ivec2(6,7) & ivec2(11,12)) == ivec2(2,4));
        STATIC_CHECK((ivec2(6,7) | ivec2(11,12)) == ivec2(15,15));
        STATIC_CHECK((ivec2(6,7) ^ ivec2(11,12)) == ivec2(13,11));
        STATIC_CHECK((ivec2(0,1) && ivec2(1,0)) == bvec2(0,0));
        STATIC_CHECK((ivec2(0,1) || ivec2(1,0)) == bvec2(1,1));

        {
            ivec2 v{1,2};
            CHECK(&v == &(++v));
            CHECK(v == ivec2{2,3});
            CHECK(&v == &(--v));
            CHECK(v == ivec2{1,2});
        }
        {
            ivec2 v{1,2};
            CHECK(v++ == ivec2{1,2});
            CHECK(v == ivec2{2,3});
            CHECK(v-- == ivec2{2,3});
            CHECK(v == ivec2{1,2});
        }
        {
            ivec2 v{1,2};
            CHECK(&v == &(v += 3));
            CHECK(v == ivec2{4,5});
            CHECK(&v == &(v += ivec2{1,2}));
            CHECK(v == ivec2{5,7});
        }
        {
            ivec2 v{4,5};
            CHECK(&v == &(v -= 3));
            CHECK(v == ivec2{1,2});
            CHECK(&v == &(v -= ivec2{2,4}));
            CHECK(v == ivec2{-1,-2});
        }
        {
            ivec2 v{1,2};
            CHECK(&v == &(v *= 3));
            CHECK(v == ivec2{3,6});
            CHECK(&v == &(v *= ivec2{2,3}));
            CHECK(v == ivec2{6,18});
        }
        {
            ivec2 v{6,18};
            CHECK(&v == &(v /= 2));
            CHECK(v == ivec2{3,9});
            CHECK(&v == &(v /= ivec2{3,4}));
            CHECK(v == ivec2{1,2});
        }
        {
            ivec2 v1{11,12};
            CHECK(&v1 == &(v1 &= 6));
            CHECK(v1 == ivec2(2,4));
            ivec2 v2{6,7};
            CHECK(&v2 == &(v2 &= ivec2(11,12)));
            CHECK(v2 == ivec2(2,4));
        }
        {
            ivec2 v1{11,12};
            CHECK(&v1 == &(v1 |= 6));
            CHECK(v1 == ivec2(15,14));
            ivec2 v2{6,7};
            CHECK(&v2 == &(v2 |= ivec2(11,12)));
            CHECK(v2 == ivec2(15,15));
        }
        {
            ivec2 v1{11,12};
            CHECK(&v1 == &(v1 ^= 6));
            CHECK(v1 == ivec2(13,10));
            ivec2 v2{6,7};
            CHECK(&v2 == &(v2 ^= ivec2(11,12)));
            CHECK(v2 == ivec2(13,11));
        }
    }

    SUBCASE("Operators2") {
        STATIC_CHECK(ivec2{} + 0.0 == dvec2{});
        STATIC_CHECK(0.0 + ivec2{} == dvec2{});
        STATIC_CHECK(ivec2{} + dvec2{} == dvec2{});
        STATIC_CHECK(dvec2{} + ivec2{} == dvec2{});

        STATIC_CHECK(ivec2{} - 0.0 == dvec2{});
        STATIC_CHECK(0.0 - ivec2{} == dvec2{});
        STATIC_CHECK(ivec2{} - dvec2{} == dvec2{});
        STATIC_CHECK(dvec2{} - ivec2{} == dvec2{});

        STATIC_CHECK(ivec2{} * 1.0 == dvec2{});
        STATIC_CHECK(0.0 * ivec2{1} == dvec2{});
        STATIC_CHECK(ivec2{} * dvec2{1.0} == dvec2{});
        STATIC_CHECK(dvec2{} * ivec2{1} == dvec2{});

        STATIC_CHECK(ivec2{} / 1.0 == dvec2{});
        STATIC_CHECK(0.0 / ivec2{1} == dvec2{});
        STATIC_CHECK(ivec2{} / dvec2{1.0} == dvec2{});
        STATIC_CHECK(dvec2{} / ivec2{1} == dvec2{});
    }

    SUBCASE("Conversions2") {
        {
            STATIC_CHECK(dvec2(1) == dvec2(1,1));
            STATIC_CHECK(dvec2(1,2.f) == dvec2(1,2));
            STATIC_CHECK(dvec2(ivec2(1,2)) == dvec2(1,2));
            STATIC_CHECK(dvec2(ivec3(1,2,3)) == dvec2(1,2));
            STATIC_CHECK(dvec2(ivec4(1,2,3,4)) == dvec2(1,2));
        }
        {
            STATIC_CHECK(dvec3(1) == dvec3(1,1,1));
            STATIC_CHECK(dvec3(1,2.f,3u) == dvec3(1,2,3));
            STATIC_CHECK(dvec3(ivec3(1,2,3)) == dvec3(1,2,3));
            STATIC_CHECK(dvec3(ivec4(1,2,3,4)) == dvec3(1,2,3));

            STATIC_CHECK(dvec3(ivec2(1,2),3.f) == dvec3(1,2,3));
            STATIC_CHECK(dvec3(1.f,ivec2(2,3)) == dvec3(1,2,3));
        }
        {
            STATIC_CHECK(dvec4(1) == dvec4(1,1,1,1));
            STATIC_CHECK(dvec4(1,2.f,3u,4) == dvec4(1,2,3,4));
            STATIC_CHECK(dvec4(ivec4(1,2,3,4)) == dvec4(1,2,3,4));

            STATIC_CHECK(dvec4(ivec2{1,2},3u,4.f) == dvec4(1,2,3,4));
            STATIC_CHECK(dvec4(1,ivec2{2,3},4.f) == dvec4(1,2,3,4));
            STATIC_CHECK(dvec4(1,2.f,ivec2{3,4}) == dvec4(1,2,3,4));
            STATIC_CHECK(dvec4(ivec2{1,2},dvec2{3,4}) == dvec4(1,2,3,4));

            STATIC_CHECK(dvec4(ivec3{1,2,3},4.f) == dvec4(1,2,3,4));
            STATIC_CHECK(dvec4(1.f,ivec3{2,3,4}) == dvec4(1,2,3,4));
        }
    }

    SUBCASE("Angle and Trigonometric Functions") {
        STATIC_CHECK(radians(degrees(fvec2(12.13f))) == uapprox2(12.13f));
        STATIC_CHECK(degrees(radians(fvec2(12.13f))) == uapprox2(12.13f));

        (void)sin(fvec2(1.f));
        (void)cos(fvec2(1.f));
        (void)tan(fvec2(1.f));

        (void)asin(fvec2(1.f));
        (void)acos(fvec2(1.f));
        (void)atan(fvec2(1.f));
        (void)atan2(fvec2(1.f), fvec2(1.f));

        (void)sinh(fvec2(1.f));
        (void)cosh(fvec2(1.f));
        (void)tanh(fvec2(1.f));

        (void)asinh(fvec2(1.f));
        (void)acosh(fvec2(1.f));
        (void)atanh(fvec2(1.f));

        {
            fvec2 out_ss{}, out_cs{};
            sincos(fvec2(10.f,15.f), &out_ss, &out_cs);
            CHECK(out_ss == uapprox2(sin(10.f), sin(15.f)));
            CHECK(out_cs == uapprox2(cos(10.f), cos(15.f)));
            const auto [out_ss2, out_cs2] = sincos(fvec2(10.f,15.f));
            CHECK(out_ss2 == uapprox2(sin(10.f), sin(15.f)));
            CHECK(out_cs2 == uapprox2(cos(10.f), cos(15.f)));
        }
    }

    SUBCASE("Exponential Functions") {
        (void)pow(fvec2(1.f), fvec2(2.f));
        (void)exp(fvec2(1.f));
        (void)log(fvec2(1.f));
        (void)exp2(fvec2(1.f));
        (void)log2(fvec2(1.f));
        (void)sqrt(fvec2(1.f));
        (void)rsqrt(fvec2(1.f));
    }

    SUBCASE("Common Functions") {
        STATIC_CHECK(abs(fvec2(1.f, -1.f)) == uapprox2(1.f,1.f));
        STATIC_CHECK(sqr(fvec2(2.f, -3.f)) == uapprox2(4.f,9.f));
        STATIC_CHECK(sign(fvec3(1.f, -1.f, 0.f)) == uapprox3(1.f,-1.f,0.f));
        STATIC_CHECK(rcp(fvec2(2.f, 4.f)) == uapprox2(0.5f,0.25f));

        CHECK(copysign(
            fvec4(2.f, -4.f, 2.f, -4.f),
            5.f)
        == uapprox4(2.f, 4.f, 2.f, 4.f));

        CHECK(copysign(
            fvec4(2.f, -4.f, 2.f, -4.f),
            -5.f)
        == uapprox4(-2.f, -4.f, -2.f, -4.f));

        CHECK(copysign(
            fvec4(2.f, -4.f, 2.f, -4.f),
            fvec4(10.f, 5.f, -4.f, -0.4f))
        == uapprox4(2.f, 4.f, -2.f, -4.f));

        (void)floor(fvec2(1.f, -1.f));
        (void)trunc(fvec2(1.f, -1.f));
        (void)round(fvec2(1.f, -1.f));
        (void)ceil(fvec2(1.f, -1.f));
        (void)fract(fvec2(1.f, -1.f));

        CHECK(fmod(fvec2(1.7f), 1.2f) == uapprox2(0.5f));
        CHECK(fmod(fvec2(1.7f), fvec2(1.2f)) == uapprox2(0.5f));

        {
            fvec2 out_i{};
            CHECK(modf(fvec2(1.7f), &out_i) == uapprox2(0.7f));
            CHECK(out_i.x == uapprox(1.f));
        }

        STATIC_CHECK(min(ivec2(1,2)) == 1);
        STATIC_CHECK(min(ivec2(1,2), 1) == ivec2(1,1));
        STATIC_CHECK(min(1, ivec2(1,2)) == ivec2(1,1));
        STATIC_CHECK(min(ivec2(1,1), ivec2(0,2)) == ivec2(0,1));

        STATIC_CHECK(max(ivec2(1,2)) == 2);
        STATIC_CHECK(max(ivec2(1,2), 1) == ivec2(1,2));
        STATIC_CHECK(max(1, ivec2(1,2)) == ivec2(1,2));
        STATIC_CHECK(max(ivec2(1,1), ivec2(0,2)) == ivec2(1,2));

        STATIC_CHECK(clamp(ivec2(1,2), 0, 1) == ivec2(1,1));
        STATIC_CHECK(clamp(ivec2(1,2), ivec2(0), ivec2(1)) == ivec2(1,1));

        STATIC_CHECK(saturate(fvec3(-1.f,0.5,1.5f)) == uapprox3(0.f,0.5f,1.f));

        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), 0.f) == uapprox2(2.f));
        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), 0.5f) == uapprox2(6.f));
        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), 1.f) == uapprox2(10.f));

        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), 0.f, 1.f) == uapprox2(10.f));
        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), 1.f, 0.f) == uapprox2(2.f));
        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), 0.5f, 0.2f) == uapprox2(3.f));

        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), fvec2(0.f)) == uapprox2(2.f));
        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), fvec2(0.5f)) == uapprox2(6.f));
        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), fvec2(1.f)) == uapprox2(10.f));

        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), fvec2(0.f), fvec2(1.f)) == uapprox2(10.f));
        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), fvec2(1.f), fvec2(0.f)) == uapprox2(2.f));
        STATIC_CHECK(lerp(fvec2(2.f), fvec2(10.f), fvec2(0.5f), fvec2(0.2f)) == uapprox2(3.f));

        STATIC_CHECK(step(0.5f, fvec2(0.4f)) == uapprox2(0.f));
        STATIC_CHECK(step(0.5f, fvec2(0.6f)) == uapprox2(1.f));
        STATIC_CHECK(step(fvec2(0.5f), fvec2(0.4f)) == uapprox2(0.f));
        STATIC_CHECK(step(fvec2(0.5f), fvec2(0.6f)) == uapprox2(1.f));

        STATIC_CHECK(smoothstep(0.f, 1.f, fvec2(0.1f)) == uapprox2(0.028f));
        STATIC_CHECK(smoothstep(fvec2(0.f), fvec2(1.f), fvec2(0.1f)) == uapprox2(0.028f));
    }

    SUBCASE("Geometric Functions") {
        CHECK(length(fvec2(10.f,0.f)) == uapprox(10.f));
        CHECK(length(fvec2(-10.f,0.f)) == uapprox(10.f));

        CHECK(rlength(fvec2(10.f,0.f)) == uapprox(0.1f));
        CHECK(rlength(fvec2(-10.f,0.f)) == uapprox(0.1f));

        STATIC_CHECK(length2(fvec2(10.f,0.f)) == uapprox(100.f));
        STATIC_CHECK(length2(fvec2(-10.f,0.f)) == uapprox(100.f));

        STATIC_CHECK(rlength2(fvec2(10.f,0.f)) == uapprox(0.01f));
        STATIC_CHECK(rlength2(fvec2(-10.f,0.f)) == uapprox(0.01f));

        CHECK(distance(fvec2(5.f,0.f), fvec2(10.f,0.f)) == uapprox(5.f));
        CHECK(distance(fvec2(-5.f,0.f), fvec2(-10.f,0.f)) == uapprox(5.f));

        STATIC_CHECK(distance2(fvec2(5.f,0.f), fvec2(10.f,0.f)) == uapprox(25.f));
        STATIC_CHECK(distance2(fvec2(-5.f,0.f), fvec2(-10.f,0.f)) == uapprox(25.f));

        STATIC_CHECK(dot(ivec2(1,2),ivec2(3,4)) == 11);
        STATIC_CHECK(dot(ivec2(1,2),dvec2(3,4)) == uapprox(11.0));
        STATIC_CHECK(dot(dvec2(3,4),ivec2(1,2)) == uapprox(11.0));

        STATIC_CHECK(cross(ivec2(1,0),ivec2(0,1)) == 1);
        STATIC_CHECK(cross(ivec2(1,0),dvec2(0,1)) == uapprox(1.0));
        STATIC_CHECK(cross(dvec2(0,1),ivec2(1,0)) == uapprox(-1.0));

        STATIC_CHECK(cross(ivec3(1,0,0),ivec3(0,1,0)) == ivec3(0,0,1));
        STATIC_CHECK(cross(ivec3(1,0,0),dvec3(0,1,0)) == uapprox3(0.0,0.0,1.0));
        STATIC_CHECK(cross(dvec3(0,1,0),ivec3(1,0,0)) == uapprox3(0.0,0.0,-1.0));

        CHECK(normalize(fvec2(0.5f,0.f)).x == uapprox(1.f));

        STATIC_CHECK(faceforward(fvec2(1.f), fvec2(2.f), fvec2(3.f)).x == uapprox(-1.f));
        STATIC_CHECK(reflect(fvec2(1.f), fvec2(2.f)).x == uapprox(-15.f));
        CHECK(refract(fvec2(1.f), fvec2(2.f), 1.f).x == uapprox(-15.f));
    }

    SUBCASE("Relational Functions") {
        STATIC_CHECK_FALSE(any(bvec2(false, false)));
        STATIC_CHECK(any(bvec2(true, false)));
        STATIC_CHECK(any(bvec2(false, true)));
        STATIC_CHECK(any(bvec2(true, true)));

        STATIC_CHECK_FALSE(any(ivec2(0, 0)));
        STATIC_CHECK(any(ivec2(1, 0)));
        STATIC_CHECK(any(ivec2(0, 1)));
        STATIC_CHECK(any(ivec2(1, 1)));

        STATIC_CHECK_FALSE(all(bvec2(false, false)));
        STATIC_CHECK_FALSE(all(bvec2(true, false)));
        STATIC_CHECK_FALSE(all(bvec2(false, true)));
        STATIC_CHECK(all(bvec2(true, true)));

        STATIC_CHECK_FALSE(all(ivec2(0, 0)));
        STATIC_CHECK_FALSE(all(ivec2(1, 0)));
        STATIC_CHECK_FALSE(all(ivec2(0, 1)));
        STATIC_CHECK(all(ivec2(1, 1)));

        STATIC_CHECK(approx(ivec3(1,1,1), ivec3(0,1,2)) == bvec3(false, true, false));
        STATIC_CHECK(approx(ivec4(1,1,1,1), ivec4(0,1,2,3), 0) == bvec4(false, true, false, false));
        STATIC_CHECK(approx(ivec4(1,1,1,1), ivec4(0,1,2,3), 1) == bvec4(true, true, true, false));
        STATIC_CHECK(approx(ivec4(1,1,1,1), ivec4(0,1,2,3), 2) == bvec4(true, true, true, true));

        STATIC_CHECK(less(ivec3(1,1,1), ivec3(0,1,2)) == bvec3(false, false, true));
        STATIC_CHECK(less_equal(ivec3(1,1,1), ivec3(0,1,2)) == bvec3(false, true, true));
        STATIC_CHECK(greater(ivec3(1,1,1), ivec3(0,1,2)) == bvec3(true, false, false));
        STATIC_CHECK(greater_equal(ivec3(1,1,1), ivec3(0,1,2)) == bvec3(true, true, false));

        STATIC_CHECK(equal_to(ivec3(1,1,1), ivec3(0,1,2)) == bvec3(false, true, false));
        STATIC_CHECK(not_equal_to(ivec3(1,1,1), ivec3(0,1,2)) == bvec3(true, false, true));
    }
}
