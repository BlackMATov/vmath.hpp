/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include <vmath.hpp/vmath_vec_ext.hpp>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "vmath_tests.hpp"

namespace
{
    using namespace vmath_hpp;
    using namespace vmath_tests;
}

TEST_CASE("vmath/vec_ext") {
    SECTION("cast_to") {
        constexpr auto v = cast_to<int>(vec2f{1.5f});
        STATIC_REQUIRE(v == vec2i(1));
        STATIC_REQUIRE(std::is_same_v<decltype(v)::value_type, int>);
    }
}
