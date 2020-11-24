/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_mat_fun.hpp>
#include <vmath.hpp/vmath_mat_ext.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
    using namespace vmath_hpp;

    template < typename T, int Size >
    constexpr mat<T, Size> generate_frank_matrix() {
        mat<T, Size> m;
        for ( int i = 1; i <= Size; ++i ) {
            for ( int j = 1; j <= Size; ++j ) {
                if ( j < i - Size ) {
                    m[i - 1][j - 1] = 0;
                } else if ( j == (i - 1) ) {
                    m[i - 1][j - 1] = Size + 1 - i;
                } else {
                    m[i - 1][j - 1] = Size + 1 - j;
                }
            }
        }
        return m;
    }

    template < typename T >
    class approx2 {
    public:
        constexpr explicit approx2(T v) : value_(v) {}
        constexpr explicit approx2(const vec<T, 2>& v) : value_(v) {}
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
        constexpr explicit approx3(const vec<T, 3>& v) : value_(v) {}
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
        constexpr explicit approx4(const vec<T, 4>& v) : value_(v) {}
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

    template < typename T >
    class approx2x2 {
    public:
        constexpr explicit approx2x2(const mat<T, 2>& v) : value_(v) {}

        friend constexpr bool operator==(const mat<T, 2>& l, const approx2x2& r) {
            return l[0] == approx2(r.value_[0])
                && l[1] == approx2(r.value_[1]);
        }
    private:
        mat<T, 2> value_;
    };

    template < typename T >
    class approx3x3 {
    public:
        constexpr explicit approx3x3(const mat<T, 3>& v) : value_(v) {}

        friend constexpr bool operator==(const mat<T, 3>& l, const approx3x3& r) {
            return l[0] == approx3(r.value_[0])
                && l[1] == approx3(r.value_[1])
                && l[2] == approx3(r.value_[2]);
        }
    private:
        mat<T, 3> value_;
    };

    template < typename T >
    class approx4x4 {
    public:
        constexpr explicit approx4x4(const mat<T, 4>& v) : value_(v) {}

        friend constexpr bool operator==(const mat<T, 4>& l, const approx4x4& r) {
            return l[0] == approx4(r.value_[0])
                && l[1] == approx4(r.value_[1])
                && l[2] == approx4(r.value_[2])
                && l[3] == approx4(r.value_[3]);
        }
    private:
        mat<T, 4> value_;
    };
}

TEST_CASE("vmath/mat_fun") {
    SECTION("Operators") {
        STATIC_REQUIRE(-mat2i(1,2,3,4) == mat2i(-1,-2,-3,-4));

        STATIC_REQUIRE(mat2i(1,2,3,4) + 2 == mat2i(3,4,5,6));
        STATIC_REQUIRE(mat2i(1,2,3,4) - 2 == mat2i(-1,0,1,2));
        STATIC_REQUIRE(mat2i(1,2,3,4) * 2 == mat2i(2,4,6,8));
        STATIC_REQUIRE(mat2i(1,2,3,4) / 2 == mat2i(0,1,1,2));

        STATIC_REQUIRE(4 + mat2i(1,2,3,4) == mat2i(5,6,7,8));
        STATIC_REQUIRE(4 - mat2i(1,2,3,4) == mat2i(3,2,1,0));
        STATIC_REQUIRE(4 * mat2i(1,2,3,4) == mat2i(4,8,12,16));
        STATIC_REQUIRE(4 / mat2i(1,2,3,4) == mat2i(4,2,1,1));

        STATIC_REQUIRE(mat2i(1,2,3,4) + mat2i(5,6,7,8) == mat2i(6,8,10,12));
        STATIC_REQUIRE(mat2i(1,2,3,4) - mat2i(5,6,7,8) == mat2i(-4,-4,-4,-4));
        STATIC_REQUIRE(mat2i(5,6,7,8) / mat2i(1,2,3,4) == mat2i(5,3,2,2));

        STATIC_REQUIRE(mat2i() * mat2i() == mat2i());
        STATIC_REQUIRE(mat3i() * mat3i() == mat3i());

        STATIC_REQUIRE(vec2i(1,2) * mat2i() == vec2i(1,2));
        STATIC_REQUIRE(vec3i(1,2,3) * mat3i() == vec3i(1,2,3));
        STATIC_REQUIRE(vec4i(1,2,3,4) * mat4i() == vec4i(1,2,3,4));
    }

    SECTION("Matrix Functions") {
        {
            STATIC_REQUIRE(transpose(mat2i(
                1, 2,
                3, 4
            )) == mat2i(
                1, 3,
                2, 4
            ));

            STATIC_REQUIRE(transpose(mat3i(
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            )) == mat3i(
                1, 4, 7,
                2, 5, 8,
                3, 6, 9
            ));

            STATIC_REQUIRE(transpose(mat4i(
                1,  2,  3,  4,
                5,  6,  7,  8,
                9,  10, 11, 12,
                13, 14, 15, 16
            )) == mat4i(
                1, 5, 9,  13,
                2, 6, 10, 14,
                3, 7, 11, 15,
                4, 8, 12, 16
            ));
        }
        {
            constexpr mat2i m2{1,2,3,4};
            constexpr mat3i m3{1,2,3,4,5,6,7,8,9};
            constexpr mat4i m4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
            STATIC_REQUIRE(determinant(m2) == determinant(transpose(m2)));
            STATIC_REQUIRE(determinant(m3) == determinant(transpose(m3)));
            STATIC_REQUIRE(determinant(m4) == determinant(transpose(m4)));

            STATIC_REQUIRE(determinant(generate_frank_matrix<int, 2>()) == 1);
            STATIC_REQUIRE(determinant(generate_frank_matrix<int, 3>()) == 1);
            STATIC_REQUIRE(determinant(generate_frank_matrix<int, 4>()) == 1);

            STATIC_REQUIRE(determinant(transpose(generate_frank_matrix<int, 2>())) == 1);
            STATIC_REQUIRE(determinant(transpose(generate_frank_matrix<int, 3>())) == 1);
            STATIC_REQUIRE(determinant(transpose(generate_frank_matrix<int, 4>())) == 1);
        }
        {
            STATIC_REQUIRE(inverse(mat2i()) == mat2i());
            STATIC_REQUIRE(inverse(mat3i()) == mat3i());
            STATIC_REQUIRE(inverse(mat4i()) == mat4i());

            STATIC_REQUIRE(inverse(mat2f(0.5)) == mat2f(2.f));
            STATIC_REQUIRE(inverse(mat3f(0.5)) == mat3f(2.f));
            STATIC_REQUIRE(inverse(mat4f(0.5)) == mat4f(2.f));

            STATIC_REQUIRE(inverse(translate(1.f,2.f,3.f)) == approx4x4(translate(-1.f,-2.f,-3.f)));

            REQUIRE(inverse(rotate(0.5f,normalize(vec3f{1.f,2.f,3.f}))) == approx4x4(rotate(-0.5f,normalize(vec3f{1.f,2.f,3.f}))));
            REQUIRE(inverse(mat3f(rotate(0.5f,normalize(vec3f{1.f,2.f,3.f})))) == approx3x3(mat3f(rotate(-0.5f,normalize(vec3f{1.f,2.f,3.f})))));
            REQUIRE(inverse(mat2f(rotate(0.5f,vec3f{0,0,1}))) == approx2x2(mat2f(rotate(-0.5f,vec3f{0,0,1}))));
        }
    }
}
