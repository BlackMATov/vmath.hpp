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

TEST_CASE("vmath/qua") {
    SUBCASE("size/sizeof") {
        STATIC_CHECK(qfloat{}.size == 4);
        STATIC_CHECK(qdouble{}.size == 4);

        STATIC_CHECK(sizeof(qfloat{}) == sizeof(float) * 4);
        STATIC_CHECK(sizeof(qdouble{}) == sizeof(double) * 4);
    }

    SUBCASE("guides") {
        STATIC_CHECK(qua{1,2,3,4}.size == 4);
        STATIC_CHECK(qua{{1,2,3},4}.size == 4);
        STATIC_CHECK(qua{vec{1,2,3},4}.size == 4);
        STATIC_CHECK(qua{{1,2,3,4}}.size == 4);
        STATIC_CHECK(qua(vec{1,2,3,4}).size == 4);
    }

    SUBCASE("ctors") {
        {
            qua<int> q;
            CHECK(q.v == int3(0,0,0));
            CHECK(q.s == 1);

            STATIC_CHECK(qua<int>() == qua<int>({0,0,0},1));
            (void)qua<int>(uninit);
            STATIC_CHECK(qua<int>(zero_init) == qua<int>({0,0,0},0));
            STATIC_CHECK(qua<int>(identity_init) == qua<int>({0,0,0},1));
        }
        {
            STATIC_CHECK(qfloat{}.v == uapprox3(0.f));
            STATIC_CHECK(qfloat{}.s == uapprox(1.f));

            STATIC_CHECK(qfloat{1,2,3,4}.v == uapprox3(1.f,2.f,3.f));
            STATIC_CHECK(qfloat{1,2,3,4}.s == uapprox(4.f));

            STATIC_CHECK(qfloat{{1,2,3},4}.v == uapprox3(1.f,2.f,3.f));
            STATIC_CHECK(qfloat{{1,2,3},4}.s == uapprox(4.f));

            STATIC_CHECK(qfloat{{1,2,3,4}}.v == uapprox3(1.f,2.f,3.f));
            STATIC_CHECK(qfloat{{1,2,3,4}}.s == uapprox(4.f));
        }
        {
            constexpr qfloat q(1,2,3,4);
            constexpr qfloat q2 = q;
            STATIC_CHECK(q2 == qfloat(1,2,3,4));
        }
        {
            constexpr qfloat q(1,2,3,4);
            constexpr qfloat q2 = std::move(q);
            STATIC_CHECK(q2 == qfloat(1,2,3,4));
        }
        {
            STATIC_CHECK(qfloat(1,2,3,4) == qfloat(1,2,3,4));
            STATIC_CHECK(qfloat(float3(1,2,3),4) == qfloat(1,2,3,4));
            STATIC_CHECK(qfloat(float4(1,2,3,4)) == qfloat(1,2,3,4));
        }
    }

    SUBCASE("operator=") {
        {
            qfloat v(1,2,3,4);
            qfloat v2;
            v2 = v;
            CHECK(v2 == qfloat(1,2,3,4));
        }
        {
            qfloat v(1,2,3,4);
            qfloat v2;
            v2 = std::move(v);
            CHECK(v2 == qfloat(1,2,3,4));
        }
    }

    SUBCASE("swap") {
        {
            qfloat v1(1,2,3,4);
            qfloat v2(4,5,6,7);
            v1.swap(v2);
            CHECK(v1 == qfloat(4,5,6,7));
            CHECK(v2 == qfloat(1,2,3,4));
        }
        {
            qfloat v1(1,2,3,4);
            qfloat v2(4,5,6,7);
            swap(v1, v2);
            CHECK(v1 == qfloat(4,5,6,7));
            CHECK(v2 == qfloat(1,2,3,4));
        }
    }

    SUBCASE("iter") {
        {
            qua v{1,2,3,4};

            CHECK(*v.begin() == 1);
            CHECK(*(v.begin() + 1) == 2);
            CHECK(*(v.end() - 1) == 4);
            CHECK(*(v.end() - 2) == 3);
            CHECK(v.begin() + 4 == v.end());
            CHECK(v.end() - 4 == v.begin());

            CHECK(*v.cbegin() == 1);
            CHECK(*(v.cbegin() + 1) == 2);
            CHECK(*(v.cend() - 1) == 4);
            CHECK(*(v.cend() - 2) == 3);
            CHECK(v.cbegin() + 4 == v.cend());
            CHECK(v.cend() - 4 == v.cbegin());

            CHECK(*v.rbegin() == 4);
            CHECK(*(v.rbegin() + 1) == 3);
            CHECK(*(v.rend() - 1) == 1);
            CHECK(*(v.rend() - 2) == 2);
            CHECK(v.rbegin() + 4 == v.rend());
            CHECK(v.rend() - 4 == v.rbegin());

            CHECK(*v.crbegin() == 4);
            CHECK(*(v.crbegin() + 1) == 3);
            CHECK(*(v.crend() - 1) == 1);
            CHECK(*(v.crend() - 2) == 2);
            CHECK(v.crbegin() + 4 == v.crend());
            CHECK(v.crend() - 4 == v.crbegin());

            *v.begin() = 3;
            CHECK(v == qua{3,2,3,4});
            *v.rbegin() = 5;
            CHECK(v == qua{3,2,3,5});
        }
        {
            const qua v{1,2,3,4};

            CHECK(*v.begin() == 1);
            CHECK(*(v.begin() + 1) == 2);
            CHECK(*(v.end() - 1) == 4);
            CHECK(*(v.end() - 2) == 3);
            CHECK(v.begin() + 4 == v.end());
            CHECK(v.end() - 4 == v.begin());

            CHECK(*v.cbegin() == 1);
            CHECK(*(v.cbegin() + 1) == 2);
            CHECK(*(v.cend() - 1) == 4);
            CHECK(*(v.cend() - 2) == 3);
            CHECK(v.cbegin() + 4 == v.cend());
            CHECK(v.cend() - 4 == v.cbegin());

            CHECK(*v.rbegin() == 4);
            CHECK(*(v.rbegin() + 1) == 3);
            CHECK(*(v.rend() - 1) == 1);
            CHECK(*(v.rend() - 2) == 2);
            CHECK(v.rbegin() + 4 == v.rend());
            CHECK(v.rend() - 4 == v.rbegin());

            CHECK(*v.crbegin() == 4);
            CHECK(*(v.crbegin() + 1) == 3);
            CHECK(*(v.crend() - 1) == 1);
            CHECK(*(v.crend() - 2) == 2);
            CHECK(v.crbegin() + 4 == v.crend());
            CHECK(v.crend() - 4 == v.crbegin());
        }
    }

    SUBCASE("data") {
        {
            qfloat i2;
            CHECK(i2.data() == &i2[0]);
        }
        {
            const qfloat i2;
            CHECK(i2.data() == &i2[0]);
        }
    }

    SUBCASE("operator[]") {
        {
            STATIC_CHECK(qua(1,2,3,4).v == vec(1,2,3));
            STATIC_CHECK(qua(1,2,3,4).s == 4);
        }
        {
            STATIC_CHECK(qua(1,2,3,4)[0] == 1);
            STATIC_CHECK(qua(1,2,3,4)[1] == 2);
            STATIC_CHECK(qua(1,2,3,4)[2] == 3);
            STATIC_CHECK(qua(1,2,3,4)[3] == 4);
        }
        {
            qua<int> v;
            v.v = vec(1,2,3);
            v.s = 4;
            CHECK(v == qua(1,2,3,4));
        }
        {
            qua<int> v;
            v[0] = 1;
            v[1] = 2;
            v[2] = 3;
            v[3] = 4;
            CHECK(v == qua(1,2,3,4));
        }
        {
            qua<int> v;
            v.at(0) = 1;
            v.at(1) = 2;
            v.at(2) = 3;
            v.at(3) = 4;
            CHECK(v == qua(1,2,3,4));
        }
        {
            const qua v{1,2,3,4};
            CHECK(v[0] == 1);
            CHECK(v[1] == 2);
            CHECK(v[2] == 3);
            CHECK(v[3] == 4);
            CHECK(v.at(0) == 1);
            CHECK(v.at(1) == 2);
            CHECK(v.at(2) == 3);
            CHECK(v.at(3) == 4);
        }
    }

    SUBCASE("at") {
        STATIC_CHECK(qua(1,2,3,4).at(0) == 1);
        STATIC_CHECK(qua(1,2,3,4).at(1) == 2);
        STATIC_CHECK(qua(1,2,3,4).at(2) == 3);
        STATIC_CHECK(qua(1,2,3,4).at(3) == 4);
    #ifndef VMATH_HPP_NO_EXCEPTIONS
        CHECK_THROWS_AS((void)qua(1,2,3,4).at(4), std::out_of_range);
    #endif
    }

    SUBCASE("operator==/operator!=") {
        STATIC_CHECK(qfloat(1,2,3,4) == qfloat(1,2,3,4));
        STATIC_CHECK_FALSE(qfloat(1,2,3,4) == qfloat(2,2,3,4));
        STATIC_CHECK_FALSE(qfloat(1,2,3,4) == qfloat(1,3,3,4));

        STATIC_CHECK_FALSE(qfloat(1,2,3,4) != qfloat(1,2,3,4));
        STATIC_CHECK(qfloat(1,2,3,4) != qfloat(2,2,3,4));
        STATIC_CHECK(qfloat(1,2,3,4) != qfloat(1,3,3,4));
    }

    SUBCASE("operator<") {
        STATIC_CHECK_FALSE(qfloat(1,2,3,4) < qfloat(1,2,3,4));

        STATIC_CHECK(qfloat(0,2,3,4) < qfloat(1,2,3,4));
        STATIC_CHECK(qfloat(1,1,3,4) < qfloat(1,2,3,4));
        STATIC_CHECK(qfloat(1,2,2,4) < qfloat(1,2,3,4));
        STATIC_CHECK(qfloat(1,2,3,3) < qfloat(1,2,3,4));

        STATIC_CHECK_FALSE(qfloat(1,2,3,4) < qfloat(0,2,3,4));
        STATIC_CHECK_FALSE(qfloat(1,2,3,4) < qfloat(1,1,3,4));
        STATIC_CHECK_FALSE(qfloat(1,2,3,4) < qfloat(1,2,2,4));
        STATIC_CHECK_FALSE(qfloat(1,2,3,4) < qfloat(1,2,3,3));

        STATIC_CHECK(qfloat(0,3,3,4) < qfloat(1,2,3,4));
        STATIC_CHECK_FALSE(qfloat(1,2,3,4) < qfloat(0,3,3,4));
    }
}
