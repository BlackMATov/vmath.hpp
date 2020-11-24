/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_mat_ext.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
    using namespace vmath_hpp;

    template < typename T >
    class approx2 {
    public:
        constexpr explicit approx2(T v) : value_(v) {}
        constexpr explicit approx2(T x, T y) : value_(x, y) {}

        friend constexpr bool operator==(const vec<T, 2>& l, const approx2& r) {
            return (r.value_.x < l.x + epsilon)
                && (l.x < r.value_.x + epsilon)
                && (r.value_.y < l.y + epsilon)
                && (l.y < r.value_.y + epsilon);
        }
    private:
        vec<T, 2> value_;
        static constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
    };

    template < typename T >
    class approx3 {
    public:
        constexpr explicit approx3(T v) : value_(v) {}
        constexpr explicit approx3(T x, T y, T z) : value_(x, y, z) {}

        friend constexpr bool operator==(const vec<T, 3>& l, const approx3& r) {
            return (r.value_.x < l.x + epsilon)
                && (l.x < r.value_.x + epsilon)
                && (r.value_.y < l.y + epsilon)
                && (l.y < r.value_.y + epsilon)
                && (r.value_.z < l.z + epsilon)
                && (l.z < r.value_.z + epsilon);
        }
    private:
        vec<T, 3> value_;
        static constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
    };

    template < typename T >
    class approx4 {
    public:
        constexpr explicit approx4(T v) : value_(v) {}
        constexpr explicit approx4(T x, T y, T z, T w) : value_(x, y, z, w) {}

        friend constexpr bool operator==(const vec<T, 4>& l, const approx4& r) {
            return (r.value_.x < l.x + epsilon)
                && (l.x < r.value_.x + epsilon)
                && (r.value_.y < l.y + epsilon)
                && (l.y < r.value_.y + epsilon)
                && (r.value_.z < l.z + epsilon)
                && (l.z < r.value_.z + epsilon)
                && (r.value_.w < l.w + epsilon)
                && (l.w < r.value_.w + epsilon);
        }
    private:
        vec<T, 4> value_;
        static constexpr T epsilon = std::numeric_limits<T>::epsilon() * 100;
    };
}

TEST_CASE("vmath/mat_ext") {
    SECTION("identity") {
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * identity<float>() == approx4(2.f,3.f,4.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * identity<float>() == approx4(2.f,3.f,4.f,1.f));
    }

    SECTION("translate") {
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * translate(1.f,2.f,3.f) == approx4(3.f,5.f,7.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * translate(vec3f{1.f,2.f,3.f}) == approx4(3.f,5.f,7.f,1.f));

        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * translate(translate(1.f,2.f,3.f), 1.f,2.f,3.f) == approx4(4.f,7.f,10.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * translate(translate(1.f,2.f,3.f), vec3f{1.f,2.f,3.f}) == approx4(4.f,7.f,10.f,1.f));
    }

    SECTION("rotate") {
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * rotate(float(M_PI),0.f,0.f,1.f) == approx4(-2.f,-3.f,4.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * rotate(float(M_PI),vec3f{0.f,0.f,1.f}) == approx4(-2.f,-3.f,4.f,1.f));

        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * rotate(rotate(float(M_PI_2),0.f,0.f,1.f),float(M_PI_2),0.f,0.f,1.f) == approx4(-2.f,-3.f,4.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * rotate(rotate(float(M_PI_2),0.f,0.f,1.f),float(M_PI_2),vec3f{0.f,0.f,1.f}) == approx4(-2.f,-3.f,4.f,1.f));
    }

    SECTION("scale") {
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * scale(2.f,3.f,4.f) == approx4(4.f,9.f,16.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * scale(vec3f{2.f,3.f,4.f}) == approx4(4.f,9.f,16.f,1.f));

        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * scale(scale(2.f,2.f,2.f), 2.f,3.f,4.f) == approx4(8.f,18.f,32.f,1.f));
        REQUIRE(vec4f(2.f,3.f,4.f,1.f) * scale(scale(2.f,2.f,2.f), vec3f{2.f,3.f,4.f}) == approx4(8.f,18.f,32.f,1.f));
    }
}
