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

TEST_CASE("vmath/fun") {
    SUBCASE("Angle and Trigonometric Functions") {
        STATIC_CHECK(radians(degrees(12.13f)) == uapprox(12.13f));
        STATIC_CHECK(degrees(radians(12.13f)) == uapprox(12.13f));

        {
            CHECK(asin(sin(1.23f)) == uapprox(1.23f));
            CHECK(acos(cos(1.23f)) == uapprox(1.23f));
            CHECK(atan(tan(1.23f)) == uapprox(1.23f));

            CHECK(asinh(sinh(1.23f)) == uapprox(1.23f));
            CHECK(acosh(cosh(1.23f)) == uapprox(1.23f));
            CHECK(atanh(tanh(1.23f)) == uapprox(1.23f));
        }

        {
            float out_s{}, out_c{};
            sincos(15.f, &out_s, &out_c);
            CHECK(out_s == uapprox(sin(15.f)));
            CHECK(out_c == uapprox(cos(15.f)));
            const auto [out_s2, out_c2] = sincos(15.f);
            CHECK(out_s2 == uapprox(sin(15.f)));
            CHECK(out_c2 == uapprox(cos(15.f)));
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
        STATIC_CHECK(vmath_hpp::abs(1) == 1);
        STATIC_CHECK(vmath_hpp::abs(-1) == 1);
        STATIC_CHECK(vmath_hpp::abs(1.f) == uapprox(1.f));
        STATIC_CHECK(vmath_hpp::abs(-1.f) == uapprox(1.f));

        STATIC_CHECK(sqr(2) == 4);
        STATIC_CHECK(sqr(-4.f) == uapprox(16.f));

        STATIC_CHECK(sign(2) == 1);
        STATIC_CHECK(sign(-2) == -1);
        STATIC_CHECK(sign(0) == 0);
        STATIC_CHECK(sign(2.f) == uapprox(1.f));
        STATIC_CHECK(sign(-2.f) == uapprox(-1.f));
        STATIC_CHECK(sign(0.f) == uapprox(0.f));

        STATIC_CHECK(rcp(2.f) == uapprox(0.5f));
        STATIC_CHECK(rcp(4.f) == uapprox(0.25f));

        CHECK(floor(1.7f) == uapprox(1.f));
        CHECK(trunc(1.7f) == uapprox(1.f));
        CHECK(round(1.7f) == uapprox(2.f));
        CHECK(ceil(1.7f) == uapprox(2.f));

        CHECK(fract(1.7f) == uapprox(0.7f));
        CHECK(fract(-2.3f) == uapprox(0.7f));

        CHECK(fmod(1.7f, 1.2f) == uapprox(0.5f));

        {
            float out_i{};
            CHECK(modf(1.7f, &out_i) == uapprox(0.7f));
            CHECK(out_i == uapprox(1.f));
        }

        STATIC_CHECK(min(0.f, 1.f) == uapprox(0.f));
        STATIC_CHECK(max(0.f, 1.f) == uapprox(1.f));

        STATIC_CHECK(clamp(1.0f, 2.f, 3.f) == uapprox(2.0f));
        STATIC_CHECK(clamp(2.5f, 2.f, 3.f) == uapprox(2.5f));
        STATIC_CHECK(clamp(3.5f, 2.f, 3.f) == uapprox(3.0f));

        STATIC_CHECK(saturate(-0.5f) == uapprox(0.f));
        STATIC_CHECK(saturate(0.5f) == uapprox(0.5f));
        STATIC_CHECK(saturate(1.5f) == uapprox(1.f));

        STATIC_CHECK(lerp(2.f, 10.f, 0.f) == uapprox(2.f));
        STATIC_CHECK(lerp(2.f, 10.f, 0.5f) == uapprox(6.f));
        STATIC_CHECK(lerp(2.f, 10.f, 1.f) == uapprox(10.f));

        STATIC_CHECK(lerp(2.f, 10.f, 0.f, 1.f) == uapprox(10.f));
        STATIC_CHECK(lerp(2.f, 10.f, 1.f, 0.f) == uapprox(2.f));
        STATIC_CHECK(lerp(2.f, 10.f, 0.5f, 0.2f) == uapprox(3.f));

        STATIC_CHECK(step(0.5f, 0.4f) == uapprox(0.f));
        STATIC_CHECK(step(0.5f, 0.6f) == uapprox(1.f));
        STATIC_CHECK(smoothstep(0.f, 1.f, 0.1f) == uapprox(0.028f));

        CHECK(fma(2.f, 3.f, 4.f) == uapprox(10.f));
    }

    SUBCASE("Geometric Functions") {
        STATIC_CHECK(length(10.f) == uapprox(10.f));
        STATIC_CHECK(length(-10.f) == uapprox(10.f));

        STATIC_CHECK(rlength(10.f) == uapprox(0.1f));
        STATIC_CHECK(rlength(-10.f) == uapprox(0.1f));

        STATIC_CHECK(length2(10.f) == uapprox(100.f));
        STATIC_CHECK(length2(-10.f) == uapprox(100.f));

        STATIC_CHECK(rlength2(10.f) == uapprox(0.01f));
        STATIC_CHECK(rlength2(-10.f) == uapprox(0.01f));

        STATIC_CHECK(distance(5.f, 10.f) == uapprox(5.f));
        STATIC_CHECK(distance(-5.f, -10.f) == uapprox(5.f));

        STATIC_CHECK(distance2(5.f, 10.f) == uapprox(25.f));
        STATIC_CHECK(distance2(-5.f, -10.f) == uapprox(25.f));

        STATIC_CHECK(dot(2.f, 5.f) == uapprox(10.f));
        CHECK(normalize(0.5f) == uapprox(1.f));

        STATIC_CHECK(faceforward(1.f, 2.f, 3.f) == uapprox(-1.f));
        STATIC_CHECK(reflect(1.f, 2.f) == uapprox(-7.f));
        CHECK(refract(1.f, 2.f, 1.f) == uapprox(-7.f));
    }

    SUBCASE("Relational Functions") {
        STATIC_CHECK_FALSE(any(false));
        STATIC_CHECK_FALSE(any(0));
        STATIC_CHECK(any(true));
        STATIC_CHECK(any(1));

        STATIC_CHECK_FALSE(all(false));
        STATIC_CHECK_FALSE(all(0));
        STATIC_CHECK(all(true));
        STATIC_CHECK(all(1));

        STATIC_CHECK(approx(1, 1));
        STATIC_CHECK_FALSE(approx(0, 1));
        STATIC_CHECK_FALSE(approx(0, 1, 0));
        STATIC_CHECK(approx(0, 1, 1));

        STATIC_CHECK(approx(1.f, 1.f + std::numeric_limits<float>::epsilon() * 0.5f));
        STATIC_CHECK_FALSE(approx(1.f, 1.f + std::numeric_limits<float>::epsilon() * 1.5f));
        STATIC_CHECK(approx(100.f, 100.f + std::numeric_limits<float>::epsilon() * 90.f));
        STATIC_CHECK_FALSE(approx(100.f, 100.f + std::numeric_limits<float>::epsilon() * 110.f));
    }
}
