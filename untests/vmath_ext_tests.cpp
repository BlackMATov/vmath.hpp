/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;

    constexpr float pi = radians(180.f);
    constexpr float pi_2 = radians(90.f);
    constexpr float pi_4 = radians(45.f);
}

TEST_CASE("vmath/ext/units") {
    STATIC_CHECK(zero2<int> == ivec2(0,0));
    STATIC_CHECK(zero3<int> == ivec3(0,0,0));
    STATIC_CHECK(zero4<int> == ivec4(0,0,0,0));

    STATIC_CHECK(unit2<int> == ivec2(1,1));
    STATIC_CHECK(unit2_x<int> == ivec2(1,0));
    STATIC_CHECK(unit2_y<int> == ivec2(0,1));

    STATIC_CHECK(unit3<int> == ivec3(1,1,1));
    STATIC_CHECK(unit3_x<int> == ivec3(1,0,0));
    STATIC_CHECK(unit3_y<int> == ivec3(0,1,0));
    STATIC_CHECK(unit3_z<int> == ivec3(0,0,1));

    STATIC_CHECK(unit4<int> == ivec4(1,1,1,1));
    STATIC_CHECK(unit4_x<int> == ivec4(1,0,0,0));
    STATIC_CHECK(unit4_y<int> == ivec4(0,1,0,0));
    STATIC_CHECK(unit4_z<int> == ivec4(0,0,1,0));
    STATIC_CHECK(unit4_w<int> == ivec4(0,0,0,1));

    STATIC_CHECK(zero2x2<int> == imat2(0,0,0,0));
    STATIC_CHECK(zero3x3<int> == imat3(0,0,0,0,0,0,0,0,0));
    STATIC_CHECK(zero4x4<int> == imat4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0));

    STATIC_CHECK(unit2x2<int> == imat2(1,1,1,1));
    STATIC_CHECK(unit3x3<int> == imat3(1,1,1,1,1,1,1,1,1));
    STATIC_CHECK(unit4x4<int> == imat4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1));

    STATIC_CHECK(identity2x2<int> == imat2());
    STATIC_CHECK(identity3x3<int> == imat3());
    STATIC_CHECK(identity4x4<int> == imat4());

    STATIC_CHECK(qzero<float> == fqua(zero_init));
    STATIC_CHECK(qidentity<float> == fqua(identity_init));
}

