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

TEST_CASE("vmath/fun") {
    SUBCASE("Angle and Trigonometry Functions") {
        STATIC_REQUIRE(radians(degrees(12.13f)) == approx(12.13f));
        STATIC_REQUIRE(degrees(radians(12.13f)) == approx(12.13f));

        (void)sin(0.f);
        (void)cos(0.f);
        (void)tan(0.f);

        (void)asin(0.f);
        (void)acos(0.f);
        (void)atan(0.f);
        (void)atan2(0.f, 0.f);

        (void)sinh(0.f);
        (void)cosh(0.f);
        (void)tanh(0.f);

        (void)asinh(0.f);
        (void)acosh(0.f);
        (void)atanh(0.f);

        {
            float out_s{}, out_c{};
            sincos(15.f, &out_s, &out_c);
            REQUIRE(out_s == approx(sin(15.f)));
            REQUIRE(out_c == approx(cos(15.f)));
        }
    }

    SUBCASE("Exponential Functions") {
        (void)pow(2.f, 3.f);
        (void)exp(2.f);
        (void)log(2.f);
        (void)exp2(2.f);
        (void)log2(2.f);
        (void)sqrt(2.f);
        (void)rsqrt(2.f);
    }

    SUBCASE("Common Functions") {
        STATIC_REQUIRE(vmath_hpp::abs(1) == 1);
        STATIC_REQUIRE(vmath_hpp::abs(-1) == 1);
        STATIC_REQUIRE(vmath_hpp::abs(1.f) == approx(1.f));
        STATIC_REQUIRE(vmath_hpp::abs(-1.f) == approx(1.f));

        STATIC_REQUIRE(sign(2) == 1);
        STATIC_REQUIRE(sign(-2) == -1);
        STATIC_REQUIRE(sign(0) == 0);
        STATIC_REQUIRE(sign(2.f) == approx(1.f));
        STATIC_REQUIRE(sign(-2.f) == approx(-1.f));
        STATIC_REQUIRE(sign(0.f) == approx(0.f));

        STATIC_REQUIRE(reciprocal(2.f) == approx(0.5f));
        STATIC_REQUIRE(reciprocal(4.f) == approx(0.25f));

        REQUIRE(floor(1.7f) == approx(1.f));
        REQUIRE(trunc(1.7f) == approx(1.f));
        REQUIRE(round(1.7f) == approx(2.f));
        REQUIRE(ceil(1.7f) == approx(2.f));

        REQUIRE(fract(1.7f) == approx(0.7f));
        REQUIRE(fract(-2.3f) == approx(0.7f));

        REQUIRE(fmod(1.7f, 1.2f) == approx(0.5f));

        {
            float out_i{};
            REQUIRE(modf(1.7f, &out_i) == approx(0.7f));
            REQUIRE(out_i == approx(1.f));
        }

        STATIC_REQUIRE(min(0.f, 1.f) == approx(0.f));
        STATIC_REQUIRE(min(3.f, 2.f, 1.f) == approx(1.f));
        STATIC_REQUIRE(min(4.f, 3.f, 2.f, 1.f) == approx(1.f));

        STATIC_REQUIRE(max(0.f, 1.f) == approx(1.f));
        STATIC_REQUIRE(max(3.f, 2.f, 1.f) == approx(3.f));
        STATIC_REQUIRE(max(4.f, 3.f, 2.f, 1.f) == approx(4.f));

        STATIC_REQUIRE(clamp(1.0f, 2.f, 3.f) == approx(2.0f));
        STATIC_REQUIRE(clamp(2.5f, 2.f, 3.f) == approx(2.5f));
        STATIC_REQUIRE(clamp(3.5f, 2.f, 3.f) == approx(3.0f));

        STATIC_REQUIRE(saturate(-0.5f) == approx(0.f));
        STATIC_REQUIRE(saturate(0.5f) == approx(0.5f));
        STATIC_REQUIRE(saturate(1.5f) == approx(1.f));

        STATIC_REQUIRE(lerp(0.f, 10.f, 0.5f) == approx(5.f));
        STATIC_REQUIRE(step(0.5f, 0.4f) == approx(0.f));
        STATIC_REQUIRE(step(0.5f, 0.6f) == approx(1.f));
        STATIC_REQUIRE(smoothstep(0.f, 1.f, 0.1f) == approx(0.028f));

        REQUIRE_FALSE(vmath_hpp::isnan(1.f));
        REQUIRE_FALSE(vmath_hpp::isinf(1.f));
        REQUIRE(vmath_hpp::isfinite(1.f));

        REQUIRE(fma(2.f, 3.f, 4.f) == approx(10.f));

        {
            int out_exp{};
            REQUIRE(frexp(1.7f, &out_exp) == approx(0.85f));
            REQUIRE(out_exp == 1);
        }

        REQUIRE(ldexp(0.85f, 1) == approx(1.7f));
    }

    SUBCASE("Geometric Functions") {
        STATIC_REQUIRE(length(10.f) == approx(10.f));
        STATIC_REQUIRE(length(-10.f) == approx(10.f));

        STATIC_REQUIRE(length2(10.f) == approx(100.f));
        STATIC_REQUIRE(length2(-10.f) == approx(100.f));

        STATIC_REQUIRE(distance(5.f, 10.f) == approx(5.f));
        STATIC_REQUIRE(distance(-5.f, -10.f) == approx(5.f));

        STATIC_REQUIRE(distance2(5.f, 10.f) == approx(25.f));
        STATIC_REQUIRE(distance2(-5.f, -10.f) == approx(25.f));

        STATIC_REQUIRE(dot(2.f, 5.f) == approx(10.f));
        REQUIRE(normalize(0.5f) == approx(1.f));

        STATIC_REQUIRE(faceforward(1.f, 2.f, 3.f) == approx(-1.f));
        STATIC_REQUIRE(reflect(1.f, 2.f) == approx(-7.f));
        REQUIRE(refract(1.f, 2.f, 1.f) == approx(-7.f));
    }

    SUBCASE("Scalar Relational Functions") {
        STATIC_REQUIRE(less(0, 1));
        STATIC_REQUIRE(less_equal(0, 1));
        STATIC_REQUIRE_FALSE(less(1, 1));
        STATIC_REQUIRE(less_equal(1, 1));

        STATIC_REQUIRE(greater(1, 0));
        STATIC_REQUIRE(greater_equal(1, 0));
        STATIC_REQUIRE_FALSE(greater(1, 1));
        STATIC_REQUIRE(greater_equal(1, 1));

        STATIC_REQUIRE(equal_to(1, 1));
        STATIC_REQUIRE_FALSE(equal_to(0, 1));
        STATIC_REQUIRE_FALSE(equal_to(0, 1, 0));
        STATIC_REQUIRE(equal_to(0, 1, 1));

        STATIC_REQUIRE(not_equal_to(0, 1));
        STATIC_REQUIRE(not_equal_to(0, 1, 0));
        STATIC_REQUIRE_FALSE(not_equal_to(0, 1, 1));
        STATIC_REQUIRE_FALSE(not_equal_to(1, 1));
        STATIC_REQUIRE_FALSE(not_equal_to(1, 1, 0));
        STATIC_REQUIRE_FALSE(not_equal_to(1, 1, 1));

        STATIC_REQUIRE_FALSE(any(false));
        STATIC_REQUIRE_FALSE(any(0));
        STATIC_REQUIRE(any(true));
        STATIC_REQUIRE(any(1));

        STATIC_REQUIRE_FALSE(all(false));
        STATIC_REQUIRE_FALSE(all(0));
        STATIC_REQUIRE(all(true));
        STATIC_REQUIRE(all(1));
    }
}
