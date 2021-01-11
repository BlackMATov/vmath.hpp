/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"
#include "doctest/doctest.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/mat") {
    SUBCASE("size/sizeof") {
        STATIC_REQUIRE(int2x2{}.size == 2);
        STATIC_REQUIRE(int3x3{}.size == 3);
        STATIC_REQUIRE(int4x4{}.size == 4);

        STATIC_REQUIRE(sizeof(int2x2{}) == sizeof(int) * 2 * 2);
        STATIC_REQUIRE(sizeof(int3x3{}) == sizeof(int) * 3 * 3);
        STATIC_REQUIRE(sizeof(int4x4{}) == sizeof(int) * 4 * 4);
    }

    SUBCASE("guides") {
        STATIC_REQUIRE(mat{1,2,3,4}.size == 2);
        STATIC_REQUIRE(mat{{1,2},{3,4}}.size == 2);
        STATIC_REQUIRE(mat{vec{1,2},vec{3,4}}.size == 2);

        STATIC_REQUIRE(mat{1,2,3,4,5,6,7,8,9}.size == 3);
        STATIC_REQUIRE(mat{{1,2,3},{4,5,6},{7,8,9}}.size == 3);
        STATIC_REQUIRE(mat{vec{1,2,3},vec{4,5,6},vec{7,8,9}}.size == 3);
        STATIC_REQUIRE(mat{mat{1,2,3,4},vec{5,6}}.size == 3);

        STATIC_REQUIRE(mat{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}.size == 4);
        STATIC_REQUIRE(mat{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}.size == 4);
        STATIC_REQUIRE(mat{vec{1,2,3,4},vec{5,6,7,8},vec{9,10,11,12},vec{13,14,15,16}}.size == 4);
        STATIC_REQUIRE(mat{mat{1,2,3,4,5,6,7,8,9},vec{5,6,7}}.size == 4);
    }

    SUBCASE("ctors") {
        {
            STATIC_REQUIRE(int2x2()[0] == int2(1,0));
            STATIC_REQUIRE(int2x2()[1] == int2(0,1));

            STATIC_REQUIRE(int2x2(1,2,3,4)[0] == int2(1,2));
            STATIC_REQUIRE(int2x2(1,2,3,4)[1] == int2(3,4));

            STATIC_REQUIRE(int2x2({1,2},{3,4})[0] == int2(1,2));
            STATIC_REQUIRE(int2x2({1,2},{3,4})[1] == int2(3,4));
        }
        {
            constexpr int2x2 v(1,2,3,4);
            constexpr int2x2 v2 = v;
            STATIC_REQUIRE(v2 == int2x2(1,2,3,4));
        }
        {
            constexpr int2x2 v(1,2,3,4);
            constexpr int2x2 v2 = std::move(v);
            STATIC_REQUIRE(v2 == int2x2(1,2,3,4));
        }
        {
            STATIC_REQUIRE(int2x2() == int2x2(1,0,0,1));
            STATIC_REQUIRE(int2x2(2) == int2x2(2,0,0,2));
            STATIC_REQUIRE(int2x2(int2{2,3}) == int2x2(2,0,0,3));
            STATIC_REQUIRE(int2x2(1,2,3,4) == int2x2(1,2,3,4));
            STATIC_REQUIRE(int2x2({1,2},{3,4}) == int2x2(1,2,3,4));
            STATIC_REQUIRE(int2x2(int2x2({1,2},{3,4})) == int2x2(1,2,3,4));
            STATIC_REQUIRE(int2x2(int3x3({1,2,3},{4,5,6},{7,8,9})) == int2x2(1,2,4,5));
            STATIC_REQUIRE(int2x2(int4x4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16})) == int2x2(1,2,5,6));

            STATIC_REQUIRE(int3x3() == int3x3(1,0,0,0,1,0,0,0,1));
            STATIC_REQUIRE(int3x3(2) == int3x3(2,0,0,0,2,0,0,0,2));
            STATIC_REQUIRE(int3x3(int3{2,3,4}) == int3x3(2,0,0,0,3,0,0,0,4));
            STATIC_REQUIRE(int3x3(1,2,3,4,5,6,7,8,9) == int3x3(1,2,3,4,5,6,7,8,9));
            STATIC_REQUIRE(int3x3({1,2,3},{4,5,6},{7,8,9}) == int3x3(1,2,3,4,5,6,7,8,9));
            STATIC_REQUIRE(int3x3(int2x2({1,2},{3,4}),int2{5,6}) == int3x3(1,2,0,3,4,0,5,6,1));
            STATIC_REQUIRE(int3x3(int3x3({1,2,3},{4,5,6},{7,8,9})) == int3x3(1,2,3,4,5,6,7,8,9));
            STATIC_REQUIRE(int3x3(int2x2({1,2},{3,4})) == int3x3(1,2,0,3,4,0,0,0,1));
            STATIC_REQUIRE(int3x3(int4x4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16})) == int3x3(1,2,3,5,6,7,9,10,11));

            STATIC_REQUIRE(int4x4() == int4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1));
            STATIC_REQUIRE(int4x4(2) == int4x4(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,2));
            STATIC_REQUIRE(int4x4(int4{2,3,4,5}) == int4x4(2,0,0,0,0,3,0,0,0,0,4,0,0,0,0,5));
            STATIC_REQUIRE(int4x4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16) == int4x4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
            STATIC_REQUIRE(int4x4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}) == int4x4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
            STATIC_REQUIRE(int4x4(int3x3({1,2,3},{4,5,6},{7,8,9}),int3{10,11,12}) == int4x4(1,2,3,0,4,5,6,0,7,8,9,0,10,11,12,1));
            STATIC_REQUIRE(int4x4(int4x4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16})) == int4x4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
            STATIC_REQUIRE(int4x4(int2x2({1,2},{3,4})) == int4x4(1,2,0,0,3,4,0,0,0,0,1,0,0,0,0,1));
            STATIC_REQUIRE(int4x4(int3x3({1,2,3},{4,5,6},{7,8,9})) == int4x4(1,2,3,0,4,5,6,0,7,8,9,0,0,0,0,1));
        }
    }

    SUBCASE("operator=") {
        {
            int2x2 v(1,2,3,4);
            int2x2 v2;
            v2 = v;
            REQUIRE(v2 == int2x2(1,2,3,4));
        }
        {
            int2x2 v(1,2,3,4);
            int2x2 v2;
            v2 = std::move(v);
            REQUIRE(v2 == int2x2(1,2,3,4));
        }
    }

    SUBCASE("swap") {
        {
            int2x2 v1(1,2,3,4);
            int2x2 v2(4,5,6,7);
            v1.swap(v2);
            REQUIRE(v1 == int2x2(4,5,6,7));
            REQUIRE(v2 == int2x2(1,2,3,4));
        }
        {
            int2x2 v1(1,2,3,4);
            int2x2 v2(4,5,6,7);
            swap(v1, v2);
            REQUIRE(v1 == int2x2(4,5,6,7));
            REQUIRE(v2 == int2x2(1,2,3,4));
        }
    }

    SUBCASE("iter") {
        {
            int2x2 m{1,2,3,4};

            REQUIRE(*m.begin() == vec{1,2});
            REQUIRE(*(m.begin() + 1) == vec{3,4});
            REQUIRE(*(m.end() - 1) == vec{3,4});
            REQUIRE(*(m.end() - 2) == vec{1,2});
            REQUIRE(m.begin() + 2 == m.end());
            REQUIRE(m.end() - 2 == m.begin());

            REQUIRE(*m.cbegin() == vec{1,2});
            REQUIRE(*(m.cbegin() + 1) == vec{3,4});
            REQUIRE(*(m.cend() - 1) == vec{3,4});
            REQUIRE(*(m.cend() - 2) == vec{1,2});
            REQUIRE(m.cbegin() + 2 == m.cend());
            REQUIRE(m.cend() - 2 == m.cbegin());

            REQUIRE(*m.rbegin() == vec{3,4});
            REQUIRE(*(m.rbegin() + 1) == vec{1,2});
            REQUIRE(*(m.rend() - 1) == vec{1,2});
            REQUIRE(*(m.rend() - 2) == vec{3,4});
            REQUIRE(m.rbegin() + 2 == m.rend());
            REQUIRE(m.rend() - 2 == m.rbegin());

            REQUIRE(*m.crbegin() == vec{3,4});
            REQUIRE(*(m.crbegin() + 1) == vec{1,2});
            REQUIRE(*(m.crend() - 1) == vec{1,2});
            REQUIRE(*(m.crend() - 2) == vec{3,4});
            REQUIRE(m.crbegin() + 2 == m.crend());
            REQUIRE(m.crend() - 2 == m.crbegin());

            *m.begin() = {5,6};
            REQUIRE(m == int2x2{5,6,3,4});
            *m.rbegin() = {7,8};
            REQUIRE(m == int2x2{5,6,7,8});
        }
        {
            const int2x2 m{1,2,3,4};

            REQUIRE(*m.begin() == vec{1,2});
            REQUIRE(*(m.begin() + 1) == vec{3,4});
            REQUIRE(*(m.end() - 1) == vec{3,4});
            REQUIRE(*(m.end() - 2) == vec{1,2});
            REQUIRE(m.begin() + 2 == m.end());
            REQUIRE(m.end() - 2 == m.begin());

            REQUIRE(*m.cbegin() == vec{1,2});
            REQUIRE(*(m.cbegin() + 1) == vec{3,4});
            REQUIRE(*(m.cend() - 1) == vec{3,4});
            REQUIRE(*(m.cend() - 2) == vec{1,2});
            REQUIRE(m.cbegin() + 2 == m.cend());
            REQUIRE(m.cend() - 2 == m.cbegin());

            REQUIRE(*m.rbegin() == vec{3,4});
            REQUIRE(*(m.rbegin() + 1) == vec{1,2});
            REQUIRE(*(m.rend() - 1) == vec{1,2});
            REQUIRE(*(m.rend() - 2) == vec{3,4});
            REQUIRE(m.rbegin() + 2 == m.rend());
            REQUIRE(m.rend() - 2 == m.rbegin());

            REQUIRE(*m.crbegin() == vec{3,4});
            REQUIRE(*(m.crbegin() + 1) == vec{1,2});
            REQUIRE(*(m.crend() - 1) == vec{1,2});
            REQUIRE(*(m.crend() - 2) == vec{3,4});
            REQUIRE(m.crbegin() + 2 == m.crend());
            REQUIRE(m.crend() - 2 == m.crbegin());
        }
    }

    SUBCASE("data") {
        {
            int2x2 m2;
            REQUIRE(m2.data() == &m2[0]);

            int3x3 m3;
            REQUIRE(m3.data() == &m3[0]);

            int4x4 m4;
            REQUIRE(m4.data() == &m4[0]);
        }
        {
            const int2x2 m2;
            REQUIRE(m2.data() == &m2[0]);

            const int3x3 m3;
            REQUIRE(m3.data() == &m3[0]);

            const int4x4 m4;
            REQUIRE(m4.data() == &m4[0]);
        }
    }

    SUBCASE("operator[]") {
        {
            STATIC_REQUIRE(int2x2()[0] == int2(1,0));
            STATIC_REQUIRE(int2x2()[1] == int2(0,1));

            STATIC_REQUIRE(int3x3()[0] == int3(1,0,0));
            STATIC_REQUIRE(int3x3()[1] == int3(0,1,0));
            STATIC_REQUIRE(int3x3()[2] == int3(0,0,1));

            STATIC_REQUIRE(int4x4()[0] == int4(1,0,0,0));
            STATIC_REQUIRE(int4x4()[1] == int4(0,1,0,0));
            STATIC_REQUIRE(int4x4()[2] == int4(0,0,1,0));
            STATIC_REQUIRE(int4x4()[3] == int4(0,0,0,1));
        }
        {
            int2x2 v;
            v[0] = int2(1,2);
            v[1] = int2(3,4);
            REQUIRE(v == int2x2(1,2,3,4));
        }
        {
            int3x3 v;
            v[0] = int3(1,2,3);
            v[1] = int3(4,5,6);
            v[2] = int3(7,8,9);
            REQUIRE(v == int3x3(1,2,3,4,5,6,7,8,9));
        }
        {
            int4x4 v;
            v[0] = int4(1,2,3,4);
            v[1] = int4(5,6,7,8);
            v[2] = int4(9,10,11,12);
            v[3] = int4(13,14,15,16);
            REQUIRE(v == int4x4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
        }
    }

    SUBCASE("at") {
        STATIC_REQUIRE(int2x2(1,2,3,4).at(0) == int2(1,2));
        STATIC_REQUIRE(int2x2(1,2,3,4).at(1) == int2(3,4));
        REQUIRE_THROWS_AS((void)int2x2(1,2,3,4).at(2), std::out_of_range);
    }

    SUBCASE("operator==/operator!=") {
        STATIC_REQUIRE(int2x2(1,2,3,4) == int2x2(1,2,3,4));
        STATIC_REQUIRE_FALSE(int2x2(1,2,3,4) == int2x2(2,2,3,4));
        STATIC_REQUIRE_FALSE(int2x2(1,2,3,4) == int2x2(1,3,3,4));

        STATIC_REQUIRE_FALSE(int2x2(1,2,3,4) != int2x2(1,2,3,4));
        STATIC_REQUIRE(int2x2(1,2,3,4) != int2x2(2,2,3,4));
        STATIC_REQUIRE(int2x2(1,2,3,4) != int2x2(1,3,3,4));
    }

    SUBCASE("operator<") {
        STATIC_REQUIRE_FALSE(int2x2(1,2,3,4) < int2x2(1,2,3,4));

        STATIC_REQUIRE(int2x2(1,1,3,4) < int2x2(1,2,3,4));
        STATIC_REQUIRE_FALSE(int2x2(1,2,3,4) < int2x2(1,1,3,4));

        STATIC_REQUIRE(int2x2(0,3,3,4) < int2x2(1,2,3,4));
        STATIC_REQUIRE_FALSE(int2x2(1,2,3,4) < int2x2(0,3,3,4));
    }
}