TEST_CASE("vmath/ext/hash") {
    SUBCASE("vector") {
        CHECK(std::hash<ivec2>{}({1,2}) == std::hash<ivec2>{}({1,2}));
        CHECK_FALSE(std::hash<ivec2>{}({1,2}) == std::hash<ivec2>{}({2,1}));

        CHECK(std::hash<ivec3>{}({1,2,3}) == std::hash<ivec3>{}({1,2,3}));
        CHECK_FALSE(std::hash<ivec3>{}({1,2,3}) == std::hash<ivec3>{}({3,2,1}));

        CHECK(std::hash<ivec4>{}({1,2,3,4}) == std::hash<ivec4>{}({1,2,3,4}));
        CHECK_FALSE(std::hash<ivec4>{}({1,2,3,4}) == std::hash<ivec4>{}({3,2,1,4}));

        {
            std::set<ivec2> s;
            s.insert(ivec2(1,2));
            CHECK(s.count(ivec2(1,2)) > 0);
            CHECK_FALSE(s.count(ivec2(1,1)) > 0);
        }
        {
            std::map<ivec2, int> s;
            s.emplace(ivec2(1,2),3);
            s.emplace(ivec2(2,3),5);
            CHECK(s[ivec2(1,2)] == 3);
            CHECK(s[ivec2(2,3)] == 5);
        }
        {
            std::unordered_set<ivec2> s;
            s.insert(ivec2(1,2));
            CHECK(s.count(ivec2(1,2)) > 0);
            CHECK_FALSE(s.count(ivec2(1,1)) > 0);
        }
        {
            std::unordered_map<ivec2, int> s;
            s.emplace(ivec2(1,2),3);
            s.emplace(ivec2(2,3),5);
            CHECK(s[ivec2(1,2)] == 3);
            CHECK(s[ivec2(2,3)] == 5);
        }
    }

    SUBCASE("matrix") {
        CHECK(std::hash<imat2>{}({1,2,3,4}) == std::hash<imat2>{}({1,2,3,4}));
        CHECK_FALSE(std::hash<imat2>{}({1,2,3,4}) == std::hash<imat2>{}({1,2,4,3}));

        {
            std::set<imat2> s;
            s.insert(imat2(1,2,3,4));
            CHECK(s.count(imat2(1,2,3,4)) > 0);
            CHECK_FALSE(s.count(imat2(1,1,1,1)) > 0);
        }
        {
            std::map<imat2, int> s;
            s.emplace(imat2(1,2,3,4),3);
            s.emplace(imat2(2,3,4,5),5);
            CHECK(s[imat2(1,2,3,4)] == 3);
            CHECK(s[imat2(2,3,4,5)] == 5);
        }
        {
            std::unordered_set<imat2> s;
            s.insert(imat2(1,2,3,4));
            CHECK(s.count(imat2(1,2,3,4)) > 0);
            CHECK_FALSE(s.count(imat2(1,1,1,1)) > 0);
        }
        {
            std::unordered_map<imat2, int> s;
            s.emplace(imat2(1,2,3,4),3);
            s.emplace(imat2(2,3,4,5),5);
            CHECK(s[imat2(1,2,3,4)] == 3);
            CHECK(s[imat2(2,3,4,5)] == 5);
        }
    }

    SUBCASE("quaternion") {
        CHECK(std::hash<fqua>{}({1,2,3,4}) == std::hash<fqua>{}({1,2,3,4}));
        CHECK_FALSE(std::hash<fqua>{}({1,2,3,4}) == std::hash<fqua>{}({3,2,1,4}));

        {
            std::set<qua<int>> s;
            s.insert(qua(1,2,3,4));
            CHECK(s.count(qua(1,2,3,4)) > 0);
            CHECK_FALSE(s.count(qua(1,1,1,1)) > 0);
        }
        {
            std::map<qua<int>, int> s;
            s.emplace(qua(1,2,3,4),3);
            s.emplace(qua(2,3,4,5),5);
            CHECK(s[qua(1,2,3,4)] == 3);
            CHECK(s[qua(2,3,4,5)] == 5);
        }
        {
            std::unordered_set<qua<int>> s;
            s.insert(qua(1,2,3,4));
            CHECK(s.count(qua(1,2,3,4)) > 0);
            CHECK_FALSE(s.count(qua(1,1,1,1)) > 0);
        }
        {
            std::unordered_map<qua<int>, int> s;
            s.emplace(qua(1,2,3,4),3);
            s.emplace(qua(2,3,4,5),5);
            CHECK(s[qua(1,2,3,4)] == 3);
            CHECK(s[qua(2,3,4,5)] == 5);
        }
    }
}

TEST_CASE("vmath/ext/cast") {
    SUBCASE("cast_to") {
        constexpr auto i = cast_to<int>(1.5f);
        STATIC_CHECK(i == 1);
        STATIC_CHECK(std::is_same_v<decltype(i), const int>);

        constexpr auto v = cast_to<int>(fvec2(1.5f));
        STATIC_CHECK(v == ivec2(1));
        STATIC_CHECK(std::is_same_v<decltype(v)::component_type, int>);

        constexpr auto m = cast_to<int>(fmat2(1.5f));
        STATIC_CHECK(m == imat2(1));
        STATIC_CHECK(std::is_same_v<decltype(m)::row_type, ivec2>);

        constexpr auto q = cast_to<int>(fqua(1.5f, 2.2f, 3.6f, 4.5f));
        STATIC_CHECK(q == qua(1,2,3,4));
        STATIC_CHECK(std::is_same_v<decltype(q)::component_type, int>);
    }
}

