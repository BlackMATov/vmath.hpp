/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"
#include "catch/catch.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/qua") {
    SECTION("size/sizeof") {
        STATIC_REQUIRE(fqua{}.size == 4);
        STATIC_REQUIRE(dqua{}.size == 4);

        STATIC_REQUIRE(sizeof(fqua{}) == sizeof(float) * 4);
        STATIC_REQUIRE(sizeof(dqua{}) == sizeof(double) * 4);
    }

    SECTION("guides") {
        STATIC_REQUIRE(qua{1,2,3,4}.size == 4);
        STATIC_REQUIRE(qua{{1,2,3},4}.size == 4);
        STATIC_REQUIRE(qua{vec{1,2,3},4}.size == 4);
        STATIC_REQUIRE(qua{{1,2,3,4}}.size == 4);
        STATIC_REQUIRE(qua(vec{1,2,3,4}).size == 4);
    }

    SECTION("ctors") {
        {
            STATIC_REQUIRE(fqua{}.v == uapprox3(0.f));
            STATIC_REQUIRE(fqua{}.s == uapprox(1.f));

            STATIC_REQUIRE(fqua{1,2,3,4}.v == uapprox3(1.f,2.f,3.f));
            STATIC_REQUIRE(fqua{1,2,3,4}.s == uapprox(4.f));

            STATIC_REQUIRE(fqua{{1,2,3},4}.v == uapprox3(1.f,2.f,3.f));
            STATIC_REQUIRE(fqua{{1,2,3},4}.s == uapprox(4.f));

            STATIC_REQUIRE(fqua{{1,2,3,4}}.v == uapprox3(1.f,2.f,3.f));
            STATIC_REQUIRE(fqua{{1,2,3,4}}.s == uapprox(4.f));
        }
        {
            constexpr fqua q(1,2,3,4);
            constexpr fqua q2 = q;
            STATIC_REQUIRE(q2 == fqua(1,2,3,4));
        }
        {
            constexpr fqua q(1,2,3,4);
            constexpr fqua q2 = std::move(q);
            STATIC_REQUIRE(q2 == fqua(1,2,3,4));
        }
        {
            STATIC_REQUIRE(fqua(1,2,3,4) == fqua(1,2,3,4));
            STATIC_REQUIRE(fqua(float3(1,2,3),4) == fqua(1,2,3,4));
            STATIC_REQUIRE(fqua(float4(1,2,3,4)) == fqua(1,2,3,4));
        }
    }

    SECTION("operator=") {
        {
            fqua v(1,2,3,4);
            fqua v2;
            v2 = v;
            REQUIRE(v2 == fqua(1,2,3,4));
        }
        {
            fqua v(1,2,3,4);
            fqua v2;
            v2 = std::move(v);
            REQUIRE(v2 == fqua(1,2,3,4));
        }
    }

    SECTION("swap") {
        {
            fqua v1(1,2,3,4);
            fqua v2(4,5,6,7);
            v1.swap(v2);
            REQUIRE(v1 == fqua(4,5,6,7));
            REQUIRE(v2 == fqua(1,2,3,4));
        }
        {
            fqua v1(1,2,3,4);
            fqua v2(4,5,6,7);
            swap(v1, v2);
            REQUIRE(v1 == fqua(4,5,6,7));
            REQUIRE(v2 == fqua(1,2,3,4));
        }
    }

    SECTION("iter") {
        {
            fqua v{1,2,3,4};

            REQUIRE(*v.begin() == 1);
            REQUIRE(*(v.begin() + 1) == 2);
            REQUIRE(*(v.end() - 1) == 4);
            REQUIRE(*(v.end() - 2) == 3);
            REQUIRE(v.begin() + 4 == v.end());
            REQUIRE(v.end() - 4 == v.begin());

            REQUIRE(*v.cbegin() == 1);
            REQUIRE(*(v.cbegin() + 1) == 2);
            REQUIRE(*(v.cend() - 1) == 4);
            REQUIRE(*(v.cend() - 2) == 3);
            REQUIRE(v.cbegin() + 4 == v.cend());
            REQUIRE(v.cend() - 4 == v.cbegin());

            REQUIRE(*v.rbegin() == 4);
            REQUIRE(*(v.rbegin() + 1) == 3);
            REQUIRE(*(v.rend() - 1) == 1);
            REQUIRE(*(v.rend() - 2) == 2);
            REQUIRE(v.rbegin() + 4 == v.rend());
            REQUIRE(v.rend() - 4 == v.rbegin());

            REQUIRE(*v.crbegin() == 4);
            REQUIRE(*(v.crbegin() + 1) == 3);
            REQUIRE(*(v.crend() - 1) == 1);
            REQUIRE(*(v.crend() - 2) == 2);
            REQUIRE(v.crbegin() + 4 == v.crend());
            REQUIRE(v.crend() - 4 == v.crbegin());

            *v.begin() = 3;
            REQUIRE(v == fqua{3,2,3,4});
            *v.rbegin() = 5;
            REQUIRE(v == fqua{3,2,3,5});
        }
        {
            const fqua v{1,2,3,4};

            REQUIRE(*v.begin() == 1);
            REQUIRE(*(v.begin() + 1) == 2);
            REQUIRE(*(v.end() - 1) == 4);
            REQUIRE(*(v.end() - 2) == 3);
            REQUIRE(v.begin() + 4 == v.end());
            REQUIRE(v.end() - 4 == v.begin());

            REQUIRE(*v.cbegin() == 1);
            REQUIRE(*(v.cbegin() + 1) == 2);
            REQUIRE(*(v.cend() - 1) == 4);
            REQUIRE(*(v.cend() - 2) == 3);
            REQUIRE(v.cbegin() + 4 == v.cend());
            REQUIRE(v.cend() - 4 == v.cbegin());

            REQUIRE(*v.rbegin() == 4);
            REQUIRE(*(v.rbegin() + 1) == 3);
            REQUIRE(*(v.rend() - 1) == 1);
            REQUIRE(*(v.rend() - 2) == 2);
            REQUIRE(v.rbegin() + 4 == v.rend());
            REQUIRE(v.rend() - 4 == v.rbegin());

            REQUIRE(*v.crbegin() == 4);
            REQUIRE(*(v.crbegin() + 1) == 3);
            REQUIRE(*(v.crend() - 1) == 1);
            REQUIRE(*(v.crend() - 2) == 2);
            REQUIRE(v.crbegin() + 4 == v.crend());
            REQUIRE(v.crend() - 4 == v.crbegin());
        }
    }

    SECTION("data") {
        {
            fqua i2;
            REQUIRE(i2.data() == &i2[0]);
        }
        {
            const fqua i2;
            REQUIRE(i2.data() == &i2[0]);
        }
    }

    SECTION("operator[]") {
        {
            STATIC_REQUIRE(qua(1,2,3,4).v == vec(1,2,3));
            STATIC_REQUIRE(qua(1,2,3,4).s == 4);
        }
        {
            STATIC_REQUIRE(qua(1,2,3,4)[0] == 1);
            STATIC_REQUIRE(qua(1,2,3,4)[1] == 2);
            STATIC_REQUIRE(qua(1,2,3,4)[2] == 3);
            STATIC_REQUIRE(qua(1,2,3,4)[3] == 4);
        }
        {
            qua<int> v;
            v.v = vec(1,2,3);
            v.s = 4;
            REQUIRE(v == qua(1,2,3,4));
        }
    }

    SECTION("at") {
        STATIC_REQUIRE(fqua(1,2,3,4).at(0) == 1);
        STATIC_REQUIRE(fqua(1,2,3,4).at(1) == 2);
        STATIC_REQUIRE(fqua(1,2,3,4).at(2) == 3);
        STATIC_REQUIRE(fqua(1,2,3,4).at(3) == 4);
        REQUIRE_THROWS_AS((void)fqua(1,2,3,4).at(4), std::out_of_range);
    }

    SECTION("operator==/operator!=") {
        STATIC_REQUIRE(fqua(1,2,3,4) == fqua(1,2,3,4));
        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) == fqua(2,2,3,4));
        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) == fqua(1,3,3,4));

        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) != fqua(1,2,3,4));
        STATIC_REQUIRE(fqua(1,2,3,4) != fqua(2,2,3,4));
        STATIC_REQUIRE(fqua(1,2,3,4) != fqua(1,3,3,4));
    }

    SECTION("operator<") {
        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) < fqua(1,2,3,4));

        STATIC_REQUIRE(fqua(0,2,3,4) < fqua(1,2,3,4));
        STATIC_REQUIRE(fqua(1,1,3,4) < fqua(1,2,3,4));
        STATIC_REQUIRE(fqua(1,2,2,4) < fqua(1,2,3,4));
        STATIC_REQUIRE(fqua(1,2,3,3) < fqua(1,2,3,4));

        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) < fqua(0,2,3,4));
        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) < fqua(1,1,3,4));
        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) < fqua(1,2,2,4));
        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) < fqua(1,2,3,3));

        STATIC_REQUIRE(fqua(0,3,3,4) < fqua(1,2,3,4));
        STATIC_REQUIRE_FALSE(fqua(1,2,3,4) < fqua(0,3,3,4));
    }
}
