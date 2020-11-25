/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_mat_ext.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "vmath_tests.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/mat_ext") {
    SECTION("units") {
        STATIC_REQUIRE(zero2x2<int> == int2x2(0,0,0,0));
        STATIC_REQUIRE(zero3x3<int> == int3x3(0,0,0,0,0,0,0,0,0));
        STATIC_REQUIRE(zero4x4<int> == int4x4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0));

        STATIC_REQUIRE(unit2x2<int> == int2x2(1,1,1,1));
        STATIC_REQUIRE(unit3x3<int> == int3x3(1,1,1,1,1,1,1,1,1));
        STATIC_REQUIRE(unit4x4<int> == int4x4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1));

        STATIC_REQUIRE(identity2x2<int> == int2x2());
        STATIC_REQUIRE(identity3x3<int> == int3x3());
        STATIC_REQUIRE(identity4x4<int> == int4x4());
    }

    SECTION("hash") {
        REQUIRE(std::hash<int2x2>{}({1,2,3,4}) == std::hash<int2x2>{}({1,2,3,4}));
        REQUIRE_FALSE(std::hash<int2x2>{}({1,2,3,4}) == std::hash<int2x2>{}({1,2,4,3}));
    }

    SECTION("cast_to") {
        constexpr auto m = cast_to<int>(float2x2{1.5f});
        STATIC_REQUIRE(m == int2x2(1));
        STATIC_REQUIRE(std::is_same_v<decltype(m)::row_type, int2>);
    }

    SECTION("row") {
        STATIC_REQUIRE(row(int2x2(1,2,3,4), 0) == int2(1,2));
        STATIC_REQUIRE(row(int2x2(1,2,3,4), 1) == int2(3,4));

        STATIC_REQUIRE(row(int2x2(), 0, {1,2}) == int2x2(1,2,0,1));
        STATIC_REQUIRE(row(int2x2(), 1, {3,4}) == int2x2(1,0,3,4));
    }

    SECTION("column") {
        STATIC_REQUIRE(column(int2x2(1,2,3,4), 0) == int2(1,3));
        STATIC_REQUIRE(column(int2x2(1,2,3,4), 1) == int2(2,4));

        STATIC_REQUIRE(column(int2x2(), 0, {2,3}) == int2x2(2,0,3,1));
        STATIC_REQUIRE(column(int2x2(), 1, {3,4}) == int2x2(1,3,0,4));
    }

    SECTION("translate") {
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * translate(1.f,2.f,3.f) == approx4(3.f,5.f,7.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * translate(float3{1.f,2.f,3.f}) == approx4(3.f,5.f,7.f,1.f));

        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * translate(translate(1.f,2.f,3.f), 1.f,2.f,3.f) == approx4(4.f,7.f,10.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * translate(translate(1.f,2.f,3.f), float3{1.f,2.f,3.f}) == approx4(4.f,7.f,10.f,1.f));
    }

    SECTION("rotate") {
        constexpr float pi = radians(180.f);
        constexpr float pi_2 = radians(90.f);

        REQUIRE(float4(2.f,3.f,4.f,1.f) * rotate(pi,0.f,0.f,1.f) == approx4(-2.f,-3.f,4.f,1.f));
        REQUIRE(float4(2.f,3.f,4.f,1.f) * rotate(pi,float3{0.f,0.f,1.f}) == approx4(-2.f,-3.f,4.f,1.f));

        REQUIRE(float4(2.f,3.f,4.f,1.f) * rotate(rotate(pi_2,0.f,0.f,1.f),pi_2,0.f,0.f,1.f) == approx4(-2.f,-3.f,4.f,1.f));
        REQUIRE(float4(2.f,3.f,4.f,1.f) * rotate(rotate(pi_2,0.f,0.f,1.f),pi_2,float3{0.f,0.f,1.f}) == approx4(-2.f,-3.f,4.f,1.f));
    }

    SECTION("scale") {
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * scale(2.f,3.f,4.f) == approx4(4.f,9.f,16.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * scale(float3{2.f,3.f,4.f}) == approx4(4.f,9.f,16.f,1.f));

        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * scale(scale(2.f,2.f,2.f), 2.f,3.f,4.f) == approx4(8.f,18.f,32.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * scale(scale(2.f,2.f,2.f), float3{2.f,3.f,4.f}) == approx4(8.f,18.f,32.f,1.f));
    }
}
