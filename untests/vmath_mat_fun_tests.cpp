/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_mat_fun.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
    using namespace vmath_hpp;
}

TEST_CASE("vmath/mat_fun") {
    SECTION("Operators") {
        STATIC_REQUIRE(-mat2i(1,2,3,4) == mat2i(-1,-2,-3,-4));

        STATIC_REQUIRE(mat2i(1,2,3,4) + 2 == mat2i(3,4,5,6));
        STATIC_REQUIRE(mat2i(1,2,3,4) - 2 == mat2i(-1,0,1,2));
        STATIC_REQUIRE(mat2i(1,2,3,4) * 2 == mat2i(2,4,6,8));
        STATIC_REQUIRE(mat2i(1,2,3,4) / 2 == mat2i(0,1,1,2));

        STATIC_REQUIRE(4 + mat2i(1,2,3,4) == mat2i(5,6,7,8));
        STATIC_REQUIRE(4 - mat2i(1,2,3,4) == mat2i(3,2,1,0));
        STATIC_REQUIRE(4 * mat2i(1,2,3,4) == mat2i(4,8,12,16));
        STATIC_REQUIRE(4 / mat2i(1,2,3,4) == mat2i(4,2,1,1));

        STATIC_REQUIRE(mat2i(1,2,3,4) + mat2i(5,6,7,8) == mat2i(6,8,10,12));
        STATIC_REQUIRE(mat2i(1,2,3,4) - mat2i(5,6,7,8) == mat2i(-4,-4,-4,-4));
        STATIC_REQUIRE(mat2i(5,6,7,8) / mat2i(1,2,3,4) == mat2i(5,3,2,2));

        STATIC_REQUIRE(mat2i() * mat2i() == mat2i());
        STATIC_REQUIRE(mat3i() * mat3i() == mat3i());

        STATIC_REQUIRE(vec2i(1,2) * mat2i() == vec2i(1,2));
        STATIC_REQUIRE(vec3i(1,2,3) * mat3i() == vec3i(1,2,3));
        STATIC_REQUIRE(vec4i(1,2,3,4) * mat4i() == vec4i(1,2,3,4));
    }
}
