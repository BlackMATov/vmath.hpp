/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_vec_ops.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
}

TEST_CASE("vmath/vec_ops") {
    using namespace vmath_hpp;

    SECTION("Vector Relational Functions") {
        STATIC_REQUIRE(less(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(false, false, true));
        STATIC_REQUIRE(less_equal(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(false, true, true));

        STATIC_REQUIRE(greater(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(true, false, false));
        STATIC_REQUIRE(greater_equal(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(true, true, false));

        STATIC_REQUIRE(equal(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(false, true, false));
        STATIC_REQUIRE(not_equal(vec3i(1,1,1), vec3i(0,1,2)) == vec3b(true, false, true));

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