TEST_CASE("vmath/ext/access") {
    SUBCASE("component") {
        STATIC_CHECK(component(ivec2{1,2}, 0) == 1);
        STATIC_CHECK(component(ivec2{1,2}, 1) == 2);

        STATIC_CHECK(component(ivec2{0,0}, 0, 1) == ivec2{1,0});
        STATIC_CHECK(component(ivec2{0,0}, 1, 2) == ivec2{0,2});
    }

    SUBCASE("row") {
        STATIC_CHECK(row(imat2(1,2,3,4), 0) == ivec2(1,2));
        STATIC_CHECK(row(imat2(1,2,3,4), 1) == ivec2(3,4));

        STATIC_CHECK(row(imat2(), 0, {1,2}) == imat2(1,2,0,1));
        STATIC_CHECK(row(imat2(), 1, {3,4}) == imat2(1,0,3,4));
    }

    SUBCASE("column") {
        STATIC_CHECK(column(imat2(1,2,3,4), 0) == ivec2(1,3));
        STATIC_CHECK(column(imat2(1,2,3,4), 1) == ivec2(2,4));

        STATIC_CHECK(column(imat2(), 0, {2,3}) == imat2(2,0,3,1));
        STATIC_CHECK(column(imat2(), 1, {3,4}) == imat2(1,3,0,4));
    }

    SUBCASE("real") {
        STATIC_CHECK(real(qua{1,2,3,4}) == 4);
        STATIC_CHECK(real(qua{1,2,3,4}, 5) == qua{1,2,3,5});
    }

    SUBCASE("imag") {
        STATIC_CHECK(imag(qua{1,2,3,4}) == vec{1,2,3});
        STATIC_CHECK(imag(qua{1,2,3,4}, {4,3,2}) == qua{4,3,2,4});
    }
}

