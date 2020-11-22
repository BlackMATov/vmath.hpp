/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_vec_fun.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
    using namespace vmath_hpp;

    template < typename T >
    class approx2 {
    public:
        constexpr explicit approx2(T v) : value_(v) {}
        constexpr explicit approx2(T x, T y) : value_(x, y) {}

        friend constexpr bool operator==(const vec<T, 2>& l, const approx2& r) {
            return (r.value_.x < l.x + epsilon)
                && (l.x < r.value_.x + epsilon)
                && (r.value_.y < l.y + epsilon)
                && (l.y < r.value_.y + epsilon);
        }
    private:
        vec<T, 2> value_;
        static constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
    };

    template < typename T >
    class approx3 {
    public:
        constexpr explicit approx3(T v) : value_(v) {}
        constexpr explicit approx3(T x, T y, T z) : value_(x, y, z) {}

        friend constexpr bool operator==(const vec<T, 3>& l, const approx3& r) {
            return (r.value_.x < l.x + epsilon)
                && (l.x < r.value_.x + epsilon)
                && (r.value_.y < l.y + epsilon)
                && (l.y < r.value_.y + epsilon)
                && (r.value_.z < l.z + epsilon)
                && (l.z < r.value_.z + epsilon);
        }
    private:
        vec<T, 3> value_;
        static constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
    };
}

