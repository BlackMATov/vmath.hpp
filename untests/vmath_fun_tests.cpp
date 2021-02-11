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
        STATIC_REQUIRE(radians(degrees(12.13f)) == uapprox(12.13f));
        STATIC_REQUIRE(degrees(radians(12.13f)) == uapprox(12.13f));

        {
            REQUIRE(asin(sin(1.23f)) == uapprox(1.23f));
            REQUIRE(acos(cos(1.23f)) == uapprox(1.23f));
            REQUIRE(atan(tan(1.23f)) == uapprox(1.23f));

            REQUIRE(asinh(sinh(1.23f)) == uapprox(1.23f));
            REQUIRE(acosh(cosh(1.23f)) == uapprox(1.23f));
            REQUIRE(atanh(tanh(1.23f)) == uapprox(1.23f));
        }

        {
            float out_s{}, out_c{};
            sincos(15.f, &out_s, &out_c);
            REQUIRE(out_s == uapprox(sin(15.f)));
            REQUIRE(out_c == uapprox(cos(15.f)));
            const auto [out_s2, out_c2] = sincos(15.f);
            REQUIRE(out_s2 == uapprox(sin(15.f)));
            REQUIRE(out_c2 == uapprox(cos(15.f)));
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
        STATIC_REQUIRE(vmath_hpp::abs(1.f) == uapprox(1.f));
        STATIC_REQUIRE(vmath_hpp::abs(-1.f) == uapprox(1.f));

        STATIC_REQUIRE(sqr(2) == 4);
        STATIC_REQUIRE(sqr(-4.f) == uapprox(16.f));

        STATIC_REQUIRE(sign(2) == 1);
        STATIC_REQUIRE(sign(-2) == -1);
        STATIC_REQUIRE(sign(0) == 0);
        STATIC_REQUIRE(sign(2.f) == uapprox(1.f));
        STATIC_REQUIRE(sign(-2.f) == uapprox(-1.f));
        STATIC_REQUIRE(sign(0.f) == uapprox(0.f));

        STATIC_REQUIRE(rcp(2.f) == uapprox(0.5f));
        STATIC_REQUIRE(rcp(4.f) == uapprox(0.25f));

        REQUIRE(floor(1.7f) == uapprox(1.f));
        REQUIRE(trunc(1.7f) == uapprox(1.f));
        REQUIRE(round(1.7f) == uapprox(2.f));
        REQUIRE(ceil(1.7f) == uapprox(2.f));

        REQUIRE(fract(1.7f) == uapprox(0.7f));
        REQUIRE(fract(-2.3f) == uapprox(0.7f));

        REQUIRE(fmod(1.7f, 1.2f) == uapprox(0.5f));

        {
            float out_i{};
            REQUIRE(modf(1.7f, &out_i) == uapprox(0.7f));
            REQUIRE(out_i == uapprox(1.f));
        }

        STATIC_REQUIRE(min(0.f, 1.f) == uapprox(0.f));
        STATIC_REQUIRE(max(0.f, 1.f) == uapprox(1.f));

        STATIC_REQUIRE(min({0.f}) == uapprox(0.f));
        STATIC_REQUIRE(min({0.f, 1.f}) == uapprox(0.f));
        STATIC_REQUIRE(min({3.f, 2.f, 1.f}) == uapprox(1.f));
        STATIC_REQUIRE(min({4.f, 3.f, 2.f, 1.f}) == uapprox(1.f));

        STATIC_REQUIRE(min({0.f}, [](auto x, auto y){return x < y;}) == uapprox(0.f));
        STATIC_REQUIRE(min({0.f, 1.f}, [](auto x, auto y){return x < y;}) == uapprox(0.f));
        STATIC_REQUIRE(min({3.f, 2.f, 1.f}, [](auto x, auto y){return x < y;}) == uapprox(1.f));
        STATIC_REQUIRE(min({4.f, 3.f, 2.f, 1.f}, [](auto x, auto y){return x < y;}) == uapprox(1.f));

        STATIC_REQUIRE(min({0.f}, [](auto x, auto y){return x > y;}) == uapprox(0.f));
        STATIC_REQUIRE(min({0.f, 1.f}, [](auto x, auto y){return x > y;}) == uapprox(1.f));
        STATIC_REQUIRE(min({3.f, 2.f, 1.f}, [](auto x, auto y){return x > y;}) == uapprox(3.f));
        STATIC_REQUIRE(min({4.f, 3.f, 2.f, 1.f}, [](auto x, auto y){return x > y;}) == uapprox(4.f));

        STATIC_REQUIRE(max({0.f}, [](auto x, auto y){return x < y;}) == uapprox(0.f));
        STATIC_REQUIRE(max({0.f, 1.f}, [](auto x, auto y){return x < y;}) == uapprox(1.f));
        STATIC_REQUIRE(max({3.f, 2.f, 1.f}, [](auto x, auto y){return x < y;}) == uapprox(3.f));
        STATIC_REQUIRE(max({4.f, 3.f, 2.f, 1.f}, [](auto x, auto y){return x < y;}) == uapprox(4.f));

        STATIC_REQUIRE(max({0.f}, [](auto x, auto y){return x > y;}) == uapprox(0.f));
        STATIC_REQUIRE(max({0.f, 1.f}, [](auto x, auto y){return x > y;}) == uapprox(0.f));
        STATIC_REQUIRE(max({3.f, 2.f, 1.f}, [](auto x, auto y){return x > y;}) == uapprox(1.f));
        STATIC_REQUIRE(max({4.f, 3.f, 2.f, 1.f}, [](auto x, auto y){return x > y;}) == uapprox(1.f));

        STATIC_REQUIRE(clamp(1.0f, 2.f, 3.f) == uapprox(2.0f));
        STATIC_REQUIRE(clamp(2.5f, 2.f, 3.f) == uapprox(2.5f));
        STATIC_REQUIRE(clamp(3.5f, 2.f, 3.f) == uapprox(3.0f));

        STATIC_REQUIRE(saturate(-0.5f) == uapprox(0.f));
        STATIC_REQUIRE(saturate(0.5f) == uapprox(0.5f));
        STATIC_REQUIRE(saturate(1.5f) == uapprox(1.f));

        STATIC_REQUIRE(lerp(2.f, 10.f, 0.f) == uapprox(2.f));
        STATIC_REQUIRE(lerp(2.f, 10.f, 0.5f) == uapprox(6.f));
        STATIC_REQUIRE(lerp(2.f, 10.f, 1.f) == uapprox(10.f));

        STATIC_REQUIRE(lerp(2.f, 10.f, 0.f, 1.f) == uapprox(10.f));
        STATIC_REQUIRE(lerp(2.f, 10.f, 1.f, 0.f) == uapprox(2.f));
        STATIC_REQUIRE(lerp(2.f, 10.f, 0.5f, 0.2f) == uapprox(3.f));

        STATIC_REQUIRE(step(0.5f, 0.4f) == uapprox(0.f));
        STATIC_REQUIRE(step(0.5f, 0.6f) == uapprox(1.f));
        STATIC_REQUIRE(smoothstep(0.f, 1.f, 0.1f) == uapprox(0.028f));

        REQUIRE_FALSE(vmath_hpp::isnan(1.f));
        REQUIRE_FALSE(vmath_hpp::isinf(1.f));
        REQUIRE(vmath_hpp::isfinite(1.f));

        REQUIRE(fma(2.f, 3.f, 4.f) == uapprox(10.f));

        {
            int out_exp{};
            REQUIRE(frexp(1.7f, &out_exp) == uapprox(0.85f));
            REQUIRE(out_exp == 1);
        }

        REQUIRE(ldexp(0.85f, 1) == uapprox(1.7f));
    }

    SUBCASE("Geometric Functions") {
        STATIC_REQUIRE(length(10.f) == uapprox(10.f));
        STATIC_REQUIRE(length(-10.f) == uapprox(10.f));

        STATIC_REQUIRE(length2(10.f) == uapprox(100.f));
        STATIC_REQUIRE(length2(-10.f) == uapprox(100.f));

        STATIC_REQUIRE(distance(5.f, 10.f) == uapprox(5.f));
        STATIC_REQUIRE(distance(-5.f, -10.f) == uapprox(5.f));

        STATIC_REQUIRE(distance2(5.f, 10.f) == uapprox(25.f));
        STATIC_REQUIRE(distance2(-5.f, -10.f) == uapprox(25.f));

        STATIC_REQUIRE(dot(2.f, 5.f) == uapprox(10.f));
        REQUIRE(normalize(0.5f) == uapprox(1.f));

        STATIC_REQUIRE(faceforward(1.f, 2.f, 3.f) == uapprox(-1.f));
        STATIC_REQUIRE(reflect(1.f, 2.f) == uapprox(-7.f));
        REQUIRE(refract(1.f, 2.f, 1.f) == uapprox(-7.f));
    }

    SUBCASE("Relational Functions") {
        STATIC_REQUIRE_FALSE(any(false));
        STATIC_REQUIRE_FALSE(any(0));
        STATIC_REQUIRE(any(true));
        STATIC_REQUIRE(any(1));

        STATIC_REQUIRE_FALSE(all(false));
        STATIC_REQUIRE_FALSE(all(0));
        STATIC_REQUIRE(all(true));
        STATIC_REQUIRE(all(1));

        STATIC_REQUIRE(approx(1, 1));
        STATIC_REQUIRE_FALSE(approx(0, 1));
        STATIC_REQUIRE_FALSE(approx(0, 1, 0));
        STATIC_REQUIRE(approx(0, 1, 1));

        STATIC_REQUIRE(approx(1.f, 1.f + std::numeric_limits<float>::epsilon() * 0.5f));
        STATIC_REQUIRE_FALSE(approx(1.f, 1.f + std::numeric_limits<float>::epsilon() * 1.5f));
        STATIC_REQUIRE(approx(100.f, 100.f + std::numeric_limits<float>::epsilon() * 90.f));
        STATIC_REQUIRE_FALSE(approx(100.f, 100.f + std::numeric_limits<float>::epsilon() * 110.f));
    }
}
