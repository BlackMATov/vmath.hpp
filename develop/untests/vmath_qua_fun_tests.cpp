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

TEST_CASE("vmath/qua_fun") {
    SUBCASE("Operators") {
        STATIC_CHECK(+qua(1,-2,3,-4) == qua(1,-2,3,-4));
        STATIC_CHECK(-qua(1,-2,3,-4) == qua(-1,2,-3,4));

        STATIC_CHECK(qua(1,2,3,4) + qua(3,4,5,6) == qua(4,6,8,10));
        STATIC_CHECK(qua(1,2,3,4) - qua(3,5,7,9) == qua(-2,-3,-4,-5));

        {
            qua v{1,2,3,4};
            CHECK(&v == &(v += qua{3,4,5,6}));
            CHECK(v == qua{4,6,8,10});
        }

        {
            qua v{1,2,3,4};
            CHECK(&v == &(v -= qua{3,4,5,6}));
            CHECK(v == qua{-2,-2,-2,-2});
        }

        STATIC_CHECK(qua(1,2,3,4) * 2 == qua(2,4,6,8));
        STATIC_CHECK(qua(2,4,6,8) / 2 == qua(1,2,3,4));

        STATIC_CHECK(2 * qua(1,2,3,4) == qua(2,4,6,8));
        STATIC_CHECK(8 / qua(1,2,4,8) == qua(8,4,2,1));

        {
            qua v{1,2,3,4};
            CHECK(&v == &(v *= 2));
            CHECK(v == qua{2,4,6,8});
            CHECK(&v == &(v *= qua<int>{}));
            CHECK(v == qua{2,4,6,8});
        }

        {
            qua v{2,4,6,8};
            CHECK(&v == &(v /= 2));
            CHECK(v == qua{1,2,3,4});
        }

        {
            fvec3 v{1,0,0};
            CHECK(&v == &(v *= fqua{0,0,0.7071067812f,0.7071067812f}));
            CHECK(v == uapprox3(0.f,1.f,0.f));
        }

        STATIC_CHECK(fqua{} * fqua{} == fqua{});
        STATIC_CHECK(fvec3{1,2,3} * fqua{} == uapprox3(1.f,2.f,3.f));
        STATIC_CHECK(fvec3{1,0,0} * fqua{0,0,0.7071067812f,0.7071067812f} == uapprox3(0.f,1.f,0.f));
    }

    SUBCASE("Operators2") {
        STATIC_CHECK(fqua{} + dqua{} == dqua{0,0,0,2});
        STATIC_CHECK(fqua{} - dqua{} == dqua{0,0,0,0});

        STATIC_CHECK(fqua{} * 1.0 == dqua{});
        STATIC_CHECK(1.0 * fqua{} == dqua{});
        STATIC_CHECK(fvec3{} * dqua{} == dvec3{});
        STATIC_CHECK(fqua{} * dqua{} == dqua{});

        STATIC_CHECK(fqua{} / 1.0 == dqua{});
        STATIC_CHECK(1.0 / fqua{1,1,1,1} == dqua{1,1,1,1});
    }

    SUBCASE("Conversions2") {
        STATIC_CHECK(dqua(1,2.f,3.0,4u) == dqua(1,2,3,4));
        STATIC_CHECK(dqua(ivec3(1,2,3),4u) == dqua(1,2,3,4));
        STATIC_CHECK(dqua(ivec4(1,2,3,4)) == dqua(1,2,3,4));
        STATIC_CHECK(dqua(fqua(1,2,3,4)) == dqua(1,2,3,4));

        STATIC_CHECK(fvec4(fqua(1,2,3,4)) == fvec4(1,2,3,4));
        STATIC_CHECK(dvec4(fqua(1,2,3,4)) == dvec4(1,2,3,4));
    }

    SUBCASE("Common Functions") {
        {
            CHECK(all(approx(
                qrotate_z(radians(5.f)),
                nlerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.f),
                0.0001f)));
            CHECK(all(approx(
                qrotate_z(radians(6.f)),
                nlerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.1f),
                0.0001f)));
            CHECK(all(approx(
                qrotate_z(radians(10.f)),
                nlerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.5f),
                0.0001f)));
            CHECK(all(approx(
                qrotate_z(radians(15.f)),
                nlerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 1.f),
                0.0001f)));

            CHECK(all(approx(
                qrotate_z(radians(315.f)),
                nlerp(qrotate_z(radians(270.f)), qrotate_z(radians(0.f)), 0.5f))));
            CHECK(all(approx(
                qrotate_z(radians(290.f)),
                nlerp(qrotate_z(radians(220.f)), qrotate_z(radians(0.f)), 0.5f))));
        }
        {
            CHECK(all(approx(
                qrotate_z(radians(5.f)),
                slerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.f),
                0.0001f)));
            CHECK(all(approx(
                qrotate_z(radians(6.f)),
                slerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.1f),
                0.0001f)));
            CHECK(all(approx(
                qrotate_z(radians(10.f)),
                slerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 0.5f),
                0.0001f)));
            CHECK(all(approx(
                qrotate_z(radians(15.f)),
                slerp(qrotate_z(radians(5.f)), qrotate_z(radians(15.f)), 1.f),
                0.0001f)));

            CHECK(all(approx(
                qrotate_z(radians(0.f)),
                slerp(qrotate_z(radians(0.f)), qrotate_z(radians(0.f)), 0.5f))));
            CHECK(all(approx(
                qrotate_z(radians(0.25f)),
                slerp(qrotate_z(radians(0.f)), qrotate_z(radians(0.5f)), 0.5f))));

            CHECK(all(approx(
                qrotate_z(radians(-45.f)),
                slerp(qrotate_z(radians(0.f)), qrotate_z(radians(270.f)), 0.5f))));
            CHECK(all(approx(
                qrotate_z(radians(-70.f)),
                slerp(qrotate_z(radians(0.f)), qrotate_z(radians(220.f)), 0.5f))));

            CHECK(all(approx(
                qrotate_z(radians(315.f)),
                slerp(qrotate_z(radians(270.f)), qrotate_z(radians(0.f)), 0.5f))));
            CHECK(all(approx(
                qrotate_z(radians(290.f)),
                slerp(qrotate_z(radians(220.f)), qrotate_z(radians(0.f)), 0.5f))));
        }
    }

    SUBCASE("Geometric Functions") {
        STATIC_CHECK(dot(qua(1,2,3,4),qua(3,4,5,6)) == 50);
        STATIC_CHECK(dot(fqua(1,2,3,4),dqua(3,4,5,6)) == uapprox(50.0));

        CHECK(length(fqua(10.f,0.f,0.f,0.f)) == uapprox(10.f));
        CHECK(length(fqua(-10.f,0.f,0.f,0.f)) == uapprox(10.f));

        CHECK(rlength(fqua(10.f,0.f,0.f,0.f)) == uapprox(0.1f));
        CHECK(rlength(fqua(-10.f,0.f,0.f,0.f)) == uapprox(0.1f));

        STATIC_CHECK(length2(fqua(10.f,0.f,0.f,0.f)) == uapprox(100.f));
        STATIC_CHECK(length2(fqua(-10.f,0.f,0.f,0.f)) == uapprox(100.f));

        STATIC_CHECK(rlength2(fqua(10.f,0.f,0.f,0.f)) == uapprox(0.01f));
        STATIC_CHECK(rlength2(fqua(-10.f,0.f,0.f,0.f)) == uapprox(0.01f));

        CHECK(distance(qrotate_z(radians(0.f)) * 2.f, qrotate_z(radians(0.f)) * 1.5f) == uapprox(radians(0.f)));
        CHECK(distance(qrotate_z(radians(0.f)) * 3.f, qrotate_z(radians(360.f)) * 2.5f) == uapprox(radians(0.f)));
        CHECK(distance(qrotate_z(radians(0.f)) * 4.f, qrotate_z(radians(180.f)) * 3.5f) == uapprox(radians(180.f)));
        CHECK(distance(qrotate_z(radians(180.f)) * 5.f, qrotate_z(radians(0.f)) * 4.5f) == uapprox(radians(180.f)));
        CHECK(distance(qrotate_z(radians(15.f)) * 6.f, qrotate_z(radians(350.f)) * 5.5f) == uapprox(radians(25.f)));
        CHECK(distance(qrotate_z(radians(350.f)) * 7.f, qrotate_z(radians(15.f)) * 6.5f) == uapprox(radians(25.f)));

        CHECK(normalize(fqua(0.5f,0.f,0.f,0.f)).v == uapprox3(1.f,0.f,0.f));
    }

    SUBCASE("Relational Functions") {
        STATIC_CHECK(any(qua(1,0,0,0)));
        STATIC_CHECK(any(qua(0,1,0,0)));
        STATIC_CHECK(any(qua(0,0,1,0)));
        STATIC_CHECK(any(qua(0,0,0,1)));
        STATIC_CHECK(any(qua(1,1,1,1)));
        STATIC_CHECK_FALSE(any(qua(0,0,0,0)));

        STATIC_CHECK_FALSE(all(qua(1,0,0,0)));
        STATIC_CHECK_FALSE(all(qua(0,1,0,0)));
        STATIC_CHECK_FALSE(all(qua(0,0,1,0)));
        STATIC_CHECK(all(qua(1,1,1,1)));
        STATIC_CHECK_FALSE(all(qua(0,0,0,0)));

        STATIC_CHECK(approx(qua(1,1,1,1), qua(0,1,2,3)) == bvec4(false, true, false, false));
        STATIC_CHECK(approx(qua(1,1,1,1), qua(0,1,2,3), 0) == bvec4(false, true, false, false));
        STATIC_CHECK(approx(qua(1,1,1,1), qua(0,1,2,3), 1) == bvec4(true, true, true, false));
        STATIC_CHECK(approx(qua(1,1,1,1), qua(0,1,2,3), 2) == bvec4(true, true, true, true));

        STATIC_CHECK(less(qua(1,1,1,1), qua(0,1,2,3)) == bvec4(false, false, true, true));
        STATIC_CHECK(less_equal(qua(1,1,1,1), qua(0,1,2,3)) == bvec4(false, true, true, true));
        STATIC_CHECK(greater(qua(1,1,1,1), qua(0,1,2,3)) == bvec4(true, false, false, false));
        STATIC_CHECK(greater_equal(qua(1,1,1,1), qua(0,1,2,3)) == bvec4(true, true, false, false));

        STATIC_CHECK(equal_to(qua(1,1,1,1), qua(0,1,2,3)) == bvec4(false, true, false, false));
        STATIC_CHECK(not_equal_to(qua(1,1,1,1), qua(0,1,2,3)) == bvec4(true, false, true, true));
    }

    SUBCASE("Quaternion Functions") {
        STATIC_CHECK(conjugate(qua(1,2,3,4)) == qua(-1,-2,-3,4));
        STATIC_CHECK(inverse(qua(0.f,0.f,0.7071067812f,0.7071067812f)).v == uapprox3(0.f,0.f,-0.7071067812f));
        STATIC_CHECK(inverse(qua(0.f,0.f,0.7071067812f,0.7071067812f)).s == uapprox(0.7071067812f));

        CHECK(inverse(qrotate_x(10.f)) == qrotate_x(-10.f));
        CHECK(all(approx(inverse(qrotate_x(10.f) * qrotate_y(15.f)), qrotate_y(-15.f) * qrotate_x(-10.f))));
    }
}