TEST_CASE("vmath/vec_fun") {
    SECTION("Operators") {
        STATIC_REQUIRE(-vec2i(1,-2) == vec2i(-1,2));

        STATIC_REQUIRE(vec2i(1,2) + 3 == vec2i(4,5));
        STATIC_REQUIRE(vec2i(1,2) - 3 == vec2i(-2,-1));
        STATIC_REQUIRE(vec2i(1,2) * 3 == vec2i(3,6));
        STATIC_REQUIRE(vec2i(2,4) / 2 == vec2i(1,2));

        STATIC_REQUIRE(3 + vec2i(1,2) == vec2i(4,5));
        STATIC_REQUIRE(3 - vec2i(1,2) == vec2i(2,1));
        STATIC_REQUIRE(3 * vec2i(1,2) == vec2i(3,6));
        STATIC_REQUIRE(4 / vec2i(2,4) == vec2i(2,1));

        STATIC_REQUIRE(vec2i(1,2) + vec2i(3,4) == vec2i(4,6));
        STATIC_REQUIRE(vec2i(1,2) - vec2i(3,4) == vec2i(-2,-2));
        STATIC_REQUIRE(vec2i(1,2) * vec2i(3,4) == vec2i(3,8));
        STATIC_REQUIRE(vec2i(3,4) / vec2i(1,2) == vec2i(3,2));
    }

    SECTION("Angle and Trigonometry Functions") {
        STATIC_REQUIRE(radians(degrees(vec2f(12.13f))) == approx2(12.13f));
        STATIC_REQUIRE(degrees(radians(vec2f(12.13f))) == approx2(12.13f));

        sin(vec2f(1.f));
        cos(vec2f(1.f));
        tan(vec2f(1.f));

        asin(vec2f(1.f));
        acos(vec2f(1.f));
        atan(vec2f(1.f));
        atan2(vec2f(1.f), vec2f(1.f));

        sinh(vec2f(1.f));
        cosh(vec2f(1.f));
        tanh(vec2f(1.f));

        asinh(vec2f(1.f));
        acosh(vec2f(1.f));
        atanh(vec2f(1.f));
    }

    SECTION("Exponential Functions") {
        pow(vec2f(1.f), vec2f(2.f));
        exp(vec2f(1.f));
        log(vec2f(1.f));
        exp2(vec2f(1.f));
        log2(vec2f(1.f));
        sqrt(vec2f(1.f));
        invsqrt(vec2f(1.f));
    }

    SECTION("Common Functions") {
        REQUIRE(abs(vec2f(1.f, -1.f)) == approx2(1.f,1.f));
        REQUIRE(sign(vec3f(1.f, -1.f, 0.f)) == approx3(1.f,-1.f,0.f));

        floor(vec2f(1.f, -1.f));
        trunc(vec2f(1.f, -1.f));
        round(vec2f(1.f, -1.f));
        ceil(vec2f(1.f, -1.f));
        fract(vec2f(1.f, -1.f));

        REQUIRE(fmod(vec2f(1.7f), 1.2f) == approx2(0.5f));
        REQUIRE(fmod(vec2f(1.7f), vec2f(1.2f)) == approx2(0.5f));

        {
            vec2f out_i{};
            REQUIRE(modf(vec2f(1.7f), &out_i) == approx2(0.7f));
            REQUIRE(out_i.x == Approx(1.f));
        }

        STATIC_REQUIRE(min(vec2i(1,2), 1) == vec2i(1,1));
        STATIC_REQUIRE(min(vec2i(1,1), vec2i(0,2)) == vec2i(0,1));

        STATIC_REQUIRE(max(vec2i(1,2), 1) == vec2i(1,2));
        STATIC_REQUIRE(max(vec2i(1,1), vec2i(0,2)) == vec2i(1,2));

        STATIC_REQUIRE(clamp(vec2i(1,2), 0, 1) == vec2i(1,1));
        STATIC_REQUIRE(clamp(vec2i(1,2), vec2i(0), vec2i(1)) == vec2i(1,1));

        STATIC_REQUIRE(mix(vec2f(0.f), vec2f(10.f), 0.5f) == approx2(5.f));
        STATIC_REQUIRE(mix(vec2f(0.f), vec2f(10.f), vec2f(0.5f)) == approx2(5.f));

        STATIC_REQUIRE(mix(vec2f(0.f), vec2f(10.f), true) == approx2(10.f));
        STATIC_REQUIRE(mix(vec2f(0.f), vec2f(10.f), false) == approx2(0.f));

        STATIC_REQUIRE(mix(vec2f(0.f,5.f), vec2f(10.f,20.f), vec2f(true,false)) == approx2(10.f, 5.f));
        STATIC_REQUIRE(mix(vec2f(0.f,5.f), vec2f(10.f,20.f), vec2f(true,false)) == approx2(10.f, 5.f));

        STATIC_REQUIRE(step(0.5f, vec2f(0.4f)) == approx2(0.f));
        STATIC_REQUIRE(step(0.5f, vec2f(0.6f)) == approx2(1.f));
        STATIC_REQUIRE(step(vec2f(0.5f), vec2f(0.4f)) == approx2(0.f));
        STATIC_REQUIRE(step(vec2f(0.5f), vec2f(0.6f)) == approx2(1.f));

        STATIC_REQUIRE(smoothstep(0.f, 1.f, vec2f(0.1f)) == approx2(0.028f));
        STATIC_REQUIRE(smoothstep(vec2f(0.f), vec2f(1.f), vec2f(0.1f)) == approx2(0.028f));

        REQUIRE_FALSE(isnan(vec2f(1.f)).x);
        REQUIRE_FALSE(isinf(vec2f(1.f)).x);

        REQUIRE_FALSE(fma(vec2f(2.f), vec2f(3.f), vec2f(4.f)).x == Approx(12.f));

        {
            vec2i out_exp{};
            REQUIRE(frexp(vec2f(1.7f), &out_exp).x == Approx(0.85f));
            REQUIRE(out_exp == vec2i(1));
        }

        REQUIRE(ldexp(vec2f(0.85f), vec2i(1)).x == Approx(1.7f));
    }

    SECTION("Geometric Functions") {
        REQUIRE(length(vec2f(10.f,0.f)) == Approx(10.f));
        REQUIRE(length(vec2f(-10.f,0.f)) == Approx(10.f));

        REQUIRE(distance(vec2f(5.f,0.f), vec2f(10.f,0.f)) == Approx(5.f));
        REQUIRE(distance(vec2f(-5.f,0.f), vec2f(-10.f,0.f)) == Approx(5.f));

        STATIC_REQUIRE(dot(vec2i(1,2),vec2i(3,4)) == 11);
        STATIC_REQUIRE(cross(vec3i(1,0,0),vec3i(0,1,0)) == vec3i(0,0,1));
        REQUIRE(normalize(vec2f(0.5f,0.f)).x == Approx(1.f));

        REQUIRE(faceforward(vec2f(1.f), vec2f(2.f), vec2f(3.f)).x == Approx(-1.f));
        REQUIRE(reflect(vec2f(1.f), vec2f(2.f)).x == Approx(-15.f));
        REQUIRE(refract(vec2f(1.f), vec2f(2.f), 1.f).x == Approx(-15.f));
    }

    SECTION("Vector Relational Functions") {
        STATIC_REQUIRE(less(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(false, false, true));
        STATIC_REQUIRE(less_equal(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(false, true, true));

        STATIC_REQUIRE(greater(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(true, false, false));
        STATIC_REQUIRE(greater_equal(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(true, true, false));

        STATIC_REQUIRE(equal_to(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(false, true, false));
        STATIC_REQUIRE(not_equal_to(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(true, false, true));

        STATIC_REQUIRE_FALSE(any(vec2b(false, false)));
        STATIC_REQUIRE(any(vec2b(true, false)));
        STATIC_REQUIRE(any(vec2b(false, true)));
        STATIC_REQUIRE(any(vec2b(true, true)));

        STATIC_REQUIRE_FALSE(all(vec2b(false, false)));
        STATIC_REQUIRE_FALSE(all(vec2b(true, false)));
        STATIC_REQUIRE_FALSE(all(vec2b(false, true)));
        STATIC_REQUIRE(all(vec2b(true, true)));

        STATIC_REQUIRE(not_(vec2b(false, false)) == vec2b(true, true));
        STATIC_REQUIRE(not_(vec2b(true, false)) == vec2b(false, true));
        STATIC_REQUIRE(not_(vec2b(false, true)) == vec2b(true, false));
        STATIC_REQUIRE(not_(vec2b(true, true)) == vec2b(false, false));
    }
}
