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

    template < typename T, int Size >
    constexpr mat<T, Size> generate_frank_matrix() {
        mat<T, Size> m;
        for ( int i = 1; i <= Size; ++i ) {
            for ( int j = 1; j <= Size; ++j ) {
                if ( j < i - Size ) {
                    m[unsigned(i - 1)][unsigned(j - 1)] = 0;
                } else if ( j == (i - 1) ) {
                    m[unsigned(i - 1)][unsigned(j - 1)] = Size + 1 - i;
                } else {
                    m[unsigned(i - 1)][unsigned(j - 1)] = Size + 1 - j;
                }
            }
        }
        return m;
    }
}

TEST_CASE("vmath/mat_fun") {
    SUBCASE("operators") {
        STATIC_CHECK(+imat2(1,-2,3,-4) == imat2(1,-2,3,-4));
        STATIC_CHECK(-imat2(1,-2,3,-4) == imat2(-1,2,-3,4));
        STATIC_CHECK(~umat2(0xF0F0F0F0,0x0F0F0F0F,0xF0F0F0F0,0x0F0F0F0F) == umat2(0x0F0F0F0F,0xF0F0F0F0,0x0F0F0F0F,0xF0F0F0F0));
        STATIC_CHECK((!imat2(-1,0,1,2)) == bmat2(false,true,false,false));

        STATIC_CHECK(imat2(1,2,3,4) + 2 == imat2(3,4,5,6));
        STATIC_CHECK(imat2(1,2,3,4) - 2 == imat2(-1,0,1,2));
        STATIC_CHECK(imat2(1,2,3,4) * 2 == imat2(2,4,6,8));
        STATIC_CHECK(imat2(1,2,3,4) / 2 == imat2(0,1,1,2));
        STATIC_CHECK((imat2(11,12,11,12) & 6) == imat2(2,4,2,4));
        STATIC_CHECK((imat2(11,12,11,12) | 6) == imat2(15,14,15,14));
        STATIC_CHECK((imat2(11,12,11,12) ^ 6) == imat2(13,10,13,10));
        STATIC_CHECK((imat2(1,0,1,0) && 1) == bmat2(1,0,1,0));
        STATIC_CHECK((imat2(1,0,1,0) || 1) == bmat2(1,1,1,1));

        STATIC_CHECK(4 + imat2(1,2,3,4) == imat2(5,6,7,8));
        STATIC_CHECK(4 - imat2(1,2,3,4) == imat2(3,2,1,0));
        STATIC_CHECK(4 * imat2(1,2,3,4) == imat2(4,8,12,16));
        STATIC_CHECK(4 / imat2(1,2,3,4) == imat2(4,2,1,1));
        STATIC_CHECK((6 &imat2(11,12,11,12)) == imat2(2,4,2,4));
        STATIC_CHECK((6 |imat2(11,12,11,12)) == imat2(15,14,15,14));
        STATIC_CHECK((6 ^ imat2(11,12,11,12)) == imat2(13,10,13,10));
        STATIC_CHECK((1 && imat2(1,0,1,0)) == bmat2(1,0,1,0));
        STATIC_CHECK((1 || imat2(1,0,1,0)) == bmat2(1,1,1,1));

        STATIC_CHECK(imat2(1,2,3,4) + imat2(5,6,7,8) == imat2(6,8,10,12));
        STATIC_CHECK(imat2(1,2,3,4) - imat2(5,6,7,8) == imat2(-4,-4,-4,-4));

        STATIC_CHECK(imat2() * imat2() == imat2());
        STATIC_CHECK(imat3() * imat3() == imat3());

        STATIC_CHECK(ivec2(1,2) * imat2() == ivec2(1,2));
        STATIC_CHECK(ivec3(1,2,3) * imat3() == ivec3(1,2,3));
        STATIC_CHECK(ivec4(1,2,3,4) * imat4() == ivec4(1,2,3,4));

        STATIC_CHECK((imat2(6,7,6,7) & imat2(11,12,11,12)) == imat2(2,4,2,4));
        STATIC_CHECK((imat2(6,7,6,7) | imat2(11,12,11,12)) == imat2(15,15,15,15));
        STATIC_CHECK((imat2(6,7,6,7) ^ imat2(11,12,11,12)) == imat2(13,11,13,11));
        STATIC_CHECK((imat2(0,1,0,1) && imat2(1,0,1,0)) == bmat2(0,0,0,0));
        STATIC_CHECK((imat2(0,1,0,1) || imat2(1,0,1,0)) == bmat2(1,1,1,1));

        {
            imat2 v{1,2,3,4};
            CHECK(&v == &(++v));
            CHECK(v == imat2{2,3,4,5});
            CHECK(&v == &(--v));
            CHECK(v == imat2{1,2,3,4});
        }
        {
            imat2 v{1,2,3,4};
            CHECK(v++ == imat2{1,2,3,4});
            CHECK(v == imat2{2,3,4,5});
            CHECK(v-- == imat2{2,3,4,5});
            CHECK(v == imat2{1,2,3,4});
        }
        {
            imat2 v{1,2,3,4};
            CHECK(&v == &(v += 3));
            CHECK(v == imat2{4,5,6,7});
            CHECK(&v == &(v += imat2{1,2,3,4}));
            CHECK(v == imat2{5,7,9,11});
        }
        {
            imat2 v{4,5,6,7};
            CHECK(&v == &(v -= 3));
            CHECK(v == imat2{1,2,3,4});
            CHECK(&v == &(v -= imat2{2,4,6,8}));
            CHECK(v == imat2{-1,-2,-3,-4});
        }
        {
            imat2 v{1,2,3,4};
            CHECK(&v == &(v *= 3));
            CHECK(v == imat2{3,6,9,12});
        }
        {
            ivec4 v{0, 0, 0, 1};
            CHECK(&v == &(v *= translate(ivec3{1,2,3})));
            CHECK(v == uapprox4(1,2,3,1));
        }
        {
            ivec3 v{1, 2, 3};
            CHECK(&v == &(v *= imat3(scale(ivec3{2,3,4}))));
            CHECK(v == ivec3(2,6,12));
        }
        {
            imat4 v = translate(ivec3{1, 2, 3});
            CHECK(&v == &(v *= translate(ivec3{1,2,3})));
            CHECK(v == translate(ivec3{2,4,6}));
        }
        {
            imat3 v = imat3(scale(ivec3{1, 2, 3}));
            CHECK(&v == &(v *= imat3(scale(ivec3{2,3,4}))));
            CHECK(v == imat3(scale(ivec3{2,6,12})));
        }
        {
            imat2 v1{11,12,11,12};
            CHECK(&v1 == &(v1 &= 6));
            CHECK(v1 == imat2(2,4,2,4));
            imat2 v2{6,7,6,7};
            CHECK(&v2 == &(v2 &= imat2(11,12,11,12)));
            CHECK(v2 == imat2(2,4,2,4));
        }
        {
            imat2 v1{11,12,11,12};
            CHECK(&v1 == &(v1 |= 6));
            CHECK(v1 == imat2(15,14,15,14));
            imat2 v2{6,7,6,7};
            CHECK(&v2 == &(v2 |= imat2(11,12,11,12)));
            CHECK(v2 == imat2(15,15,15,15));
        }
        {
            imat2 v1{11,12,11,12};
            CHECK(&v1 == &(v1 ^= 6));
            CHECK(v1 == imat2(13,10,13,10));
            imat2 v2{6,7,6,7};
            CHECK(&v2 == &(v2 ^= imat2(11,12,11,12)));
            CHECK(v2 == imat2(13,11,13,11));
        }
    }

    SUBCASE("Operators2") {
        STATIC_CHECK(imat2{} + 0.0 == dmat2{});
        STATIC_CHECK(0.0 + imat2{} == dmat2{});
        STATIC_CHECK(imat2{} + dmat2{} == dmat2{2.0});
        STATIC_CHECK(dmat2{} + imat2{} == dmat2{2.0});

        STATIC_CHECK(imat2{} - 0.0 == dmat2{});
        STATIC_CHECK(0.0 - imat2{} == dmat2{-1.0});
        STATIC_CHECK(imat2{} - dmat2{} == dmat2{0.0});
        STATIC_CHECK(dmat2{} - imat2{} == dmat2{0.0});

        STATIC_CHECK(imat2{} * 1.0 == dmat2{});
        STATIC_CHECK(0.0 * imat2{1} == dmat2{0.0});
        STATIC_CHECK(ivec2{} * dmat2{} == dvec2{});
        STATIC_CHECK(imat2{} * dmat2{} == dmat2{});
        STATIC_CHECK(dmat2{} * imat2{1} == dmat2{});

        STATIC_CHECK(imat2{} / 1.0 == dmat2{});
        STATIC_CHECK(0.0 / imat2{1,1,1,1} == dmat2{0.0});
    }

    SUBCASE("Conversions2") {
        {
            STATIC_CHECK(dmat2(1.0) == dmat2(1));
            STATIC_CHECK(dmat2(ivec2(1,2)) == dmat2(dvec2(1,2)));
            STATIC_CHECK(dmat2(ivec2(1,2),fvec2(3,4)) == dmat2(1,2,3,4));

            STATIC_CHECK(dmat2(imat2(1)) == dmat2(1));
            STATIC_CHECK(dmat2(imat3(1)) == dmat2(1));
            STATIC_CHECK(dmat2(imat4(1)) == dmat2(1));
        }
        {
            STATIC_CHECK(dmat3(1.0) == dmat3(1));
            STATIC_CHECK(dmat3(ivec3(1,2,3)) == dmat3(dvec3(1,2,3)));
            STATIC_CHECK(dmat3(ivec3(1,2,3),fvec3(2,3,4),uvec3(3,4,5)) == dmat3(1,2,3,2,3,4,3,4,5));

            STATIC_CHECK(dmat3(imat2(1),uvec2(2)) == dmat3(dmat2(1),dvec2(2)));

            STATIC_CHECK(dmat3(imat2(1)) == dmat3(1));
            STATIC_CHECK(dmat3(imat3(1)) == dmat3(1));
            STATIC_CHECK(dmat3(imat4(1)) == dmat3(1));
        }
        {
            STATIC_CHECK(dmat4(1.0) == dmat4(1));
            STATIC_CHECK(dmat4(ivec4(1,2,3,4)) == dmat4(dvec4(1,2,3,4)));
            STATIC_CHECK(dmat4(ivec4(1,2,3,4),fvec4(2,3,4,5),uvec4(3,4,5,6),ivec4(4,5,6,7)) == dmat4(1,2,3,4,2,3,4,5,3,4,5,6,4,5,6,7));

            STATIC_CHECK(dmat4(imat3(1),uvec3(2)) == dmat4(dmat3(1),dvec3(2)));

            STATIC_CHECK(dmat4(imat2(1)) == dmat4(1));
            STATIC_CHECK(dmat4(imat3(1)) == dmat4(1));
            STATIC_CHECK(dmat4(imat4(1)) == dmat4(1));
        }
    }

    SUBCASE("relational functions") {
        STATIC_CHECK_FALSE(any(bmat2(false, false, false, false)));
        STATIC_CHECK(any(bmat2(true, false, true, false)));
        STATIC_CHECK(any(bmat2(false, true, false, true)));
        STATIC_CHECK(any(bmat2(true, true, true, true)));

        STATIC_CHECK_FALSE(any(imat2(0, 0, 0, 0)));
        STATIC_CHECK(any(imat2(1, 0, 1, 0)));
        STATIC_CHECK(any(imat2(0, 1, 0, 1)));
        STATIC_CHECK(any(imat2(1, 1, 1, 1)));

        STATIC_CHECK_FALSE(all(bmat2(false, false, false, false)));
        STATIC_CHECK_FALSE(all(bmat2(true, false, true, false)));
        STATIC_CHECK_FALSE(all(bmat2(false, true, false, true)));
        STATIC_CHECK(all(bmat2(true, true, true, true)));

        STATIC_CHECK_FALSE(all(imat2(0, 0, 0, 0)));
        STATIC_CHECK_FALSE(all(imat2(1, 0, 1, 0)));
        STATIC_CHECK_FALSE(all(imat2(0, 1, 0, 1)));
        STATIC_CHECK(all(imat2(1, 1, 1, 1)));

        STATIC_CHECK(approx(imat2(1,1,1,1), imat2(0,1,2,3)) == bmat2(false, true, false, false));
        STATIC_CHECK(approx(imat2(1,1,1,1), imat2(0,1,2,3), 0) == bmat2(false, true, false, false));
        STATIC_CHECK(approx(imat2(1,1,1,1), imat2(0,1,2,3), 1) == bmat2(true, true, true, false));
        STATIC_CHECK(approx(imat2(1,1,1,1), imat2(0,1,2,3), 2) == bmat2(true, true, true, true));

        STATIC_CHECK(less(imat2(1,1,1,1), imat2(0,1,2,3)) == bmat2(false, false, true, true));
        STATIC_CHECK(less_equal(imat2(1,1,1,1), imat2(0,1,2,3)) == bmat2(false, true, true, true));
        STATIC_CHECK(greater(imat2(1,1,1,1), imat2(0,1,2,3)) == bmat2(true, false, false, false));
        STATIC_CHECK(greater_equal(imat2(1,1,1,1), imat2(0,1,2,3)) == bmat2(true, true, false, false));

        STATIC_CHECK(equal_to(imat2(1,1,1,1), imat2(0,1,2,3)) == bmat2(false, true, false, false));
        STATIC_CHECK(not_equal_to(imat2(1,1,1,1), imat2(0,1,2,3)) == bmat2(true, false, true, true));
    }

    SUBCASE("transpose") {
        STATIC_CHECK(transpose(imat2(
            1, 2,
            3, 4
        )) == imat2(
            1, 3,
            2, 4
        ));

        STATIC_CHECK(transpose(imat3(
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        )) == imat3(
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
        ));

        STATIC_CHECK(transpose(imat4(
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        )) == imat4(
            1, 5, 9,  13,
            2, 6, 10, 14,
            3, 7, 11, 15,
            4, 8, 12, 16
        ));
    }

    SUBCASE("determinant") {
        constexpr imat2 m2{1,2,3,4};
        constexpr imat3 m3{1,2,3,4,5,6,7,8,9};
        constexpr imat4 m4{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        STATIC_CHECK(determinant(m2) == determinant(transpose(m2)));
        STATIC_CHECK(determinant(m3) == determinant(transpose(m3)));
        STATIC_CHECK(determinant(m4) == determinant(transpose(m4)));

        STATIC_CHECK(determinant(generate_frank_matrix<int, 2>()) == 1);
        STATIC_CHECK(determinant(generate_frank_matrix<int, 3>()) == 1);
        STATIC_CHECK(determinant(generate_frank_matrix<int, 4>()) == 1);

        STATIC_CHECK(determinant(transpose(generate_frank_matrix<int, 2>())) == 1);
        STATIC_CHECK(determinant(transpose(generate_frank_matrix<int, 3>())) == 1);
        STATIC_CHECK(determinant(transpose(generate_frank_matrix<int, 4>())) == 1);
    }

    SUBCASE("inverse") {
        STATIC_CHECK(inverse(fmat2()) == fmat2());
        STATIC_CHECK(inverse(fmat3()) == fmat3());
        STATIC_CHECK(inverse(fmat4()) == fmat4());

        STATIC_CHECK(inverse(fmat2(0.5)) == fmat2(2.f));
        STATIC_CHECK(inverse(fmat3(0.5)) == fmat3(2.f));
        STATIC_CHECK(inverse(fmat4(0.5)) == fmat4(2.f));

        {
            constexpr fmat4 m1 = translate(fvec3(1.f, 2.f, 3.f));
            constexpr fmat4 rm1 = inverse(m1);
            STATIC_CHECK(all(approx(
                unit4_z<float> * m1 * rm1,
                unit4_z<float>)));
        }

        {
            const fvec3 axis2 = normalize(fvec3(1.f, 2.f, 3.f));
            const fmat4 m2 = fmat4(rotate(0.5f,axis2));
            const fmat4 rm2 = inverse(m2);
            CHECK(all(approx(
                unit4_z<float> * m2 * rm2,
                unit4_z<float>)));
        }

        {
            const fvec3 axis3 = normalize(fvec3(1.f, 2.f, 3.f));
            const fmat3 m3 = fmat3(rotate(0.5f,axis3));
            const fmat3 rm3 = inverse(m3);
            CHECK(all(approx(
                unit3_z<float> * m3 * rm3,
                unit3_z<float>)));
        }

        {
            const fvec3 axis4 = normalize(fvec3(0.f, 0.f, 3.f));
            const fmat2 m4 = fmat2(rotate(0.5f,axis4));
            const fmat2 rm4 = inverse(m4);
            CHECK(all(approx(
                unit2_y<float> * m4 * rm4,
                unit2_y<float>)));
        }
    }
}
