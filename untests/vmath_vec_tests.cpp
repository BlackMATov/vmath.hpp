/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_vec.hpp>
#include <vmath.hpp/vmath_vec_fun.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
}

TEST_CASE("vmath/vec") {
    using namespace vmath_hpp;

    SECTION("size/sizeof") {
        STATIC_REQUIRE(vec2i{}.size == 2);
        STATIC_REQUIRE(vec3i{}.size == 3);
        STATIC_REQUIRE(vec4i{}.size == 4);

        STATIC_REQUIRE(sizeof(vec2i{}) == sizeof(int) * 2);
        STATIC_REQUIRE(sizeof(vec3i{}) == sizeof(int) * 3);
        STATIC_REQUIRE(sizeof(vec4i{}) == sizeof(int) * 4);
    }

    SECTION("ctors") {
        {
            STATIC_REQUIRE(vec2i().x == 0);
            STATIC_REQUIRE(vec2i().y == 0);

            STATIC_REQUIRE(vec2i(1).x == 1);
            STATIC_REQUIRE(vec2i(1).y == 1);

            STATIC_REQUIRE(vec2i(1,2).x == 1);
            STATIC_REQUIRE(vec2i(1,2).y == 2);
        }
        {
            constexpr vec2i v(1,2);
            constexpr vec2i v2 = v;
            STATIC_REQUIRE(v2 == vec2i(1,2));
        }
        {
            constexpr vec2i v(1,2);
            constexpr vec2i v2 = std::move(v);
            STATIC_REQUIRE(v2 == vec2i(1,2));
        }
        {
            STATIC_REQUIRE(vec2i(1) == vec2i(1,1));
            STATIC_REQUIRE(vec2i(1,2) == vec2i(1,2));
            STATIC_REQUIRE(vec2i(vec2i(1,2)) == vec2i(1,2));
            STATIC_REQUIRE(vec2i(vec3i(1,2,3)) == vec2i(1,2));
            STATIC_REQUIRE(vec2i(vec4i(1,2,3,4)) == vec2i(1,2));

            STATIC_REQUIRE(vec3i(1) == vec3i(1,1,1));
            STATIC_REQUIRE(vec3i(1,2,3) == vec3i(1,2,3));
            STATIC_REQUIRE(vec3i(vec2i(1,2),3) == vec3i(1,2,3));
            STATIC_REQUIRE(vec3i(1,vec2i(2,3)) == vec3i(1,2,3));
            STATIC_REQUIRE(vec3i(vec3i(1,2,3)) == vec3i(1,2,3));
            STATIC_REQUIRE(vec3i(vec4i(1,2,3,4)) == vec3i(1,2,3));

            STATIC_REQUIRE(vec4i(1) == vec4i(1,1,1,1));
            STATIC_REQUIRE(vec4i(1,2,3,4) == vec4i(1,2,3,4));
            STATIC_REQUIRE(vec4i(vec2i(1,2),3,4) == vec4i(1,2,3,4));
            STATIC_REQUIRE(vec4i(1,vec2i(2,3),4) == vec4i(1,2,3,4));
            STATIC_REQUIRE(vec4i(1,2,vec2i(3,4)) == vec4i(1,2,3,4));
            STATIC_REQUIRE(vec4i(vec2i(1,2),vec2i(3,4)) == vec4i(1,2,3,4));
            STATIC_REQUIRE(vec4i(vec3i(1,2,3),4) == vec4i(1,2,3,4));
            STATIC_REQUIRE(vec4i(1,vec3i(2,3,4)) == vec4i(1,2,3,4));
        }
    }

    SECTION("operator=") {
        {
            vec2i v(1,2);
            vec2i v2;
            v2 = v;
            REQUIRE(v2 == vec2i(1,2));
        }
        {
            vec2i v(1,2);
            vec2i v2;
            v2 = std::move(v);
            REQUIRE(v2 == vec2i(1,2));
        }
    }

    SECTION("swap") {
        {
            vec2i v1(1,2);
            vec2i v2(4,5);
            v1.swap(v2);
            REQUIRE(v1 == vec2i(4,5));
            REQUIRE(v2 == vec2i(1,2));
        }
        {
            vec2i v1(1,2);
            vec2i v2(4,5);
            swap(v1, v2);
            REQUIRE(v1 == vec2i(4,5));
            REQUIRE(v2 == vec2i(1,2));
        }
    }

    SECTION("operator[]") {
        {
            STATIC_REQUIRE(vec2i(1,2).x == 1);
            STATIC_REQUIRE(vec2i(1,2).y == 2);

            STATIC_REQUIRE(vec3i(1,2,3).x == 1);
            STATIC_REQUIRE(vec3i(1,2,3).y == 2);
            STATIC_REQUIRE(vec3i(1,2,3).z == 3);

            STATIC_REQUIRE(vec4i(1,2,3,4).x == 1);
            STATIC_REQUIRE(vec4i(1,2,3,4).y == 2);
            STATIC_REQUIRE(vec4i(1,2,3,4).z == 3);
            STATIC_REQUIRE(vec4i(1,2,3,4).w == 4);
        }
        {
            STATIC_REQUIRE(vec2i(1,2)[0] == 1);
            STATIC_REQUIRE(vec2i(1,2)[1] == 2);
        }
        {
            vec2i v;
            v.x = 1;
            v.y = 2;
            REQUIRE(v == vec2i(1,2));
        }
        {
            vec3i v;
            v.x = 1;
            v.y = 2;
            v.z = 3;
            REQUIRE(v == vec3i(1,2,3));
        }
        {
            vec4i v;
            v.x = 1;
            v.y = 2;
            v.z = 3;
            v.w = 4;
            REQUIRE(v == vec4i(1,2,3,4));
        }
    }

    SECTION("at") {
        STATIC_REQUIRE(vec2i(1,2).at(0) == 1);
        STATIC_REQUIRE(vec2i(1,2).at(1) == 2);
        REQUIRE_THROWS_AS(vec2i(1,2).at(2), std::out_of_range);
    }

    SECTION("operator==/operator!=") {
        STATIC_REQUIRE(vec2i(1,2) == vec2i(1,2));
        STATIC_REQUIRE_FALSE(vec2i(1,2) == vec2i(2,2));
        STATIC_REQUIRE_FALSE(vec2i(1,2) == vec2i(1,3));

        STATIC_REQUIRE_FALSE(vec2i(1,2) != vec2i(1,2));
        STATIC_REQUIRE(vec2i(1,2) != vec2i(2,2));
        STATIC_REQUIRE(vec2i(1,2) != vec2i(1,3));
    }

    SECTION("operator<") {
        STATIC_REQUIRE_FALSE(vec2i(1,2) < vec2i(1,2));

        STATIC_REQUIRE(vec2i(1,1) < vec2i(1,2));
        STATIC_REQUIRE_FALSE(vec2i(1,2) < vec2i(1,1));

        STATIC_REQUIRE(vec2i(0,3) < vec2i(1,2));
        STATIC_REQUIRE_FALSE(vec2i(1,2) < vec2i(0,3));
    }
}
