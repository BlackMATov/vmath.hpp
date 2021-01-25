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

TEST_CASE("vmath/qua_fun") {
    SUBCASE("Operators") {
        STATIC_REQUIRE(+qua(1,-2,3,-4) == qua(1,-2,3,-4));
        STATIC_REQUIRE(-qua(1,-2,3,-4) == qua(-1,2,-3,4));

        STATIC_REQUIRE(qua(1,2,3,4) + qua(3,4,5,6) == qua(4,6,8,10));
        STATIC_REQUIRE(qua(1,2,3,4) - qua(3,5,7,9) == qua(-2,-3,-4,-5));

        {
            qua v{1,2,3,4};
            REQUIRE(&v == &(v += qua{3,4,5,6}));
            REQUIRE(v == qua{4,6,8,10});
        }

        {
            qua v{1,2,3,4};
            REQUIRE(&v == &(v -= qua{3,4,5,6}));
            REQUIRE(v == qua{-2,-2,-2,-2});
        }

        STATIC_REQUIRE(qua(1,2,3,4) * 2 == qua(2,4,6,8));
        STATIC_REQUIRE(qua(2,4,6,8) / 2 == qua(1,2,3,4));

        STATIC_REQUIRE(2 * qua(1,2,3,4) == qua(2,4,6,8));
        STATIC_REQUIRE(8 / qua(1,2,4,8) == qua(8,4,2,1));

        {
            qua v{1,2,3,4};
            REQUIRE(&v == &(v *= 2));
            REQUIRE(v == qua{2,4,6,8});
            REQUIRE(&v == &(v *= qua<int>{}));
            REQUIRE(v == qua{2,4,6,8});
        }

        {
            qua v{2,4,6,8};
            REQUIRE(&v == &(v /= 2));
            REQUIRE(v == qua{1,2,3,4});
        }

        {
            float3 v{1,0,0};
            REQUIRE(&v == &(v *= fqua{0,0,0.7071067812f,0.7071067812f}));
            REQUIRE(v == uapprox3(0.f,1.f,0.f));
        }

        STATIC_REQUIRE(fqua{} * fqua{} == fqua{});
        STATIC_REQUIRE(float3{1,2,3} * fqua{} == uapprox3(1.f,2.f,3.f));
        STATIC_REQUIRE(float3{1,0,0} * fqua{0,0,0.7071067812f,0.7071067812f} == uapprox3(0.f,1.f,0.f));
    }

    SUBCASE("Common Functions") {
        REQUIRE_FALSE(any(isnan(fqua(1,1,1,1))));
        REQUIRE_FALSE(any(isinf(fqua(1,1,1,1))));
        REQUIRE(all(isfinite(fqua(1,1,1,1))));
    }

    SUBCASE("Geometric Functions") {
        STATIC_REQUIRE(dot(qua(1,2,3,4),qua(3,4,5,6)) == 50);

        REQUIRE(length(fqua(10.f,0.f,0.f,0.f)) == uapprox(10.f));
        REQUIRE(length(fqua(-10.f,0.f,0.f,0.f)) == uapprox(10.f));

        STATIC_REQUIRE(length2(fqua(10.f,0.f,0.f,0.f)) == uapprox(100.f));
        STATIC_REQUIRE(length2(fqua(-10.f,0.f,0.f,0.f)) == uapprox(100.f));

        REQUIRE(normalize(fqua(0.5f,0.f,0.f,0.f)).v == uapprox3(1.f,0.f,0.f));
    }
}
