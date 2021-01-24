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
    SUBCASE("Detail") {
        STATIC_REQUIRE(map_join([](const int& x){
            return x * 2;
        }, qua(1,2,3,4)) == qua(2,4,6,8));

        STATIC_REQUIRE(map_join([](const int& x, const int& y){
            return x + y;
        }, qua(1,2,3,4), qua(2,3,4,5)) == qua(3,5,7,9));

        STATIC_REQUIRE(map_join([](const int& x, const int& y, const int& z){
            return x + y + z;
        }, qua(1,2,3,4), qua(2,3,4,5), qua(3,4,5,6)) == qua(6,9,12,15));

        STATIC_REQUIRE(fold_join([](int acc, const int& x){
            return acc + x;
        }, 0, qua(1,2,3,4)) == 10);

        STATIC_REQUIRE(fold_join([](int acc, const int& x, const int& y){
            return acc + x + y;
        }, 0, qua(1,2,3,4), qua(2,3,4,5)) == 24);

        STATIC_REQUIRE(fold1_join([](const int& acc, const int& x){
            return acc + x;
        }, qua{1,2,3,4}) == 10);
    }
}
