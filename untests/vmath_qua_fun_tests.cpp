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
            REQUIRE(&v == &(v *= qfloat{0,0,0.7071067812f,0.7071067812f}));
            REQUIRE(v == uapprox3(0.f,1.f,0.f));
        }

        STATIC_REQUIRE(qfloat{} * qfloat{} == qfloat{});
        STATIC_REQUIRE(float3{1,2,3} * qfloat{} == uapprox3(1.f,2.f,3.f));
        STATIC_REQUIRE(float3{1,0,0} * qfloat{0,0,0.7071067812f,0.7071067812f} == uapprox3(0.f,1.f,0.f));
    }

    SUBCASE("Common Functions") {
        {
            REQUIRE(all(approx(
                qrotate_z(radians(5.f)),
                nlerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.f),
                0.00001f)));
            REQUIRE(all(approx(
                qrotate_z(radians(6.f)),
                nlerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.1f),
                0.00001f)));
            REQUIRE(all(approx(
                qrotate_z(radians(10.f)),
                nlerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.5f),
                0.00001f)));
            REQUIRE(all(approx(
                qrotate_z(radians(15.f)),
                nlerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 1.f),
                0.00001f)));

            REQUIRE(all(approx(
                qrotate_z(radians(315.f)),
                nlerp(qrotate_z(radians(270.f)), qrotate_z(radians(0.f)), 0.5f))));
            REQUIRE(all(approx(
                qrotate_z(radians(290.f)),
                nlerp(qrotate_z(radians(220.f)), qrotate_z(radians(0.f)), 0.5f))));
        }
        {
            REQUIRE(all(approx(
                qrotate_z(radians(5.f)),
                slerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.f),
                0.00001f)));
            REQUIRE(all(approx(
                qrotate_z(radians(6.f)),
                slerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.1f),
                0.00001f)));
            REQUIRE(all(approx(
                qrotate_z(radians(10.f)),
                slerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.5f),
                0.00001f)));
            REQUIRE(all(approx(
                qrotate_z(radians(15.f)),
                slerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 1.f),
                0.00001f)));

            REQUIRE(all(approx(
                qrotate_z(radians(0.f)),
                slerp(qrotate_z(radians(0.f)), qrotate_z(radians(0.f)), 0.5f))));
            REQUIRE(all(approx(
                qrotate_z(radians(0.25f)),
                slerp(qrotate_z(radians(0.f)), qrotate_z(radians(0.5f)), 0.5f))));

            REQUIRE(all(approx(
                qrotate_z(radians(-45.f)),
                slerp(qrotate_z(radians(0.f)), qrotate_z(radians(270.f)), 0.5f))));
            REQUIRE(all(approx(
                qrotate_z(radians(-70.f)),
                slerp(qrotate_z(radians(0.f)), qrotate_z(radians(220.f)), 0.5f))));

            REQUIRE(all(approx(
                qrotate_z(radians(315.f)),
                slerp(qrotate_z(radians(270.f)), qrotate_z(radians(0.f)), 0.5f))));
            REQUIRE(all(approx(
                qrotate_z(radians(290.f)),
                slerp(qrotate_z(radians(220.f)), qrotate_z(radians(0.f)), 0.5f))));
        }

        {
            REQUIRE_FALSE(any(isnan(qfloat(1,1,1,1))));
            REQUIRE_FALSE(any(isinf(qfloat(1,1,1,1))));
            REQUIRE(all(isfinite(qfloat(1,1,1,1))));
        }
    }

    SUBCASE("Geometric Functions") {
        STATIC_REQUIRE(dot(qua(1,2,3,4),qua(3,4,5,6)) == 50);

        REQUIRE(length(qfloat(10.f,0.f,0.f,0.f)) == uapprox(10.f));
        REQUIRE(length(qfloat(-10.f,0.f,0.f,0.f)) == uapprox(10.f));

        STATIC_REQUIRE(length2(qfloat(10.f,0.f,0.f,0.f)) == uapprox(100.f));
        STATIC_REQUIRE(length2(qfloat(-10.f,0.f,0.f,0.f)) == uapprox(100.f));

        REQUIRE(distance(qrotate_z(radians(0.f)) * 2.f, qrotate_z(radians(0.f)) * 1.5f) == uapprox(radians(0.f)));
        REQUIRE(distance(qrotate_z(radians(0.f)) * 3.f, qrotate_z(radians(360.f)) * 2.5f) == uapprox(radians(0.f)));
        REQUIRE(distance(qrotate_z(radians(0.f)) * 4.f, qrotate_z(radians(180.f)) * 3.5f) == uapprox(radians(180.f)));
        REQUIRE(distance(qrotate_z(radians(180.f)) * 5.f, qrotate_z(radians(0.f)) * 4.5f) == uapprox(radians(180.f)));
        REQUIRE(distance(qrotate_z(radians(15.f)) * 6.f, qrotate_z(radians(350.f)) * 5.5f) == uapprox(radians(25.f)));
        REQUIRE(distance(qrotate_z(radians(350.f)) * 7.f, qrotate_z(radians(15.f)) * 6.5f) == uapprox(radians(25.f)));

        REQUIRE(normalize(qfloat(0.5f,0.f,0.f,0.f)).v == uapprox3(1.f,0.f,0.f));
    }

    SUBCASE("Relational Functions") {
        STATIC_REQUIRE(approx(qua(1,1,1,1), qua(0,1,2,3)) == bool4(false, true, false, false));
        STATIC_REQUIRE(approx(qua(1,1,1,1), qua(0,1,2,3), 0) == bool4(false, true, false, false));
        STATIC_REQUIRE(approx(qua(1,1,1,1), qua(0,1,2,3), 1) == bool4(true, true, true, false));
        STATIC_REQUIRE(approx(qua(1,1,1,1), qua(0,1,2,3), 2) == bool4(true, true, true, true));

        STATIC_REQUIRE(less(qua(1,1,1,1), qua(0,1,2,3)) == bool4(false, false, true, true));
        STATIC_REQUIRE(less_equal(qua(1,1,1,1), qua(0,1,2,3)) == bool4(false, true, true, true));
        STATIC_REQUIRE(greater(qua(1,1,1,1), qua(0,1,2,3)) == bool4(true, false, false, false));
        STATIC_REQUIRE(greater_equal(qua(1,1,1,1), qua(0,1,2,3)) == bool4(true, true, false, false));

        STATIC_REQUIRE(equal_to(qua(1,1,1,1), qua(0,1,2,3)) == bool4(false, true, false, false));
        STATIC_REQUIRE(not_equal_to(qua(1,1,1,1), qua(0,1,2,3)) == bool4(true, false, true, true));
    }

    SUBCASE("Quaternion Functions") {
        STATIC_REQUIRE(conjugate(qua(1,2,3,4)) == qua(-1,-2,-3,4));
        STATIC_REQUIRE(inverse(qua(0.f,0.f,0.7071067812f,0.7071067812f)).v == uapprox3(0.f,0.f,-0.7071067812f));
        STATIC_REQUIRE(inverse(qua(0.f,0.f,0.7071067812f,0.7071067812f)).s == uapprox(0.7071067812f));

        REQUIRE(inverse(qrotate_x(10.f)) == qrotate_x(-10.f));
        REQUIRE(all(approx(inverse(qrotate_x(10.f) * qrotate_y(15.f)), qrotate_y(-15.f) * qrotate_x(-10.f))));
    }
}
