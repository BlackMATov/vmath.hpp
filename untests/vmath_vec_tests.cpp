/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/vec") {
    SUBCASE("size/sizeof") {
        STATIC_CHECK(int2{}.size == 2);
        STATIC_CHECK(int3{}.size == 3);
        STATIC_CHECK(int4{}.size == 4);

        STATIC_CHECK(sizeof(int2{}) == sizeof(int) * 2);
        STATIC_CHECK(sizeof(int3{}) == sizeof(int) * 3);
        STATIC_CHECK(sizeof(int4{}) == sizeof(int) * 4);
    }

    SUBCASE("guides") {
        STATIC_CHECK(vec{1,2}.size == 2);

        STATIC_CHECK(vec{1,2,3}.size == 3);
        STATIC_CHECK(vec{{1,2},3}.size == 3);
        STATIC_CHECK(vec{1,{2,3}}.size == 3);

        STATIC_CHECK(vec{1,2,3,4}.size == 4);
        STATIC_CHECK(vec{vec{1,2},3,4}.size == 4);
        STATIC_CHECK(vec{1,vec{2,3},4}.size == 4);
        STATIC_CHECK(vec{1,2,vec{3,4}}.size == 4);
        STATIC_CHECK(vec{vec{1,2},vec{3,4}}.size == 4);
        STATIC_CHECK(vec{vec{1,2,3},4}.size == 4);
        STATIC_CHECK(vec{1,vec{2,3,4}}.size == 4);
    }

    SUBCASE("ctors") {
        {
            vec<int, 2> i2;
            CHECK(i2.x == 0);
            CHECK(i2.y == 0);

            vec<int, 3> i3;
            CHECK(i3.x == 0);
            CHECK(i3.y == 0);
            CHECK(i3.z == 0);

            vec<int, 4> i4;
            CHECK(i4.x == 0);
            CHECK(i4.y == 0);
            CHECK(i4.z == 0);
            CHECK(i4.w == 0);
        }
        {
            STATIC_CHECK(int2().x == 0);
            STATIC_CHECK(int2().y == 0);

            STATIC_CHECK(int2(1).x == 1);
            STATIC_CHECK(int2(1).y == 1);

            STATIC_CHECK(int2(1,2).x == 1);
            STATIC_CHECK(int2(1,2).y == 2);
        }
        {
            constexpr int2 v(1,2);
            constexpr int2 v2 = v;
            STATIC_CHECK(v2 == int2(1,2));
        }
        {
            constexpr int2 v(1,2);
            constexpr int2 v2 = std::move(v);
            STATIC_CHECK(v2 == int2(1,2));
        }
        {
            STATIC_CHECK(int2(1) == int2(1,1));
            STATIC_CHECK(int2(1,2) == int2(1,2));
            STATIC_CHECK(int2(int2(1,2)) == int2(1,2));
            STATIC_CHECK(int2(int3(1,2,3)) == int2(1,2));
            STATIC_CHECK(int2(int4(1,2,3,4)) == int2(1,2));

            STATIC_CHECK(int3(1) == int3(1,1,1));
            STATIC_CHECK(int3(1,2,3) == int3(1,2,3));
            STATIC_CHECK(int3(int2(1,2),3) == int3(1,2,3));
            STATIC_CHECK(int3(1,int2(2,3)) == int3(1,2,3));
            STATIC_CHECK(int3(int3(1,2,3)) == int3(1,2,3));
            STATIC_CHECK(int3(int4(1,2,3,4)) == int3(1,2,3));

            STATIC_CHECK(int4(1) == int4(1,1,1,1));
            STATIC_CHECK(int4(1,2,3,4) == int4(1,2,3,4));
            STATIC_CHECK(int4(int2(1,2),3,4) == int4(1,2,3,4));
            STATIC_CHECK(int4(1,int2(2,3),4) == int4(1,2,3,4));
            STATIC_CHECK(int4(1,2,int2(3,4)) == int4(1,2,3,4));
            STATIC_CHECK(int4(int2(1,2),int2(3,4)) == int4(1,2,3,4));
            STATIC_CHECK(int4(int3(1,2,3),4) == int4(1,2,3,4));
            STATIC_CHECK(int4(1,int3(2,3,4)) == int4(1,2,3,4));
        }
    }

    SUBCASE("operator=") {
        {
            int2 v(1,2);
            int2 v2;
            v2 = v;
            CHECK(v2 == int2(1,2));
        }
        {
            int2 v(1,2);
            int2 v2;
            v2 = std::move(v);
            CHECK(v2 == int2(1,2));
        }
    }

    SUBCASE("swap") {
        {
            int2 v1(1,2);
            int2 v2(4,5);
            v1.swap(v2);
            CHECK(v1 == int2(4,5));
            CHECK(v2 == int2(1,2));
        }
        {
            int2 v1(1,2);
            int2 v2(4,5);
            swap(v1, v2);
            CHECK(v1 == int2(4,5));
            CHECK(v2 == int2(1,2));
        }
    }

    SUBCASE("iter") {
        {
            int2 v{1,2};

            CHECK(*v.begin() == 1);
            CHECK(*(v.begin() + 1) == 2);
            CHECK(*(v.end() - 1) == 2);
            CHECK(*(v.end() - 2) == 1);
            CHECK(v.begin() + 2 == v.end());
            CHECK(v.end() - 2 == v.begin());

            CHECK(*v.cbegin() == 1);
            CHECK(*(v.cbegin() + 1) == 2);
            CHECK(*(v.cend() - 1) == 2);
            CHECK(*(v.cend() - 2) == 1);
            CHECK(v.cbegin() + 2 == v.cend());
            CHECK(v.cend() - 2 == v.cbegin());

            CHECK(*v.rbegin() == 2);
            CHECK(*(v.rbegin() + 1) == 1);
            CHECK(*(v.rend() - 1) == 1);
            CHECK(*(v.rend() - 2) == 2);
            CHECK(v.rbegin() + 2 == v.rend());
            CHECK(v.rend() - 2 == v.rbegin());

            CHECK(*v.crbegin() == 2);
            CHECK(*(v.crbegin() + 1) == 1);
            CHECK(*(v.crend() - 1) == 1);
            CHECK(*(v.crend() - 2) == 2);
            CHECK(v.crbegin() + 2 == v.crend());
            CHECK(v.crend() - 2 == v.crbegin());

            *v.begin() = 3;
            CHECK(v == int2{3,2});
            *v.rbegin() = 4;
            CHECK(v == int2{3,4});
        }
        {
            const int2 v{1,2};

            CHECK(*v.begin() == 1);
            CHECK(*(v.begin() + 1) == 2);
            CHECK(*(v.end() - 1) == 2);
            CHECK(*(v.end() - 2) == 1);
            CHECK(v.begin() + 2 == v.end());
            CHECK(v.end() - 2 == v.begin());

            CHECK(*v.cbegin() == 1);
            CHECK(*(v.cbegin() + 1) == 2);
            CHECK(*(v.cend() - 1) == 2);
            CHECK(*(v.cend() - 2) == 1);
            CHECK(v.cbegin() + 2 == v.cend());
            CHECK(v.cend() - 2 == v.cbegin());

            CHECK(*v.rbegin() == 2);
            CHECK(*(v.rbegin() + 1) == 1);
            CHECK(*(v.rend() - 1) == 1);
            CHECK(*(v.rend() - 2) == 2);
            CHECK(v.rbegin() + 2 == v.rend());
            CHECK(v.rend() - 2 == v.rbegin());

            CHECK(*v.crbegin() == 2);
            CHECK(*(v.crbegin() + 1) == 1);
            CHECK(*(v.crend() - 1) == 1);
            CHECK(*(v.crend() - 2) == 2);
            CHECK(v.crbegin() + 2 == v.crend());
            CHECK(v.crend() - 2 == v.crbegin());
        }
    }

    SUBCASE("data") {
        {
            int2 i2;
            CHECK(i2.data() == &i2[0]);

            int3 i3;
            CHECK(i3.data() == &i3[0]);

            int4 i4;
            CHECK(i4.data() == &i4[0]);
        }
        {
            const int2 i2;
            CHECK(i2.data() == &i2[0]);

            const int3 i3;
            CHECK(i3.data() == &i3[0]);

            const int4 i4;
            CHECK(i4.data() == &i4[0]);
        }
    }

    SUBCASE("operator[]") {
        {
            STATIC_CHECK(int2(1,2).x == 1);
            STATIC_CHECK(int2(1,2).y == 2);

            STATIC_CHECK(int3(1,2,3).x == 1);
            STATIC_CHECK(int3(1,2,3).y == 2);
            STATIC_CHECK(int3(1,2,3).z == 3);

            STATIC_CHECK(int4(1,2,3,4).x == 1);
            STATIC_CHECK(int4(1,2,3,4).y == 2);
            STATIC_CHECK(int4(1,2,3,4).z == 3);
            STATIC_CHECK(int4(1,2,3,4).w == 4);
        }
        {
            STATIC_CHECK(int2(1,2)[0] == 1);
            STATIC_CHECK(int2(1,2)[1] == 2);
        }
        {
            int2 v;
            v.x = 1;
            v.y = 2;
            CHECK(v == int2(1,2));
            CHECK(std::as_const(v).at(0) == 1);
            CHECK(std::as_const(v).at(1) == 2);
        }
        {
            int3 v;
            v.x = 1;
            v.y = 2;
            v.z = 3;
            CHECK(v == int3(1,2,3));
            CHECK(std::as_const(v).at(0) == 1);
            CHECK(std::as_const(v).at(1) == 2);
            CHECK(std::as_const(v).at(2) == 3);
        }
        {
            int4 v;
            v.x = 1;
            v.y = 2;
            v.z = 3;
            v.w = 4;
            CHECK(v == int4(1,2,3,4));
            CHECK(std::as_const(v).at(0) == 1);
            CHECK(std::as_const(v).at(1) == 2);
            CHECK(std::as_const(v).at(2) == 3);
            CHECK(std::as_const(v).at(3) == 4);
        }
    }

    SUBCASE("at") {
        STATIC_CHECK(int2(1,2).at(0) == 1);
        STATIC_CHECK(int2(1,2).at(1) == 2);
    #ifndef VMATH_HPP_NO_EXCEPTIONS
        CHECK_THROWS_AS((void)int2(1,2).at(2), std::out_of_range);
    #endif
    }

    SUBCASE("operator==/operator!=") {
        STATIC_CHECK(int2(1,2) == int2(1,2));
        STATIC_CHECK_FALSE(int2(1,2) == int2(2,2));
        STATIC_CHECK_FALSE(int2(1,2) == int2(1,3));

        STATIC_CHECK_FALSE(int2(1,2) != int2(1,2));
        STATIC_CHECK(int2(1,2) != int2(2,2));
        STATIC_CHECK(int2(1,2) != int2(1,3));
    }

    SUBCASE("operator<") {
        STATIC_CHECK_FALSE(int2(1,2) < int2(1,2));

        STATIC_CHECK(int2(1,1) < int2(1,2));
        STATIC_CHECK_FALSE(int2(1,2) < int2(1,1));

        STATIC_CHECK(int2(0,3) < int2(1,2));
        STATIC_CHECK_FALSE(int2(1,2) < int2(0,3));
    }
}
