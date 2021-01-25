/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"
#include "doctest/doctest.hpp"

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/ext") {
    SUBCASE("units") {
        STATIC_REQUIRE(zero2<int> == int2(0,0));
        STATIC_REQUIRE(zero3<int> == int3(0,0,0));
        STATIC_REQUIRE(zero4<int> == int4(0,0,0,0));

        STATIC_REQUIRE(unit2<int> == int2(1,1));
        STATIC_REQUIRE(unit2_x<int> == int2(1,0));
        STATIC_REQUIRE(unit2_y<int> == int2(0,1));

        STATIC_REQUIRE(unit3<int> == int3(1,1,1));
        STATIC_REQUIRE(unit3_x<int> == int3(1,0,0));
        STATIC_REQUIRE(unit3_y<int> == int3(0,1,0));
        STATIC_REQUIRE(unit3_z<int> == int3(0,0,1));

        STATIC_REQUIRE(unit4<int> == int4(1,1,1,1));
        STATIC_REQUIRE(unit4_x<int> == int4(1,0,0,0));
        STATIC_REQUIRE(unit4_y<int> == int4(0,1,0,0));
        STATIC_REQUIRE(unit4_z<int> == int4(0,0,1,0));
        STATIC_REQUIRE(unit4_w<int> == int4(0,0,0,1));

        STATIC_REQUIRE(zero2x2<int> == int2x2(0,0,0,0));
        STATIC_REQUIRE(zero3x3<int> == int3x3(0,0,0,0,0,0,0,0,0));
        STATIC_REQUIRE(zero4x4<int> == int4x4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0));

        STATIC_REQUIRE(unit2x2<int> == int2x2(1,1,1,1));
        STATIC_REQUIRE(unit3x3<int> == int3x3(1,1,1,1,1,1,1,1,1));
        STATIC_REQUIRE(unit4x4<int> == int4x4(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1));

        STATIC_REQUIRE(identity2x2<int> == int2x2());
        STATIC_REQUIRE(identity3x3<int> == int3x3());
        STATIC_REQUIRE(identity4x4<int> == int4x4());
    }

    SUBCASE("vector hash") {
        REQUIRE(std::hash<int2>{}({1,2}) == std::hash<int2>{}({1,2}));
        REQUIRE_FALSE(std::hash<int2>{}({1,2}) == std::hash<int2>{}({2,1}));

        REQUIRE(std::hash<int3>{}({1,2,3}) == std::hash<int3>{}({1,2,3}));
        REQUIRE_FALSE(std::hash<int3>{}({1,2,3}) == std::hash<int3>{}({3,2,1}));

        REQUIRE(std::hash<int4>{}({1,2,3,4}) == std::hash<int4>{}({1,2,3,4}));
        REQUIRE_FALSE(std::hash<int4>{}({1,2,3,4}) == std::hash<int4>{}({3,2,1,4}));

        {
            std::set<int2> s;
            s.insert(int2(1,2));
            REQUIRE(s.count(int2(1,2)) > 0);
            REQUIRE_FALSE(s.count(int2(1,1)) > 0);
        }
        {
            std::map<int2, int> s;
            s.emplace(int2(1,2),3);
            s.emplace(int2(2,3),5);
            REQUIRE(s[int2(1,2)] == 3);
            REQUIRE(s[int2(2,3)] == 5);
        }
        {
            std::unordered_set<int2> s;
            s.insert(int2(1,2));
            REQUIRE(s.count(int2(1,2)) > 0);
            REQUIRE_FALSE(s.count(int2(1,1)) > 0);
        }
        {
            std::unordered_map<int2, int> s;
            s.emplace(int2(1,2),3);
            s.emplace(int2(2,3),5);
            REQUIRE(s[int2(1,2)] == 3);
            REQUIRE(s[int2(2,3)] == 5);
        }
    }

    SUBCASE("matrix hash") {
        REQUIRE(std::hash<int2x2>{}({1,2,3,4}) == std::hash<int2x2>{}({1,2,3,4}));
        REQUIRE_FALSE(std::hash<int2x2>{}({1,2,3,4}) == std::hash<int2x2>{}({1,2,4,3}));

        {
            std::set<int2x2> s;
            s.insert(int2x2(1,2,3,4));
            REQUIRE(s.count(int2x2(1,2,3,4)) > 0);
            REQUIRE_FALSE(s.count(int2x2(1,1,1,1)) > 0);
        }
        {
            std::map<int2x2, int> s;
            s.emplace(int2x2(1,2,3,4),3);
            s.emplace(int2x2(2,3,4,5),5);
            REQUIRE(s[int2x2(1,2,3,4)] == 3);
            REQUIRE(s[int2x2(2,3,4,5)] == 5);
        }
        {
            std::unordered_set<int2x2> s;
            s.insert(int2x2(1,2,3,4));
            REQUIRE(s.count(int2x2(1,2,3,4)) > 0);
            REQUIRE_FALSE(s.count(int2x2(1,1,1,1)) > 0);
        }
        {
            std::unordered_map<int2x2, int> s;
            s.emplace(int2x2(1,2,3,4),3);
            s.emplace(int2x2(2,3,4,5),5);
            REQUIRE(s[int2x2(1,2,3,4)] == 3);
            REQUIRE(s[int2x2(2,3,4,5)] == 5);
        }
    }

    SUBCASE("quaternion hash") {
        REQUIRE(std::hash<fqua>{}({1,2,3,4}) == std::hash<fqua>{}({1,2,3,4}));
        REQUIRE_FALSE(std::hash<fqua>{}({1,2,3,4}) == std::hash<fqua>{}({3,2,1,4}));

        {
            std::set<qua<int>> s;
            s.insert(qua(1,2,3,4));
            REQUIRE(s.count(qua(1,2,3,4)) > 0);
            REQUIRE_FALSE(s.count(qua(1,1,1,1)) > 0);
        }
        {
            std::map<qua<int>, int> s;
            s.emplace(qua(1,2,3,4),3);
            s.emplace(qua(2,3,4,5),5);
            REQUIRE(s[qua(1,2,3,4)] == 3);
            REQUIRE(s[qua(2,3,4,5)] == 5);
        }
        {
            std::unordered_set<qua<int>> s;
            s.insert(qua(1,2,3,4));
            REQUIRE(s.count(qua(1,2,3,4)) > 0);
            REQUIRE_FALSE(s.count(qua(1,1,1,1)) > 0);
        }
        {
            std::unordered_map<qua<int>, int> s;
            s.emplace(qua(1,2,3,4),3);
            s.emplace(qua(2,3,4,5),5);
            REQUIRE(s[qua(1,2,3,4)] == 3);
            REQUIRE(s[qua(2,3,4,5)] == 5);
        }
    }

    SUBCASE("cast_to") {
        {
            constexpr auto i = cast_to<int>(1.5f);
            STATIC_REQUIRE(i == 1);
            STATIC_REQUIRE(std::is_same_v<decltype(i), const int>);
        }
        {
            constexpr auto v = cast_to<int>(float2{1.5f});
            STATIC_REQUIRE(v == int2(1));
            STATIC_REQUIRE(std::is_same_v<decltype(v)::component_type, int>);
        }
        {
            constexpr auto m = cast_to<int>(float2x2{1.5f});
            STATIC_REQUIRE(m == int2x2(1));
            STATIC_REQUIRE(std::is_same_v<decltype(m)::row_type, int2>);
        }
        {
            constexpr auto v = cast_to<int>(fqua{1.5f, 2.2f, 3.6f, 4.5f});
            STATIC_REQUIRE(v == qua(1,2,3,4));
            STATIC_REQUIRE(std::is_same_v<decltype(v)::component_type, int>);
        }
    }

    SUBCASE("component") {
        STATIC_REQUIRE(component(int2{1,2}, 0) == 1);
        STATIC_REQUIRE(component(int2{1,2}, 1) == 2);

        STATIC_REQUIRE(component(int2{0,0}, 0, 1) == int2{1,0});
        STATIC_REQUIRE(component(int2{0,0}, 1, 2) == int2{0,2});
    }

    SUBCASE("row") {
        STATIC_REQUIRE(row(int2x2(1,2,3,4), 0) == int2(1,2));
        STATIC_REQUIRE(row(int2x2(1,2,3,4), 1) == int2(3,4));

        STATIC_REQUIRE(row(int2x2(), 0, {1,2}) == int2x2(1,2,0,1));
        STATIC_REQUIRE(row(int2x2(), 1, {3,4}) == int2x2(1,0,3,4));
    }

    SUBCASE("column") {
        STATIC_REQUIRE(column(int2x2(1,2,3,4), 0) == int2(1,3));
        STATIC_REQUIRE(column(int2x2(1,2,3,4), 1) == int2(2,4));

        STATIC_REQUIRE(column(int2x2(), 0, {2,3}) == int2x2(2,0,3,1));
        STATIC_REQUIRE(column(int2x2(), 1, {3,4}) == int2x2(1,3,0,4));
    }

    SUBCASE("matrix translate") {
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * translate(float2{1.f,2.f}) == uapprox3(3.f,5.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * translate(translate(float2{1.f,2.f}), float2{1.f,2.f}) == uapprox3(4.f,7.f,1.f));

        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * translate(float3{1.f,2.f,3.f}) == uapprox4(3.f,5.f,7.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * translate(translate(float3{1.f,2.f,3.f}), float3{1.f,2.f,3.f}) == uapprox4(4.f,7.f,10.f,1.f));
    }

    SUBCASE("matrix rotate") {
        constexpr float pi = radians(180.f);
        constexpr float pi_2 = radians(90.f);
        constexpr float pi_4 = radians(45.f);

        REQUIRE(float4(0.f,1.f,0.f,1.f) * rotate_x(pi_2) == uapprox4(0.f,0.f,1.f,1.f));
        REQUIRE(float4(0.f,0.f,1.f,1.f) * rotate_y(pi_2) == uapprox4(1.f,0.f,0.f,1.f));
        REQUIRE(float4(1.f,0.f,0.f,1.f) * rotate_z(pi_2) == uapprox4(0.f,1.f,0.f,1.f));

        REQUIRE(float4(0.f,1.f,0.f,1.f) * rotate_x(rotate_x(pi_4),pi_4) == uapprox4(0.f,0.f,1.f,1.f));
        REQUIRE(float4(0.f,0.f,1.f,1.f) * rotate_y(rotate_y(pi_4),pi_4) == uapprox4(1.f,0.f,0.f,1.f));
        REQUIRE(float4(1.f,0.f,0.f,1.f) * rotate_z(rotate_z(pi_4),pi_4) == uapprox4(0.f,1.f,0.f,1.f));

        REQUIRE(float3(2.f,3.f,1.f) * rotate(pi) == uapprox3(-2.f,-3.f,1.f));
        REQUIRE(float4(2.f,3.f,4.f,1.f) * rotate(pi,{0.f,0.f,1.f}) == uapprox4(-2.f,-3.f,4.f,1.f));
        REQUIRE(float4(2.f,3.f,4.f,1.f) * rotate(pi,float3{0.f,0.f,1.f}) == uapprox4(-2.f,-3.f,4.f,1.f));

        REQUIRE(float3(2.f,3.f,1.f) * rotate(rotate(pi_2),pi_2) == uapprox3(-2.f,-3.f,1.f));
        REQUIRE(float4(2.f,3.f,4.f,1.f) * rotate(rotate(pi_2,{0.f,0.f,1.f}),pi_2,{0.f,0.f,1.f}) == uapprox4(-2.f,-3.f,4.f,1.f));
        REQUIRE(float4(2.f,3.f,4.f,1.f) * rotate(rotate(pi_2,float3{0.f,0.f,1.f}),pi_2,float3{0.f,0.f,1.f}) == uapprox4(-2.f,-3.f,4.f,1.f));
    }

    SUBCASE("matrix scale") {
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * scale(float2{2.f,3.f}) == uapprox3(4.f,9.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * scale(float3{2.f,3.f,4.f}) == uapprox4(4.f,9.f,16.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * scale(float3{2.f,3.f,4.f}) == uapprox4(4.f,9.f,16.f,1.f));

        STATIC_REQUIRE(float3(2.f,3.f,1.f) * scale(scale(float2{2.f,2.f}), {2.f,3.f}) == uapprox3(8.f,18.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * scale(scale(float3{2.f,2.f,2.f}), {2.f,3.f,4.f}) == uapprox4(8.f,18.f,32.f,1.f));
        STATIC_REQUIRE(float4(2.f,3.f,4.f,1.f) * scale(scale(float3{2.f,2.f,2.f}), float3{2.f,3.f,4.f}) == uapprox4(8.f,18.f,32.f,1.f));
    }

    SUBCASE("matrix shear") {
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear_x(0.f) == uapprox3(2.f,3.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear_x(1.f) == uapprox3(5.f,3.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear_x(shear_x(1.f),1.f) == uapprox3(8.f,3.f,1.f));

        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear_y(0.f) == uapprox3(2.f,3.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear_y(1.f) == uapprox3(2.f,5.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear_y(shear_y(1.f),1.f) == uapprox3(2.f,7.f,1.f));

        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear(float2(0.f,0.f)) == uapprox3(2.f,3.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear(float2(1.f,0.f)) == uapprox3(5.f,3.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear(float2(0.f,1.f)) == uapprox3(2.f,5.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear(shear(float2(1.f,0.f)),float2(1.f,0.f)) == uapprox3(8.f,3.f,1.f));
        STATIC_REQUIRE(float3(2.f,3.f,1.f) * shear(shear(float2(0.f,1.f)),float2(0.f,1.f)) == uapprox3(2.f,7.f,1.f));
    }

    SUBCASE("matrix look_at") {
        (void)look_at_lh(float3(-10.f), float3(0.f), float3(0,-1,0));
        (void)look_at_rh(float3(-10.f), float3(0.f), float3(0,-1,0));

        (void)orthographic_lh_zo(0.f, 800.f, 0.f, 640.f, 0.f, 10.f);
        (void)orthographic_lh_no(0.f, 800.f, 0.f, 640.f, 0.f, 10.f);
        (void)orthographic_rh_zo(0.f, 800.f, 0.f, 640.f, 0.f, 10.f);
        (void)orthographic_rh_no(0.f, 800.f, 0.f, 640.f, 0.f, 10.f);

        (void)perspective_lh_zo(1.f, 1.3f, 0.f, 10.f);
        (void)perspective_lh_no(1.f, 1.3f, 0.f, 10.f);
        (void)perspective_rh_zo(1.f, 1.3f, 0.f, 10.f);
        (void)perspective_rh_no(1.f, 1.3f, 0.f, 10.f);
    }

    SUBCASE("vector angle") {
        REQUIRE(angle(float2(2.f,0.f), float2(0.f,1.f)) == uapprox(radians(90.f)));
        REQUIRE(angle(float2(0.f,3.f), float2(1.f,0.f)) == uapprox(radians(90.f)));
        REQUIRE(angle(float2(0.5f,0.f), float2(-1.f,0.f)) == uapprox(radians(180.f)));
        REQUIRE(angle(float2(-0.2f,0.f), float2(1.f,0.f)) == uapprox(radians(180.f)));
        REQUIRE(angle(float3(0.f,2.f,0.f), float3(0.f,0.f,1.f)) == uapprox(radians(90.f)));
        REQUIRE(angle(float3(0.f,0.f,3.f), float3(0.f,1.f,0.f)) == uapprox(radians(90.f)));
    }

    SUBCASE("vector rotate") {
        REQUIRE(rotate(float2(2.f,0.f), radians(90.f)) == uapprox2(0.f,2.f));
        REQUIRE(rotate(float2(1.5f,0.f), radians(-90.f)) == uapprox2(0.f,-1.5f));

        REQUIRE(rotate(float3(1.5f,0.f,0.f), qrotate_z(radians(90.f))) == uapprox3(0.f,1.5f,0.f));
        REQUIRE(rotate(float3(1.5f,0.f,0.f), radians(90.f), float3(0,0,1)) == uapprox3(0.f,1.5f,0.f));

        REQUIRE(rotate(float4(1.5f,0.f,0.f,1.f), qrotate_z(radians(90.f))) == uapprox4(0.f,1.5f,0.f,1.f));
        REQUIRE(rotate(float4(1.5f,0.f,0.f,1.f), radians(90.f), float3(0,0,1)) == uapprox4(0.f,1.5f,0.f,1.f));
    }

    SUBCASE("vector project") {
        REQUIRE(project(float2(2.f, 2.f), float2(0.f, 1.f)) == uapprox2(0.f, 2.f));
        REQUIRE(project(float3(2.f, 2.f, 2.f), float3(0.f, 0.f, 1.f)) == uapprox3(0.f, 0.f, 2.f));
    }

    SUBCASE("quaternion qrotate") {
        constexpr float pi = radians(180.f);
        constexpr float pi_2 = radians(90.f);
        constexpr float pi_4 = radians(45.f);

        REQUIRE(float3(0.f,1.f,0.f) * qrotate_x(pi_2) == uapprox3(0.f,0.f,1.f));
        REQUIRE(float3(0.f,0.f,1.f) * qrotate_y(pi_2) == uapprox3(1.f,0.f,0.f));
        REQUIRE(float3(1.f,0.f,0.f) * qrotate_z(pi_2) == uapprox3(0.f,1.f,0.f));

        REQUIRE(float3(0.f,1.f,0.f) * qrotate_x(qrotate_x(pi_4),pi_4) == uapprox3(0.f,0.f,1.f));
        REQUIRE(float3(0.f,0.f,1.f) * qrotate_y(qrotate_y(pi_4),pi_4) == uapprox3(1.f,0.f,0.f));
        REQUIRE(float3(1.f,0.f,0.f) * qrotate_z(qrotate_z(pi_4),pi_4) == uapprox3(0.f,1.f,0.f));

        REQUIRE(float3(2.f,3.f,4.f) * qrotate(pi,{0.f,0.f,1.f}) == uapprox3(-2.f,-3.f,4.f));
        REQUIRE(float3(2.f,3.f,4.f) * qrotate(pi,float3{0.f,0.f,1.f}) == uapprox3(-2.f,-3.f,4.f));

        REQUIRE(float3(2.f,3.f,4.f) * qrotate(qrotate(pi_2,{0.f,0.f,1.f}),pi_2,{0.f,0.f,1.f}) == uapprox3(-2.f,-3.f,4.f));
        REQUIRE(float3(2.f,3.f,4.f) * qrotate(qrotate(pi_2,float3{0.f,0.f,1.f}),pi_2,float3{0.f,0.f,1.f}) == uapprox3(-2.f,-3.f,4.f));

        REQUIRE(qrotate_x(12.3f) == qrotate(12.3f, unit3_x<float> * 2.f));
        REQUIRE(qrotate_y(12.3f) == qrotate(12.3f, unit3_y<float> * 2.f));
        REQUIRE(qrotate_z(12.3f) == qrotate(12.3f, unit3_z<float> * 2.f));
    }
}
