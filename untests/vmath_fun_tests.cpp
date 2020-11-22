/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_fun.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
    template < typename T >
    class approx {
    public:
        explicit constexpr approx(T v) : value_(v) {}

        friend constexpr bool operator==(const T& l, const approx& r) {
            return (r.value_ < l + epsilon)
                && (l < r.value_ + epsilon);
        }
    private:
        T value_;
        static constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
    };
}

TEST_CASE("vmath/fun") {
    using namespace vmath_hpp;

    SECTION("Angle and Trigonometry Functions") {
        STATIC_REQUIRE(radians(degrees(12.13f)) == approx(12.13f));
        STATIC_REQUIRE(degrees(radians(12.13f)) == approx(12.13f));

        sin(0.f);
        cos(0.f);
        tan(0.f);

        asin(0.f);
        acos(0.f);
        atan(0.f);
        atan2(0.f, 0.f);

        sinh(0.f);
        cosh(0.f);
        tanh(0.f);

        asinh(0.f);
        acosh(0.f);
        atanh(0.f);
    }

    SECTION("Exponential Functions") {
        pow(2.f, 3.f);
        exp(2.f);
        log(2.f);
        exp2(2.f);
        log2(2.f);
        sqrt(2.f);
        invsqrt(2.f);
    }

    SECTION("Common Functions") {
        REQUIRE(abs(1) == 1);
        REQUIRE(abs(-1) == 1);
        REQUIRE(abs(1.f) == approx(1.f));
        REQUIRE(abs(-1.f) == approx(1.f));

        REQUIRE(sign(2) == 1);
        REQUIRE(sign(-2) == -1);
        REQUIRE(sign(0) == 0);
        REQUIRE(sign(2.f) == approx(1.f));
        REQUIRE(sign(-2.f) == approx(-1.f));
        REQUIRE(sign(0.f) == approx(0.f));

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

        STATIC_REQUIRE(min(1.f, 2.f) == approx(1.f));
        STATIC_REQUIRE(max(1.f, 2.f) == approx(2.f));

        STATIC_REQUIRE(clamp(1.0f, 2.f, 3.f) == approx(2.0f));
        STATIC_REQUIRE(clamp(2.5f, 2.f, 3.f) == approx(2.5f));
        STATIC_REQUIRE(clamp(3.5f, 2.f, 3.f) == approx(3.0f));

        STATIC_REQUIRE(mix(0.f, 10.f, 0.5f) == approx(5.f));
        STATIC_REQUIRE(mix(0.f, 10.f, false) == approx(0.f));
        STATIC_REQUIRE(mix(0.f, 10.f, true) == approx(10.f));
        STATIC_REQUIRE(step(0.5f, 0.4f) == approx(0.f));
        STATIC_REQUIRE(step(0.5f, 0.6f) == approx(1.f));
        STATIC_REQUIRE(smoothstep(0.f, 1.f, 0.1f) == approx(0.028f));

        REQUIRE_FALSE(isnan(1.f));
        REQUIRE_FALSE(isinf(1.f));

        REQUIRE(fma(2.f, 3.f, 4.f) == approx(10.f));

        {
            int out_exp{};
            REQUIRE(frexp(1.7f, &out_exp) == approx(0.85f));
            REQUIRE(out_exp == 1);
        }

        REQUIRE(ldexp(0.85f, 1) == approx(1.7f));
    }

    SECTION("Geometric Functions") {
        REQUIRE(length(10.f) == approx(10.f));
        REQUIRE(length(-10.f) == approx(10.f));

        REQUIRE(distance(5.f, 10.f) == approx(5.f));
        REQUIRE(distance(-5.f, -10.f) == approx(5.f));

        REQUIRE(dot(2.f, 5.f) == approx(10.f));
        REQUIRE(normalize(0.5f) == approx(1.f));

        REQUIRE(faceforward(1.f, 2.f, 3.f) == approx(-1.f));
        REQUIRE(reflect(1.f, 2.f) == approx(-7.f));
        REQUIRE(refract(1.f, 2.f, 1.f) == approx(-7.f));
    }
}
