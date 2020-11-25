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
    SECTION("cast_to") {
        constexpr auto m = cast_to<int>(mat2f{1.5f});
        STATIC_REQUIRE(m == mat2i(1));
        STATIC_REQUIRE(std::is_same_v<decltype(m)::row_type, vec2i>);
    }

    SECTION("row") {
        STATIC_REQUIRE(row(mat2i(1,2,3,4), 0) == vec2i(1,2));
        STATIC_REQUIRE(row(mat2i(1,2,3,4), 1) == vec2i(3,4));

        STATIC_REQUIRE(row(mat2i(), 0, {1,2}) == mat2i(1,2,0,1));
        STATIC_REQUIRE(row(mat2i(), 1, {3,4}) == mat2i(1,0,3,4));
    }

    SECTION("column") {
        STATIC_REQUIRE(column(mat2i(1,2,3,4), 0) == vec2i(1,3));
        STATIC_REQUIRE(column(mat2i(1,2,3,4), 1) == vec2i(2,4));

        STATIC_REQUIRE(column(mat2i(), 0, {2,3}) == mat2i(2,0,3,1));
        STATIC_REQUIRE(column(mat2i(), 1, {3,4}) == mat2i(1,3,0,4));
    }

    SECTION("identity") {
        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * identity<float>() == approx4(2.f,3.f,4.f,1.f));
        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * identity<float>() == approx4(2.f,3.f,4.f,1.f));
    }

    SECTION("translate") {
        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * translate(1.f,2.f,3.f) == approx4(3.f,5.f,7.f,1.f));
        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * translate(vec3f{1.f,2.f,3.f}) == approx4(3.f,5.f,7.f,1.f));

        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * translate(translate(1.f,2.f,3.f), 1.f,2.f,3.f) == approx4(4.f,7.f,10.f,1.f));
        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * translate(translate(1.f,2.f,3.f), vec3f{1.f,2.f,3.f}) == approx4(4.f,7.f,10.f,1.f));
    }

    SECTION("rotate") {
        constexpr float pi = radians(180.f);
        constexpr float pi_2 = radians(90.f);

        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * rotate(pi,0.f,0.f,1.f) == approx4(-2.f,-3.f,4.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * rotate(pi,vec3f{0.f,0.f,1.f}) == approx4(-2.f,-3.f,4.f,1.f));

        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * rotate(rotate(pi_2,0.f,0.f,1.f),pi_2,0.f,0.f,1.f) == approx4(-2.f,-3.f,4.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * rotate(rotate(pi_2,0.f,0.f,1.f),pi_2,vec3f{0.f,0.f,1.f}) == approx4(-2.f,-3.f,4.f,1.f));
    }

    SECTION("scale") {
        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * scale(2.f,3.f,4.f) == approx4(4.f,9.f,16.f,1.f));
        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * scale(vec3f{2.f,3.f,4.f}) == approx4(4.f,9.f,16.f,1.f));

        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * scale(scale(2.f,2.f,2.f), 2.f,3.f,4.f) == approx4(8.f,18.f,32.f,1.f));
        STATIC_REQUIRE(vec4f(2.f,3.f,4.f,1.f) * scale(scale(2.f,2.f,2.f), vec3f{2.f,3.f,4.f}) == approx4(8.f,18.f,32.f,1.f));
    }
}
