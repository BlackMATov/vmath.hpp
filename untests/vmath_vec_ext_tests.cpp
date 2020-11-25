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
    SECTION("hash") {
        REQUIRE(std::hash<vec2i>{}({1,2}) == std::hash<vec2i>{}({1,2}));
        REQUIRE_FALSE(std::hash<vec2i>{}({1,2}) == std::hash<vec2i>{}({2,1}));

        REQUIRE(std::hash<vec3i>{}({1,2,3}) == std::hash<vec3i>{}({1,2,3}));
        REQUIRE_FALSE(std::hash<vec3i>{}({1,2,3}) == std::hash<vec3i>{}({3,2,1}));

        REQUIRE(std::hash<vec4i>{}({1,2,3,4}) == std::hash<vec4i>{}({1,2,3,4}));
        REQUIRE_FALSE(std::hash<vec4i>{}({1,2,3,4}) == std::hash<vec4i>{}({3,2,1,4}));
    }

    SECTION("cast_to") {
        constexpr auto v = cast_to<int>(vec2f{1.5f});
        STATIC_REQUIRE(v == vec2i(1));
        STATIC_REQUIRE(std::is_same_v<decltype(v)::value_type, int>);
    }

    SECTION("component") {
        STATIC_REQUIRE(component(vec2i{1,2}, 0) == 1);
        STATIC_REQUIRE(component(vec2i{1,2}, 1) == 2);

        STATIC_REQUIRE(component(vec2i{0,0}, 0, 1) == vec2i{1,0});
        STATIC_REQUIRE(component(vec2i{0,0}, 1, 2) == vec2i{0,2});
    }
}
