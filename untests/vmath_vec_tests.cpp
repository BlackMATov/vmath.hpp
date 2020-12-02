/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"
#include "doctest/doctest.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/vec") {
    SUBCASE("size/sizeof") {
        STATIC_REQUIRE(int2{}.size == 2);
        STATIC_REQUIRE(int3{}.size == 3);
        STATIC_REQUIRE(int4{}.size == 4);

        STATIC_REQUIRE(sizeof(int2{}) == sizeof(int) * 2);
        STATIC_REQUIRE(sizeof(int3{}) == sizeof(int) * 3);
        STATIC_REQUIRE(sizeof(int4{}) == sizeof(int) * 4);
    }

    SUBCASE("guides") {
        STATIC_REQUIRE(vec{1,2}.size == 2);

        STATIC_REQUIRE(vec{1,2,3}.size == 3);
        STATIC_REQUIRE(vec{{1,2},3}.size == 3);
        STATIC_REQUIRE(vec{1,{2,3}}.size == 3);

        STATIC_REQUIRE(vec{1,2,3,4}.size == 4);
        STATIC_REQUIRE(vec{vec{1,2},3,4}.size == 4);
        STATIC_REQUIRE(vec{1,vec{2,3},4}.size == 4);
        STATIC_REQUIRE(vec{1,2,vec{3,4}}.size == 4);
        STATIC_REQUIRE(vec{vec{1,2},vec{3,4}}.size == 4);
        STATIC_REQUIRE(vec{vec{1,2,3},4}.size == 4);
        STATIC_REQUIRE(vec{1,vec{2,3,4}}.size == 4);
    }

    SUBCASE("ctors") {
        {
            STATIC_REQUIRE(int2().x == 0);
            STATIC_REQUIRE(int2().y == 0);

            STATIC_REQUIRE(int2(1).x == 1);
            STATIC_REQUIRE(int2(1).y == 1);

            STATIC_REQUIRE(int2(1,2).x == 1);
            STATIC_REQUIRE(int2(1,2).y == 2);
        }
        {
            constexpr int2 v(1,2);
            constexpr int2 v2 = v;
            STATIC_REQUIRE(v2 == int2(1,2));
        }
        {
            constexpr int2 v(1,2);
            constexpr int2 v2 = std::move(v);
            STATIC_REQUIRE(v2 == int2(1,2));
        }
        {
            STATIC_REQUIRE(int2(1) == int2(1,1));
            STATIC_REQUIRE(int2(1,2) == int2(1,2));
            STATIC_REQUIRE(int2(int2(1,2)) == int2(1,2));
            STATIC_REQUIRE(int2(int3(1,2,3)) == int2(1,2));
            STATIC_REQUIRE(int2(int4(1,2,3,4)) == int2(1,2));

            STATIC_REQUIRE(int3(1) == int3(1,1,1));
            STATIC_REQUIRE(int3(1,2,3) == int3(1,2,3));
            STATIC_REQUIRE(int3(int2(1,2),3) == int3(1,2,3));
            STATIC_REQUIRE(int3(1,int2(2,3)) == int3(1,2,3));
            STATIC_REQUIRE(int3(int3(1,2,3)) == int3(1,2,3));
            STATIC_REQUIRE(int3(int4(1,2,3,4)) == int3(1,2,3));

            STATIC_REQUIRE(int4(1) == int4(1,1,1,1));
            STATIC_REQUIRE(int4(1,2,3,4) == int4(1,2,3,4));
            STATIC_REQUIRE(int4(int2(1,2),3,4) == int4(1,2,3,4));
            STATIC_REQUIRE(int4(1,int2(2,3),4) == int4(1,2,3,4));
            STATIC_REQUIRE(int4(1,2,int2(3,4)) == int4(1,2,3,4));
            STATIC_REQUIRE(int4(int2(1,2),int2(3,4)) == int4(1,2,3,4));
            STATIC_REQUIRE(int4(int3(1,2,3),4) == int4(1,2,3,4));
            STATIC_REQUIRE(int4(1,int3(2,3,4)) == int4(1,2,3,4));
        }
    }

    SUBCASE("operator=") {
        {
            int2 v(1,2);
            int2 v2;
            v2 = v;
            REQUIRE(v2 == int2(1,2));
        }
        {
            int2 v(1,2);
            int2 v2;
            v2 = std::move(v);
            REQUIRE(v2 == int2(1,2));
        }
    }

    SUBCASE("swap") {
        {
            int2 v1(1,2);
            int2 v2(4,5);
            v1.swap(v2);
            REQUIRE(v1 == int2(4,5));
            REQUIRE(v2 == int2(1,2));
        }
        {
            int2 v1(1,2);
            int2 v2(4,5);
            swap(v1, v2);
            REQUIRE(v1 == int2(4,5));
            REQUIRE(v2 == int2(1,2));
        }
    }

    SUBCASE("operator[]") {
        {
            STATIC_REQUIRE(int2(1,2).x == 1);
            STATIC_REQUIRE(int2(1,2).y == 2);

            STATIC_REQUIRE(int3(1,2,3).x == 1);
            STATIC_REQUIRE(int3(1,2,3).y == 2);
            STATIC_REQUIRE(int3(1,2,3).z == 3);

            STATIC_REQUIRE(int4(1,2,3,4).x == 1);
            STATIC_REQUIRE(int4(1,2,3,4).y == 2);
            STATIC_REQUIRE(int4(1,2,3,4).z == 3);
            STATIC_REQUIRE(int4(1,2,3,4).w == 4);
        }
        {
            STATIC_REQUIRE(int2(1,2)[0] == 1);
            STATIC_REQUIRE(int2(1,2)[1] == 2);
        }
        {
            int2 v;
            v.x = 1;
            v.y = 2;
            REQUIRE(v == int2(1,2));
        }
        {
            int3 v;
            v.x = 1;
            v.y = 2;
            v.z = 3;
            REQUIRE(v == int3(1,2,3));
        }
        {
            int4 v;
            v.x = 1;
            v.y = 2;
            v.z = 3;
            v.w = 4;
            REQUIRE(v == int4(1,2,3,4));
        }
    }

    SUBCASE("at") {
        STATIC_REQUIRE(int2(1,2).at(0) == 1);
        STATIC_REQUIRE(int2(1,2).at(1) == 2);
        REQUIRE_THROWS_AS((void)int2(1,2).at(2), std::out_of_range);
    }

    SUBCASE("operator==/operator!=") {
        STATIC_REQUIRE(int2(1,2) == int2(1,2));
        STATIC_REQUIRE_FALSE(int2(1,2) == int2(2,2));
        STATIC_REQUIRE_FALSE(int2(1,2) == int2(1,3));

        STATIC_REQUIRE_FALSE(int2(1,2) != int2(1,2));
        STATIC_REQUIRE(int2(1,2) != int2(2,2));
        STATIC_REQUIRE(int2(1,2) != int2(1,3));
    }

    SUBCASE("operator<") {
        STATIC_REQUIRE_FALSE(int2(1,2) < int2(1,2));

        STATIC_REQUIRE(int2(1,1) < int2(1,2));
        STATIC_REQUIRE_FALSE(int2(1,2) < int2(1,1));

        STATIC_REQUIRE(int2(0,3) < int2(1,2));
        STATIC_REQUIRE_FALSE(int2(1,2) < int2(0,3));
    }
}
