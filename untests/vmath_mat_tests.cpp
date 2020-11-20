/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_mat.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

namespace
{
}

TEST_CASE("vmath/mat") {
    using namespace vmath_hpp;

    SECTION("sizeof") {
        STATIC_REQUIRE(sizeof(mat2i{}) == sizeof(int) * 2 * 2);
        STATIC_REQUIRE(sizeof(mat3i{}) == sizeof(int) * 3 * 3);
        STATIC_REQUIRE(sizeof(mat4i{}) == sizeof(int) * 4 * 4);
    }

    SECTION("ctors") {
        {
            STATIC_REQUIRE(mat2i()[0] == vec2i(1,0));
            STATIC_REQUIRE(mat2i()[1] == vec2i(0,1));

            STATIC_REQUIRE(mat2i(1,2,3,4)[0] == vec2i(1,2));
            STATIC_REQUIRE(mat2i(1,2,3,4)[1] == vec2i(3,4));

            STATIC_REQUIRE(mat2i({1,2},{3,4})[0] == vec2i(1,2));
            STATIC_REQUIRE(mat2i({1,2},{3,4})[1] == vec2i(3,4));
        }
        {
            constexpr mat2i v(1,2,3,4);
            constexpr mat2i v2 = v;
            STATIC_REQUIRE(v2 == mat2i(1,2,3,4));
        }
        {
            constexpr mat2i v(1,2,3,4);
            constexpr mat2i v2 = std::move(v);
            STATIC_REQUIRE(v2 == mat2i(1,2,3,4));
        }
    }

    SECTION("operator=") {
        {
            mat2i v(1,2,3,4);
            mat2i v2;
            v2 = v;
            REQUIRE(v2 == mat2i(1,2,3,4));
        }
        {
            mat2i v(1,2,3,4);
            mat2i v2;
            v2 = std::move(v);
            REQUIRE(v2 == mat2i(1,2,3,4));
        }
    }

    SECTION("swap") {
        {
            mat2i v1(1,2,3,4);
            mat2i v2(4,5,6,7);
            v1.swap(v2);
            REQUIRE(v1 == mat2i(4,5,6,7));
            REQUIRE(v2 == mat2i(1,2,3,4));
        }
        {
            mat2i v1(1,2,3,4);
            mat2i v2(4,5,6,7);
            swap(v1, v2);
            REQUIRE(v1 == mat2i(4,5,6,7));
            REQUIRE(v2 == mat2i(1,2,3,4));
        }
    }

    SECTION("iter") {
        {
            mat2i v{1,2,3,4};
            mat2i::iterator i = v.begin();
            REQUIRE(*i++ == vec2i{1,2});
            REQUIRE(*i++ == vec2i{3,4});
            REQUIRE(v.end() == i);
        }
        {
            const mat2i v{1,2,3,4};
            mat2i::const_iterator i = v.begin();
            REQUIRE(*i++ == vec2i{1,2});
            REQUIRE(*i++ == vec2i{3,4});
            REQUIRE(v.end() == i);
        }
        {
            mat2i v{1,2,3,4};
            for ( auto i = v.begin(); i < v.end(); ++i ) {
                *i = vec2i(i->x() * 2, i->y() * 2);
            }
            REQUIRE(v == mat2i(2,4,6,8));
        }
    }

    SECTION("riter") {
        {
            mat2i v{1,2,3,4};
            mat2i::reverse_iterator i = v.rbegin();
            REQUIRE(*i++ == vec2i{3,4});
            REQUIRE(*i++ == vec2i{1,2});
            REQUIRE(v.rend() == i);
            for ( auto j = v.rbegin(); j < v.rend(); ++j ) {
                *j = vec2i(j->x() * 2, j->y() * 2);
            }
            REQUIRE(v == mat2i(2,4,6,8));
        }
        {
            const mat2i v{1,2,3,4};
            mat2i::const_reverse_iterator i = v.rbegin();
            REQUIRE(*i++ == vec2i{3,4});
            REQUIRE(*i++ == vec2i{1,2});
            REQUIRE(v.rend() == i);
        }
        {
            mat2i v{1,2,3,4};
            for ( auto i = v.rbegin(); i < v.rend(); ++i ) {
                *i = vec2i(i->x() * 2, i->y() * 2);
            }
            REQUIRE(v == mat2i(2,4,6,8));
        }
    }

    SECTION("size/max_size/empty") {
        STATIC_REQUIRE(mat<int, 2>().size() == 2);
        STATIC_REQUIRE(mat<int, 2>().max_size() == 2);
        STATIC_REQUIRE_FALSE(mat<int, 2>().empty());

        STATIC_REQUIRE(mat<int, 3>().size() == 3);
        STATIC_REQUIRE(mat<int, 3>().max_size() == 3);
        STATIC_REQUIRE_FALSE(mat<int, 3>().empty());
    }

    SECTION("operator[]") {
        {
            STATIC_REQUIRE(mat2i()[0] == vec2i(1,0));
            STATIC_REQUIRE(mat2i()[1] == vec2i(0,1));

            STATIC_REQUIRE(mat3i()[0] == vec3i(1,0,0));
            STATIC_REQUIRE(mat3i()[1] == vec3i(0,1,0));
            STATIC_REQUIRE(mat3i()[2] == vec3i(0,0,1));

            STATIC_REQUIRE(mat4i()[0] == vec4i(1,0,0,0));
            STATIC_REQUIRE(mat4i()[1] == vec4i(0,1,0,0));
            STATIC_REQUIRE(mat4i()[2] == vec4i(0,0,1,0));
            STATIC_REQUIRE(mat4i()[3] == vec4i(0,0,0,1));
        }
        {
            mat2i v;
            v[0] = vec2i(1,2);
            v[1] = vec2i(3,4);
            REQUIRE(v == mat2i(1,2,3,4));
        }
        {
            mat3i v;
            v[0] = vec3i(1,2,3);
            v[1] = vec3i(4,5,6);
            v[2] = vec3i(7,8,9);
            REQUIRE(v == mat3i(1,2,3,4,5,6,7,8,9));
        }
        {
            mat4i v;
            v[0] = vec4i(1,2,3,4);
            v[1] = vec4i(5,6,7,8);
            v[2] = vec4i(9,10,11,12);
            v[3] = vec4i(13,14,15,16);
            REQUIRE(v == mat4i(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16));
        }
    }

    SECTION("at") {
        STATIC_REQUIRE(mat2i(1,2,3,4).at(0) == vec2i(1,2));
        STATIC_REQUIRE(mat2i(1,2,3,4).at(1) == vec2i(3,4));
        REQUIRE_THROWS_AS(mat2i(1,2,3,4).at(2), std::out_of_range);
    }

    SECTION("operator==/operator!=") {
        STATIC_REQUIRE(mat2i(1,2,3,4) == mat2i(1,2,3,4));
        STATIC_REQUIRE_FALSE(mat2i(1,2,3,4) == mat2i(2,2,3,4));
        STATIC_REQUIRE_FALSE(mat2i(1,2,3,4) == mat2i(1,3,3,4));

        STATIC_REQUIRE_FALSE(mat2i(1,2,3,4) != mat2i(1,2,3,4));
        STATIC_REQUIRE(mat2i(1,2,3,4) != mat2i(2,2,3,4));
        STATIC_REQUIRE(mat2i(1,2,3,4) != mat2i(1,3,3,4));
    }

    SECTION("operator<") {
        STATIC_REQUIRE_FALSE(mat2i(1,2,3,4) < mat2i(1,2,3,4));

        STATIC_REQUIRE(mat2i(1,1,3,4) < mat2i(1,2,3,4));
        STATIC_REQUIRE_FALSE(mat2i(1,2,3,4) < mat2i(1,1,3,4));

        STATIC_REQUIRE(mat2i(0,3,3,4) < mat2i(1,2,3,4));
        STATIC_REQUIRE_FALSE(mat2i(1,2,3,4) < mat2i(0,3,3,4));
    }
}
