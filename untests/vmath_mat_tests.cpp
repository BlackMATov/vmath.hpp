/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2023, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/mat") {
    SUBCASE("size/sizeof") {
        STATIC_CHECK(imat2{}.size == 2);
        STATIC_CHECK(imat3{}.size == 3);
        STATIC_CHECK(imat4{}.size == 4);

        STATIC_CHECK(sizeof(imat2{}) == sizeof(int) * 2 * 2);
        STATIC_CHECK(sizeof(imat3{}) == sizeof(int) * 3 * 3);
        STATIC_CHECK(sizeof(imat4{}) == sizeof(int) * 4 * 4);
    }

    SUBCASE("guides") {
        STATIC_CHECK(mat{1,2,3,4}.size == 2);
        STATIC_CHECK(mat{{1,2},{3,4}}.size == 2);
        STATIC_CHECK(mat{vec{1,2},vec{3,4}}.size == 2);

        STATIC_CHECK(mat{1,2,3,4,5,6,7,8,9}.size == 3);
        STATIC_CHECK(mat{{1,2,3},{4,5,6},{7,8,9}}.size == 3);
        STATIC_CHECK(mat{vec{1,2,3},vec{4,5,6},vec{7,8,9}}.size == 3);
        STATIC_CHECK(mat{mat{1,2,3,4},vec{5,6}}.size == 3);

        STATIC_CHECK(mat{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}.size == 4);
        STATIC_CHECK(mat{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}.size == 4);
        STATIC_CHECK(mat{vec{1,2,3,4},vec{5,6,7,8},vec{9,10,11,12},vec{13,14,15,16}}.size == 4);
        STATIC_CHECK(mat{mat{1,2,3,4,5,6,7,8,9},vec{5,6,7}}.size == 4);
    }

    SUBCASE("ctors") {
        {
            mat<int, 2> m2;
            CHECK(m2.rows[0] == ivec2(1,0));
            CHECK(m2.rows[1] == ivec2(0,1));

            mat<int, 3> m3;
            CHECK(m3.rows[0] == ivec3(1,0,0));
            CHECK(m3.rows[1] == ivec3(0,1,0));
            CHECK(m3.rows[2] == ivec3(0,0,1));

            mat<int, 4> m4;
            CHECK(m4.rows[0] == ivec4(1,0,0,0));
            CHECK(m4.rows[1] == ivec4(0,1,0,0));
            CHECK(m4.rows[2] == ivec4(0,0,1,0));
            CHECK(m4.rows[3] == ivec4(0,0,0,1));

            STATIC_CHECK(imat2() == imat2({1,0},{0,1}));
            STATIC_CHECK(imat3() == imat3({1,0,0},{0,1,0},{0,0,1}));
            STATIC_CHECK(imat4() == imat4({1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}));

            (void)imat2(uninit);
            (void)imat3(uninit);
            (void)imat4(uninit);

            STATIC_CHECK(imat2(zero_init) == imat2({0,0},{0,0}));
            STATIC_CHECK(imat3(zero_init) == imat3({0,0,0},{0,0,0},{0,0,0}));
            STATIC_CHECK(imat4(zero_init) == imat4({0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}));

            STATIC_CHECK(imat2(unit_init) == imat2({1,1},{1,1}));
            STATIC_CHECK(imat3(unit_init) == imat3({1,1,1},{1,1,1},{1,1,1}));
            STATIC_CHECK(imat4(unit_init) == imat4({1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}));

            STATIC_CHECK(imat2(identity_init) == imat2({1,0},{0,1}));
            STATIC_CHECK(imat3(identity_init) == imat3({1,0,0},{0,1,0},{0,0,1}));
            STATIC_CHECK(imat4(identity_init) == imat4({1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}));
        }
        {
            STATIC_CHECK(imat2()[0] == ivec2(1,0));
            STATIC_CHECK(imat2()[1] == ivec2(0,1));

            STATIC_CHECK(imat2(1,2,3,4)[0] == ivec2(1,2));
            STATIC_CHECK(imat2(1,2,3,4)[1] == ivec2(3,4));

            STATIC_CHECK(imat2({1,2},{3,4})[0] == ivec2(1,2));
            STATIC_CHECK(imat2({1,2},{3,4})[1] == ivec2(3,4));
        }
        {
            constexpr imat2 v(1,2,3,4);
            constexpr imat2 v2 = v;
            STATIC_CHECK(v2 == imat2(1,2,3,4));
        }
        {
            constexpr imat2 v(1,2,3,4);
            constexpr imat2 v2 = std::move(v);
            STATIC_CHECK(v2 == imat2(1,2,3,4));
        }
        {
            STATIC_CHECK(imat2() == imat2(1,0,0,1));
            STATIC_CHECK(imat2(2) == imat2(2,0,0,2));
            STATIC_CHECK(imat2(ivec2{2,3}) == imat2(2,0,0,3));
            STATIC_CHECK(imat2(1,2,3,4) == imat2(1,2,3,4));
            STATIC_CHECK(imat2({1,2},{3,4}) == imat2(1,2,3,4));
            STATIC_CHECK(imat2(imat2({1,2},{3,4})) == imat2(1,2,3,4));
            STATIC_CHECK(imat2(imat3({1,2,3},{4,5,6},{7,8,9})) == imat2(1,2,4,5));
            STATIC_CHECK(imat2(imat4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16})) == imat2(1,2,5,6));

            STATIC_CHECK(imat3() == imat3(1,0,0,0,1,0,0,0,1));
            STATIC_CHECK(imat3(2) == imat3(2,0,0,0,2,0,0,0,2));
            STATIC_CHECK(imat3(ivec3{2,3,4}) == imat3(2,0,0,0,3,0,0,0,4));
            STATIC_CHECK(imat3(1,2,3,4,5,6,7,8,9) == imat3(1,2,3,4,5,6,7,8,9));
            STATIC_CHECK(imat3({1,2,3},{4,5,6},{7,8,9}) == imat3(1,2,3,4,5,6,7,8,9));
            STATIC_CHECK(imat3(imat2({1,2},{3,4}),ivec2{5,6}) == imat3(1,2,0,3,4,0,5,6,1));
            STATIC_CHECK(imat3(imat3({1,2,3},{4,5,6},{7,8,9})) == imat3(1,2,3,4,5,6,7,8,9));
            STATIC_CHECK(imat3(imat2({1,2},{3,4})) == imat3(1,2,0,3,4,0,0,0,1));
            STATIC_CHECK(imat3(imat4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16})) == imat3(1,2,3,5,6,7,9,10,11));

            STATIC_CHECK(imat4() == imat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1));
            STATIC_CHECK(imat4(2) == imat4(2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,2));
            STATIC_CHECK(imat4(ivec4{2,3,4,5}) == imat4(2,0,0,0,0,3,0,0,0,0,4,0,0,0,0,5));
            STATIC_CHECK(imat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16) == imat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
            STATIC_CHECK(imat4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}) == imat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
            STATIC_CHECK(imat4(imat3({1,2,3},{4,5,6},{7,8,9}),ivec3{10,11,12}) == imat4(1,2,3,0,4,5,6,0,7,8,9,0,10,11,12,1));
            STATIC_CHECK(imat4(imat4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16})) == imat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
            STATIC_CHECK(imat4(imat2({1,2},{3,4})) == imat4(1,2,0,0,3,4,0,0,0,0,1,0,0,0,0,1));
            STATIC_CHECK(imat4(imat3({1,2,3},{4,5,6},{7,8,9})) == imat4(1,2,3,0,4,5,6,0,7,8,9,0,0,0,0,1));
        }
        {
            constexpr float is[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
            STATIC_CHECK(dmat2(is) == dmat2(1,2,3,4));
            STATIC_CHECK(dmat3(is) == dmat3(1,2,3,4,5,6,7,8,9));
            STATIC_CHECK(dmat4(is) == dmat4({1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}));
        }
    }

    SUBCASE("operator=") {
        {
            imat2 v(1,2,3,4);
            imat2 v2;
            v2 = v;
            CHECK(v2 == imat2(1,2,3,4));
        }
        {
            imat2 v(1,2,3,4);
            imat2 v2;
            v2 = std::move(v);
            CHECK(v2 == imat2(1,2,3,4));
        }
    }

    SUBCASE("swap") {
        {
            imat2 v1(1,2,3,4);
            imat2 v2(4,5,6,7);
            v1.swap(v2);
            CHECK(v1 == imat2(4,5,6,7));
            CHECK(v2 == imat2(1,2,3,4));
        }
        {
            imat2 v1(1,2,3,4);
            imat2 v2(4,5,6,7);
            swap(v1, v2);
            CHECK(v1 == imat2(4,5,6,7));
            CHECK(v2 == imat2(1,2,3,4));
        }
    }

    SUBCASE("iter") {
        {
            imat2 m{1,2,3,4};

            CHECK(*m.begin() == vec{1,2});
            CHECK(*(m.begin() + 1) == vec{3,4});
            CHECK(*(m.end() - 1) == vec{3,4});
            CHECK(*(m.end() - 2) == vec{1,2});
            CHECK(m.begin() + 2 == m.end());
            CHECK(m.end() - 2 == m.begin());

            CHECK(*m.cbegin() == vec{1,2});
            CHECK(*(m.cbegin() + 1) == vec{3,4});
            CHECK(*(m.cend() - 1) == vec{3,4});
            CHECK(*(m.cend() - 2) == vec{1,2});
            CHECK(m.cbegin() + 2 == m.cend());
            CHECK(m.cend() - 2 == m.cbegin());

            CHECK(*m.rbegin() == vec{3,4});
            CHECK(*(m.rbegin() + 1) == vec{1,2});
            CHECK(*(m.rend() - 1) == vec{1,2});
            CHECK(*(m.rend() - 2) == vec{3,4});
            CHECK(m.rbegin() + 2 == m.rend());
            CHECK(m.rend() - 2 == m.rbegin());

            CHECK(*m.crbegin() == vec{3,4});
            CHECK(*(m.crbegin() + 1) == vec{1,2});
            CHECK(*(m.crend() - 1) == vec{1,2});
            CHECK(*(m.crend() - 2) == vec{3,4});
            CHECK(m.crbegin() + 2 == m.crend());
            CHECK(m.crend() - 2 == m.crbegin());

            *m.begin() = {5,6};
            CHECK(m == imat2{5,6,3,4});
            *m.rbegin() = {7,8};
            CHECK(m == imat2{5,6,7,8});
        }
        {
            const imat2 m{1,2,3,4};

            CHECK(*m.begin() == vec{1,2});
            CHECK(*(m.begin() + 1) == vec{3,4});
            CHECK(*(m.end() - 1) == vec{3,4});
            CHECK(*(m.end() - 2) == vec{1,2});
            CHECK(m.begin() + 2 == m.end());
            CHECK(m.end() - 2 == m.begin());

            CHECK(*m.cbegin() == vec{1,2});
            CHECK(*(m.cbegin() + 1) == vec{3,4});
            CHECK(*(m.cend() - 1) == vec{3,4});
            CHECK(*(m.cend() - 2) == vec{1,2});
            CHECK(m.cbegin() + 2 == m.cend());
            CHECK(m.cend() - 2 == m.cbegin());

            CHECK(*m.rbegin() == vec{3,4});
            CHECK(*(m.rbegin() + 1) == vec{1,2});
            CHECK(*(m.rend() - 1) == vec{1,2});
            CHECK(*(m.rend() - 2) == vec{3,4});
            CHECK(m.rbegin() + 2 == m.rend());
            CHECK(m.rend() - 2 == m.rbegin());

            CHECK(*m.crbegin() == vec{3,4});
            CHECK(*(m.crbegin() + 1) == vec{1,2});
            CHECK(*(m.crend() - 1) == vec{1,2});
            CHECK(*(m.crend() - 2) == vec{3,4});
            CHECK(m.crbegin() + 2 == m.crend());
            CHECK(m.crend() - 2 == m.crbegin());
        }
    }

    SUBCASE("data") {
        {
            imat2 m2;
            CHECK(m2.data() == &m2[0]);

            imat3 m3;
            CHECK(m3.data() == &m3[0]);

            imat4 m4;
            CHECK(m4.data() == &m4[0]);
        }
        {
            const imat2 m2;
            CHECK(m2.data() == &m2[0]);

            const imat3 m3;
            CHECK(m3.data() == &m3[0]);

            const imat4 m4;
            CHECK(m4.data() == &m4[0]);
        }
    }

    SUBCASE("operator[]") {
        {
            STATIC_CHECK(imat2()[0] == ivec2(1,0));
            STATIC_CHECK(imat2()[1] == ivec2(0,1));

            STATIC_CHECK(imat3()[0] == ivec3(1,0,0));
            STATIC_CHECK(imat3()[1] == ivec3(0,1,0));
            STATIC_CHECK(imat3()[2] == ivec3(0,0,1));

            STATIC_CHECK(imat4()[0] == ivec4(1,0,0,0));
            STATIC_CHECK(imat4()[1] == ivec4(0,1,0,0));
            STATIC_CHECK(imat4()[2] == ivec4(0,0,1,0));
            STATIC_CHECK(imat4()[3] == ivec4(0,0,0,1));
        }
        {
            imat2 v;
            v[0] = ivec2(1,2);
            v[1] = ivec2(3,4);
            CHECK(v == imat2(1,2,3,4));
            CHECK(std::as_const(v).at(0) == ivec2(1,2));
            CHECK(std::as_const(v).at(1) == ivec2(3,4));
        }
        {
            imat3 v;
            v[0] = ivec3(1,2,3);
            v[1] = ivec3(4,5,6);
            v[2] = ivec3(7,8,9);
            CHECK(v == imat3(1,2,3,4,5,6,7,8,9));
            CHECK(std::as_const(v).at(0) == ivec3(1,2,3));
            CHECK(std::as_const(v).at(1) == ivec3(4,5,6));
            CHECK(std::as_const(v).at(2) == ivec3(7,8,9));
        }
        {
            imat4 v;
            v[0] = ivec4(1,2,3,4);
            v[1] = ivec4(5,6,7,8);
            v[2] = ivec4(9,10,11,12);
            v[3] = ivec4(13,14,15,16);
            CHECK(v == imat4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
            CHECK(std::as_const(v).at(0) == ivec4(1,2,3,4));
            CHECK(std::as_const(v).at(1) == ivec4(5,6,7,8));
            CHECK(std::as_const(v).at(2) == ivec4(9,10,11,12));
            CHECK(std::as_const(v).at(3) == ivec4(13,14,15,16));
        }
    }

    SUBCASE("at") {
        STATIC_CHECK(imat2(1,2,3,4).at(0) == ivec2(1,2));
        STATIC_CHECK(imat2(1,2,3,4).at(1) == ivec2(3,4));
    #ifndef VMATH_HPP_NO_EXCEPTIONS
        CHECK_THROWS_AS((void)imat2(1,2,3,4).at(2), std::out_of_range);
    #endif
    }

    SUBCASE("operator==/operator!=") {
        STATIC_CHECK(imat2(1,2,3,4) == imat2(1,2,3,4));
        STATIC_CHECK_FALSE(imat2(1,2,3,4) == imat2(2,2,3,4));
        STATIC_CHECK_FALSE(imat2(1,2,3,4) == imat2(1,3,3,4));

        STATIC_CHECK_FALSE(imat2(1,2,3,4) != imat2(1,2,3,4));
        STATIC_CHECK(imat2(1,2,3,4) != imat2(2,2,3,4));
        STATIC_CHECK(imat2(1,2,3,4) != imat2(1,3,3,4));
    }

    SUBCASE("operator<") {
        STATIC_CHECK_FALSE(imat2(1,2,3,4) < imat2(1,2,3,4));

        STATIC_CHECK(imat2(1,1,3,4) < imat2(1,2,3,4));
        STATIC_CHECK_FALSE(imat2(1,2,3,4) < imat2(1,1,3,4));

        STATIC_CHECK(imat2(0,3,3,4) < imat2(1,2,3,4));
        STATIC_CHECK_FALSE(imat2(1,2,3,4) < imat2(0,3,3,4));
    }
}
