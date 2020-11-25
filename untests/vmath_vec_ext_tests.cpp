/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_vec_ext.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "vmath_tests.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/vec_ext") {
    SECTION("units") {
        STATIC_REQUIRE(zero2<int> == int2(0,0));
        STATIC_REQUIRE(zero3<int> == int3(0,0,0));
        STATIC_REQUIRE(zero4<int> == int4(0,0,0,0));

        STATIC_REQUIRE(unit2<int> == int2(1,1));
        STATIC_REQUIRE(unit2_x<int> == int2(1,0));
        STATIC_REQUIRE(unit2_y<int> == int2(0,1));

        STATIC_REQUIRE(unit3<int> == int3(1,1,1));
        STATIC_REQUIRE(unit3_x<int> == int3(1,0,0));
        STATIC_REQUIRE(unit3_y<int> == int3(0,1,0));
        STATIC_REQUIRE(unit3_z<int> == int3(0,0,1));

        STATIC_REQUIRE(unit4<int> == int4(1,1,1,1));
        STATIC_REQUIRE(unit4_x<int> == int4(1,0,0,0));
        STATIC_REQUIRE(unit4_y<int> == int4(0,1,0,0));
        STATIC_REQUIRE(unit4_z<int> == int4(0,0,1,0));
        STATIC_REQUIRE(unit4_w<int> == int4(0,0,0,1));
    }

    SECTION("hash") {
        REQUIRE(std::hash<int2>{}({1,2}) == std::hash<int2>{}({1,2}));
        REQUIRE_FALSE(std::hash<int2>{}({1,2}) == std::hash<int2>{}({2,1}));

        REQUIRE(std::hash<int3>{}({1,2,3}) == std::hash<int3>{}({1,2,3}));
        REQUIRE_FALSE(std::hash<int3>{}({1,2,3}) == std::hash<int3>{}({3,2,1}));

        REQUIRE(std::hash<int4>{}({1,2,3,4}) == std::hash<int4>{}({1,2,3,4}));
        REQUIRE_FALSE(std::hash<int4>{}({1,2,3,4}) == std::hash<int4>{}({3,2,1,4}));
    }

    SECTION("cast_to") {
        constexpr auto v = cast_to<int>(float2{1.5f});
        STATIC_REQUIRE(v == int2(1));
        STATIC_REQUIRE(std::is_same_v<decltype(v)::value_type, int>);
    }

    SECTION("component") {
        STATIC_REQUIRE(component(int2{1,2}, 0) == 1);
        STATIC_REQUIRE(component(int2{1,2}, 1) == 2);

        STATIC_REQUIRE(component(int2{0,0}, 0, 1) == int2{1,0});
        STATIC_REQUIRE(component(int2{0,0}, 1, 2) == int2{0,2});
    }

    SECTION("angle") {
        REQUIRE(angle(float2(2.f,0.f), float2(0.f,1.f)) == Approx(radians(90.f)));
        REQUIRE(angle(float2(0.f,3.f), float2(1.f,0.f)) == Approx(radians(90.f)));
        REQUIRE(angle(float2(0.5f,0.f), float2(-1.f,0.f)) == Approx(radians(180.f)));
        REQUIRE(angle(float2(-0.2f,0.f), float2(1.f,0.f)) == Approx(radians(180.f)));
        REQUIRE(angle(float3(0.f,2.f,0.f), float3(0.f,0.f,1.f)) == Approx(radians(90.f)));
        REQUIRE(angle(float3(0.f,0.f,3.f), float3(0.f,1.f,0.f)) == Approx(radians(90.f)));
    }
}