TEST_CASE("vmath/ext/matrix_transform") {
    SUBCASE("translate") {
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * translate(fvec2{1.f,2.f}) == uapprox3(3.f,5.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * translate(translate(fvec2{1.f,2.f}), fvec2{1.f,2.f}) == uapprox3(4.f,7.f,1.f));

        STATIC_CHECK(fvec4(2.f,3.f,4.f,1.f) * translate(fvec3{1.f,2.f,3.f}) == uapprox4(3.f,5.f,7.f,1.f));
        STATIC_CHECK(fvec4(2.f,3.f,4.f,1.f) * translate(translate(fvec3{1.f,2.f,3.f}), fvec3{1.f,2.f,3.f}) == uapprox4(4.f,7.f,10.f,1.f));
    }

    SUBCASE("rotate") {
        CHECK(fvec4(0.f,1.f,0.f,1.f) * rotate_x(pi_2) == uapprox4(0.f,0.f,1.f,1.f));
        CHECK(fvec4(0.f,0.f,1.f,1.f) * rotate_y(pi_2) == uapprox4(1.f,0.f,0.f,1.f));
        CHECK(fvec4(1.f,0.f,0.f,1.f) * rotate_z(pi_2) == uapprox4(0.f,1.f,0.f,1.f));

        CHECK(fvec4(0.f,1.f,0.f,1.f) * rotate_x(rotate_x(pi_4),pi_4) == uapprox4(0.f,0.f,1.f,1.f));
        CHECK(fvec4(0.f,0.f,1.f,1.f) * rotate_y(rotate_y(pi_4),pi_4) == uapprox4(1.f,0.f,0.f,1.f));
        CHECK(fvec4(1.f,0.f,0.f,1.f) * rotate_z(rotate_z(pi_4),pi_4) == uapprox4(0.f,1.f,0.f,1.f));

        CHECK(fvec3(2.f,3.f,1.f) * rotate(pi) == uapprox3(-2.f,-3.f,1.f));
        CHECK(fvec4(2.f,3.f,4.f,1.f) * rotate(pi,{0.f,0.f,1.f}) == uapprox4(-2.f,-3.f,4.f,1.f));
        CHECK(fvec4(2.f,3.f,4.f,1.f) * rotate(pi,fvec3{0.f,0.f,1.f}) == uapprox4(-2.f,-3.f,4.f,1.f));
        CHECK(fvec4(2.f,3.f,4.f,1.f) * rotate(qrotate(pi,fvec3{0.f,0.f,1.f})) == uapprox4(-2.f,-3.f,4.f,1.f));

        CHECK(fvec3(2.f,3.f,1.f) * rotate(rotate(pi_2),pi_2) == uapprox3(-2.f,-3.f,1.f));
        CHECK(fvec4(2.f,3.f,4.f,1.f) * rotate(rotate(pi_2,{0.f,0.f,1.f}),pi_2,{0.f,0.f,1.f}) == uapprox4(-2.f,-3.f,4.f,1.f));
        CHECK(fvec4(2.f,3.f,4.f,1.f) * rotate(rotate(pi_2,fvec3{0.f,0.f,1.f}),pi_2,fvec3{0.f,0.f,1.f}) == uapprox4(-2.f,-3.f,4.f,1.f));
        CHECK(fvec4(2.f,3.f,4.f,1.f) * rotate(rotate(qrotate(pi_2,fvec3{0.f,0.f,1.f})),qrotate(pi_2,fvec3{0.f,0.f,1.f})) == uapprox4(-2.f,-3.f,4.f,1.f));
    }

    SUBCASE("scale") {
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * scale(fvec2{2.f,3.f}) == uapprox3(4.f,9.f,1.f));
        STATIC_CHECK(fvec4(2.f,3.f,4.f,1.f) * scale(fvec3{2.f,3.f,4.f}) == uapprox4(4.f,9.f,16.f,1.f));
        STATIC_CHECK(fvec4(2.f,3.f,4.f,1.f) * scale(fvec3{2.f,3.f,4.f}) == uapprox4(4.f,9.f,16.f,1.f));

        STATIC_CHECK(fvec3(2.f,3.f,1.f) * scale(scale(fvec2{2.f,2.f}), {2.f,3.f}) == uapprox3(8.f,18.f,1.f));
        STATIC_CHECK(fvec4(2.f,3.f,4.f,1.f) * scale(scale(fvec3{2.f,2.f,2.f}), {2.f,3.f,4.f}) == uapprox4(8.f,18.f,32.f,1.f));
        STATIC_CHECK(fvec4(2.f,3.f,4.f,1.f) * scale(scale(fvec3{2.f,2.f,2.f}), fvec3{2.f,3.f,4.f}) == uapprox4(8.f,18.f,32.f,1.f));
    }

    SUBCASE("shear") {
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear_x(0.f) == uapprox3(2.f,3.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear_x(1.f) == uapprox3(5.f,3.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear_x(2.f) == uapprox3(8.f,3.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear_x(shear_x(1.f),1.f) == uapprox3(8.f,3.f,1.f));

        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear_y(0.f) == uapprox3(2.f,3.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear_y(1.f) == uapprox3(2.f,5.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear_y(2.f) == uapprox3(2.f,7.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear_y(shear_y(1.f),1.f) == uapprox3(2.f,7.f,1.f));

        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear(fvec2(0.f,0.f)) == uapprox3(2.f,3.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear(fvec2(2.f,0.f)) == uapprox3(8.f,3.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear(fvec2(0.f,2.f)) == uapprox3(2.f,7.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear(shear(fvec2(1.f,0.f)),fvec2(1.f,0.f)) == uapprox3(8.f,3.f,1.f));
        STATIC_CHECK(fvec3(2.f,3.f,1.f) * shear(shear(fvec2(0.f,1.f)),fvec2(0.f,1.f)) == uapprox3(2.f,7.f,1.f));
    }

    SUBCASE("matrix look_at") {
        (void)look_at_lh(fvec3(1,2,3), fvec3(0,0,0), fvec3(0,2,0));
        (void)look_at_rh(fvec3(1,2,3), fvec3(0,0,0), fvec3(0,2,0));
    }
}

TEST_CASE("vmath/ext/matrix_projections") {
    SUBCASE("orthographic") {
        CHECK(all(approx(
            orthographic_lh(800.f, 600.f, 5.f, 10.f),
            scale(1.f,1.f,-1.f) * orthographic_rh(800.f, 600.f, 5.f, 10.f))));

        CHECK(all(approx(
            orthographic_lh(100.f, 800.f, 50.f, 640.f, 5.f, 10.f),
            scale(1.f,1.f,-1.f) * orthographic_rh(100.f, 800.f, 50.f, 640.f, 5.f, 10.f))));
    }


    SUBCASE("perspective") {
        CHECK(all(approx(
            perspective_lh(800.f, 600.f, 5.f, 10.f),
            scale(1.f,1.f,-1.f) * perspective_rh(800.f, 600.f, 5.f, 10.f))));

        CHECK(all(approx(
            perspective_fov_lh(1.5f, 1.3f, 0.f, 10.f),
            scale(1.f,1.f,-1.f) * perspective_fov_rh(1.5f, 1.3f, 0.f, 10.f))));

        CHECK(all(approx(
            perspective_lh(100.f, 800.f, 50.f, 600.f, 5.f, 10.f),
            scale(1.f,1.f,-1.f) * perspective_rh(100.f, 800.f, 50.f, 600.f, 5.f, 10.f))));
    }
}

TEST_CASE("vmath/ext/vector_transform") {
    SUBCASE("angle") {
        CHECK(angle(fvec2(2.f,0.f), fvec2(0.f,1.f)) == uapprox(radians(90.f)));
        CHECK(angle(fvec2(0.f,3.f), fvec2(1.f,0.f)) == uapprox(radians(90.f)));
        CHECK(angle(fvec2(0.5f,0.f), fvec2(-1.f,0.f)) == uapprox(radians(180.f)));
        CHECK(angle(fvec2(-0.2f,0.f), fvec2(1.f,0.f)) == uapprox(radians(180.f)));
        CHECK(angle(fvec3(0.f,2.f,0.f), fvec3(0.f,0.f,1.f)) == uapprox(radians(90.f)));
        CHECK(angle(fvec3(0.f,0.f,3.f), fvec3(0.f,1.f,0.f)) == uapprox(radians(90.f)));
    }

    SUBCASE("rotate") {
        CHECK(rotate(fvec2(2.f,0.f), radians(90.f)) == uapprox2(0.f,2.f));
        CHECK(rotate(fvec2(1.5f,0.f), radians(-90.f)) == uapprox2(0.f,-1.5f));

        CHECK(rotate_x(fvec3(0.f,1.5f,0.f), radians(90.f)) == uapprox3(0.f,0.f,1.5f));
        CHECK(rotate_y(fvec3(0.f,0.f,1.5f), radians(90.f)) == uapprox3(1.5f,0.f,0.f));
        CHECK(rotate_z(fvec3(1.5f,0.f,0.f), radians(90.f)) == uapprox3(0.f,1.5f,0.f));

        CHECK(rotate(fvec3(1.5f,0.f,0.f), qrotate_z(radians(90.f))) == uapprox3(0.f,1.5f,0.f));
        CHECK(rotate(fvec3(1.5f,0.f,0.f), radians(90.f), fvec3(0,0,1)) == uapprox3(0.f,1.5f,0.f));
    }

    SUBCASE("project") {
        STATIC_CHECK(project(fvec2(2.f, 2.f), fvec2(0.f, 1.f)) == uapprox2(0.f, 2.f));
        STATIC_CHECK(project(fvec3(2.f, 2.f, 2.f), fvec3(0.f, 0.f, 1.f)) == uapprox3(0.f, 0.f, 2.f));
    }

    SUBCASE("perpendicular") {
        STATIC_CHECK(perpendicular(fvec2(2.f, 2.f), fvec2(0.f, 1.f)) == uapprox2(2.f, 0.f));
        STATIC_CHECK(perpendicular(fvec3(2.f, 2.f, 2.f), fvec3(0.f, 0.f, 1.f)) == uapprox3(2.f, 2.f, 0.f));
    }
}

TEST_CASE("vmath/ext/quaternion_transform") {
    SUBCASE("qrotate(m)") {
        CHECK(all(approx(
            vec{4.f,3.f,2.f,1.f} * rotate(qrotate(fmat3(rotate(0.f, vec{1.f,2.f,3.f})))),
            vec{4.f,3.f,2.f,1.f} * rotate(0.f, vec{1.f,2.f,3.f}), 0.001f)));
        CHECK(all(approx(
            vec{4.f,3.f,2.f,1.f} * rotate(qrotate(fmat3(rotate(radians(12.5f), vec{1.f,2.f,3.f})))),
            vec{4.f,3.f,2.f,1.f} * rotate(radians(12.5f), vec{1.f,2.f,3.f}), 0.001f)));
        CHECK(all(approx(
            vec{4.f,3.f,2.f,1.f} * rotate(qrotate(fmat3(rotate(radians(-190.5f), vec{1.f,2.f,3.f})))),
            vec{4.f,3.f,2.f,1.f} * rotate(radians(-190.5f), vec{1.f,2.f,3.f}), 0.001f)));
    }

    SUBCASE("qrotate(q, m)") {
        CHECK(all(approx(
            vec{4.f,3.f,2.f} * qrotate(
                qrotate(fmat3(rotate(0.f, vec{1.f,2.f,3.f}))),
                fmat3(rotate(0.f, vec{3.f,2.f,1.f}))),
            vec{4.f,3.f,2.f} *
                fmat3(rotate(0.f, vec{1.f,2.f,3.f})) *
                fmat3(rotate(0.f, vec{3.f,2.f,1.f})))));
    }

    SUBCASE("qrotate(from, to)") {
        CHECK(+unit3_x<float> * qrotate(-unit3_x<float>, +unit3_x<float>) == uapprox3(-unit3_x<float>));
        CHECK(-unit3_y<float> * qrotate(+unit3_y<float>, -unit3_y<float>) == uapprox3(+unit3_y<float>));
        CHECK(+unit3_z<float> * qrotate(-unit3_z<float>, +unit3_z<float>) == uapprox3(-unit3_z<float>));
        CHECK(vec{1.f,2.f,3.f} * qrotate(vec{1.f,2.f,3.f}, vec{-2.f,1.f,3.f}) == uapprox3(-2.f,1.f,3.f));
        CHECK(vec{-2.f,1.f,3.f} * qrotate(vec{-2.f,1.f,3.f}, vec{1.f,2.f,3.f}) == uapprox3(1.f,2.f,3.f));
    }

    SUBCASE("qrotate(q, from, to)") {
        CHECK(vec{1.f,2.f,3.f} *
            inverse(qrotate(fmat3(rotate(radians(12.f), {2.f,2.f,2.f})))) *
            qrotate(
                qrotate(fmat3(rotate(radians(12.f), {2.f,2.f,2.f}))),
                vec{1.f,2.f,3.f},
                vec{-2.f,1.f,3.f}) == uapprox3(vec{-2.f,1.f,3.f}));
    }

    SUBCASE("qrotate(angle, axis)") {
        CHECK(all(approx(
            rotate(12.3f, fvec3(1.f,2.f,3.f)),
            rotate(qrotate(12.3f, fvec3(1.f,2.f,3.f)) * 2.f))));

        CHECK(fvec3(0.f,1.f,0.f) * qrotate_x(pi_2) == uapprox3(0.f,0.f,1.f));
        CHECK(fvec3(0.f,0.f,1.f) * qrotate_y(pi_2) == uapprox3(1.f,0.f,0.f));
        CHECK(fvec3(1.f,0.f,0.f) * qrotate_z(pi_2) == uapprox3(0.f,1.f,0.f));

        CHECK(fvec3(2.f,3.f,4.f) * qrotate(pi,{0.f,0.f,1.f}) == uapprox3(-2.f,-3.f,4.f));
        CHECK(fvec3(2.f,3.f,4.f) * qrotate(pi,fvec3{0.f,0.f,1.f}) == uapprox3(-2.f,-3.f,4.f));

        CHECK(qrotate_x(12.3f) == qrotate(12.3f, unit3_x<float> * 2.f));
        CHECK(qrotate_y(12.3f) == qrotate(12.3f, unit3_y<float> * 2.f));
        CHECK(qrotate_z(12.3f) == qrotate(12.3f, unit3_z<float> * 2.f));
    }

    SUBCASE("qrotate(q, angle, axis)") {
        CHECK(fvec3(0.f,1.f,0.f) * qrotate_x(qrotate_x(pi_4),pi_4) == uapprox3(0.f,0.f,1.f));
        CHECK(fvec3(0.f,0.f,1.f) * qrotate_y(qrotate_y(pi_4),pi_4) == uapprox3(1.f,0.f,0.f));
        CHECK(fvec3(1.f,0.f,0.f) * qrotate_z(qrotate_z(pi_4),pi_4) == uapprox3(0.f,1.f,0.f));

        CHECK(fvec3(2.f,3.f,4.f) * qrotate(qrotate(pi_2,{0.f,0.f,1.f}),pi_2,{0.f,0.f,1.f}) == uapprox3(-2.f,-3.f,4.f));
        CHECK(fvec3(2.f,3.f,4.f) * qrotate(qrotate(pi_2,fvec3{0.f,0.f,1.f}),pi_2,fvec3{0.f,0.f,1.f}) == uapprox3(-2.f,-3.f,4.f));
    }

    SUBCASE("qlook_at") {
        CHECK(all(approx(
            qlook_at_lh(fvec3(1.f,2.f,3.f), fvec3(0,1,0)),
            qrotate(fmat3(look_at_lh(fvec3(), fvec3(1.f,2.f,3.f), fvec3(0,1,0)))))));
        CHECK(all(approx(
            qlook_at_rh(fvec3(1.f,2.f,3.f), fvec3(0,1,0)),
            qrotate(fmat3(look_at_rh(fvec3(), fvec3(1.f,2.f,3.f), fvec3(0,1,0)))))));
    }
}
