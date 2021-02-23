/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#include "vmath_tests.hpp"

namespace
{
    template < typename T >
    class fix {
    public:
        fix() = default;

        fix(fix&&) = default;
        fix& operator=(fix&&) = default;

        fix(const fix&) = default;
        fix& operator=(const fix&) = default;

        constexpr explicit fix(T underlying): underlying_(underlying) {}
        constexpr T underlying() const noexcept { return underlying_; }

        constexpr friend fix abs(const fix& l) { using vmath_hpp::abs; return { fix{abs(l.underlying())} }; }
        constexpr friend fix sqr(const fix& l) { using vmath_hpp::sqr; return { fix{sqr(l.underlying())} }; }
        constexpr friend fix sign(const fix& l) { using vmath_hpp::sign; return { fix{sign(l.underlying())} }; }

        constexpr friend fix rcp(const fix& l) { using vmath_hpp::rcp; return { fix{rcp(l.underlying())} }; }
        constexpr friend fix floor(const fix& l) { using vmath_hpp::floor; return { fix{floor(l.underlying())} }; }
        constexpr friend fix trunc(const fix& l) { using vmath_hpp::trunc; return { fix{trunc(l.underlying())} }; }
        constexpr friend fix round(const fix& l) { using vmath_hpp::round; return { fix{round(l.underlying())} }; }
        constexpr friend fix ceil(const fix& l) { using vmath_hpp::ceil; return { fix{ceil(l.underlying())} }; }
        constexpr friend fix fract(const fix& l) { using vmath_hpp::fract; return { fix{fract(l.underlying())} }; }

        constexpr friend fix fmod(const fix& l, const fix& r) { using vmath_hpp::fmod; return { fix{fmod(l.underlying(), r.underlying())} }; }
        constexpr friend fix modf(const fix& l, fix* r) { using vmath_hpp::modf; return { fix{modf(l.underlying(), &r->underlying_)} }; }
        constexpr friend fix copysign(const fix& l, const fix& r) { using vmath_hpp::copysign; return { fix{copysign(l.underlying(), r.underlying())} }; }

        constexpr friend fix min(const fix& l, const fix& r) { using vmath_hpp::min; return fix{min(l.underlying(), r.underlying())}; }
        constexpr friend fix max(const fix& l, const fix& r) { using vmath_hpp::max; return fix{max(l.underlying(), r.underlying())}; }
        constexpr friend fix clamp(const fix& l, const fix& min_l, const fix& max_l) { using vmath_hpp::clamp; return fix{clamp(l.underlying(), min_l.underlying(), max_l.underlying())}; }
        constexpr friend fix saturate(const fix& l) { using vmath_hpp::saturate; return fix{saturate(l.underlying())}; }
        constexpr friend fix lerp(const fix& l, const fix& r, const fix& a) { using vmath_hpp::lerp; return fix{lerp(l.underlying(), r.underlying(), a.underlying())}; }
        constexpr friend fix lerp(const fix& l, const fix& r, const fix& a, const fix& b) { using vmath_hpp::lerp; return fix{lerp(l.underlying(), r.underlying(), a.underlying(), b.underlying())}; }

        constexpr friend fix step(const fix& e, const fix& l) { using vmath_hpp::step; return fix{step(e.underlying(), l.underlying())}; }
        constexpr friend fix smoothstep(const fix& e0, const fix& e1, const fix& l) { using vmath_hpp::smoothstep; return fix{smoothstep(e0.underlying(), e1.underlying(), l.underlying())}; }

        constexpr friend fix fma(const fix& x, const fix& y, const fix& z) { using vmath_hpp::fma; return fix{fma(x.underlying(), y.underlying(), z.underlying())}; }

        //

        constexpr friend fix<bool> any(const fix& l) { using vmath_hpp::any; return fix<bool>{any(l.underlying())}; }
        constexpr friend fix<bool> all(const fix& l) { using vmath_hpp::all; return fix<bool>{all(l.underlying())}; }

        constexpr friend fix<bool> approx(const fix& l, const fix& r) { using vmath_hpp::approx; return fix<bool>{approx(l.underlying(), r.underlying())}; }
        constexpr friend fix<bool> approx(const fix& l, const fix& r, const fix& e) { using vmath_hpp::approx; return fix<bool>{approx(l.underlying(), r.underlying(), e.underlying())}; }

        constexpr friend fix<bool> less(const fix& l, const fix& r) { using vmath_hpp::less; return fix<bool>{less(l.underlying(), r.underlying())}; }
        constexpr friend fix<bool> less_equal(const fix& l, const fix& r) { using vmath_hpp::less_equal; return fix<bool>{less_equal(l.underlying(), r.underlying())}; }
        constexpr friend fix<bool> greater(const fix& l, const fix& r) { using vmath_hpp::greater; return fix<bool>{greater(l.underlying(), r.underlying())}; }
        constexpr friend fix<bool> greater_equal(const fix& l, const fix& r) { using vmath_hpp::greater_equal; return fix<bool>{greater_equal(l.underlying(), r.underlying())}; }
        constexpr friend fix<bool> equal_to(const fix& l, const fix& r) { using vmath_hpp::equal_to; return fix<bool>{equal_to(l.underlying(), r.underlying())}; }
        constexpr friend fix<bool> not_equal_to(const fix& l, const fix& r) { using vmath_hpp::not_equal_to; return fix<bool>{not_equal_to(l.underlying(), r.underlying())}; }

        //

        constexpr friend fix radians(const fix& l) { using vmath_hpp::radians; return fix{radians(l.underlying())}; }
        constexpr friend fix degrees(const fix& l) { using vmath_hpp::degrees; return fix{degrees(l.underlying())}; }
        constexpr friend fix sin(const fix& l) { using vmath_hpp::sin; return fix{sin(l.underlying())}; }
        constexpr friend fix cos(const fix& l) { using vmath_hpp::cos; return fix{cos(l.underlying())}; }
        constexpr friend fix tan(const fix& l) { using vmath_hpp::tan; return fix{tan(l.underlying())}; }
        constexpr friend fix asin(const fix& l) { using vmath_hpp::asin; return fix{asin(l.underlying())}; }
        constexpr friend fix acos(const fix& l) { using vmath_hpp::acos; return fix{acos(l.underlying())}; }
        constexpr friend fix atan(const fix& l) { using vmath_hpp::atan; return fix{atan(l.underlying())}; }
        constexpr friend fix atan2(const fix& l, const fix& r) { using vmath_hpp::atan2; return fix{atan2(l.underlying(), r.underlying())}; }
        constexpr friend fix sinh(const fix& l) { using vmath_hpp::sinh; return fix{sinh(l.underlying())}; }
        constexpr friend fix cosh(const fix& l) { using vmath_hpp::cosh; return fix{cosh(l.underlying())}; }
        constexpr friend fix tanh(const fix& l) { using vmath_hpp::tanh; return fix{tanh(l.underlying())}; }
        constexpr friend fix asinh(const fix& l) { using vmath_hpp::asinh; return fix{asinh(l.underlying())}; }
        constexpr friend fix acosh(const fix& l) { using vmath_hpp::acosh; return fix{acosh(l.underlying())}; }
        constexpr friend fix atanh(const fix& l) { using vmath_hpp::atanh; return fix{atanh(l.underlying())}; }
        constexpr friend std::pair<fix,fix> sincos(const fix& l) { return { sin(l), cos(l) }; }
        constexpr friend void sincos(const fix& l, fix* s, fix* c) { *s = sin(l); *c = cos(l); }

        //

        constexpr friend fix pow(const fix& l, const fix& r) { using vmath_hpp::pow; return fix{pow(l.underlying(), r.underlying())}; }
        constexpr friend fix exp(const fix& l) { using vmath_hpp::exp; return fix{exp(l.underlying())}; }
        constexpr friend fix log(const fix& l) { using vmath_hpp::log; return fix{log(l.underlying())}; }
        constexpr friend fix exp2(const fix& l) { using vmath_hpp::exp2; return fix{exp2(l.underlying())}; }
        constexpr friend fix log2(const fix& l) { using vmath_hpp::log2; return fix{log2(l.underlying())}; }
        constexpr friend fix sqrt(const fix& l) { using vmath_hpp::sqrt; return fix{sqrt(l.underlying())}; }
        constexpr friend fix rsqrt(const fix& l) { using vmath_hpp::rsqrt; return fix{rsqrt(l.underlying())}; }

        //

        constexpr friend fix operator+(const fix& l) { return { fix{+l.underlying()} }; }
        constexpr friend fix operator-(const fix& l) { return { fix{-l.underlying()} }; }
        constexpr friend fix operator~(const fix& l) { return { fix{~l.underlying()} }; }
        constexpr friend fix<bool> operator!(const fix& l) { return { fix<bool>{!l.underlying()} }; }

        constexpr friend fix operator+(const fix& l, const fix& r) { return fix{l.underlying() + r.underlying()}; }
        constexpr friend fix operator-(const fix& l, const fix& r) { return fix{l.underlying() - r.underlying()}; }
        constexpr friend fix operator*(const fix& l, const fix& r) { return fix{l.underlying() * r.underlying()}; }
        constexpr friend fix operator/(const fix& l, const fix& r) { return fix{l.underlying() / r.underlying()}; }

        constexpr friend fix operator&(const fix& l, const fix& r) { return fix{l.underlying() & r.underlying()}; }
        constexpr friend fix operator|(const fix& l, const fix& r) { return fix{l.underlying() | r.underlying()}; }
        constexpr friend fix operator^(const fix& l, const fix& r) { return fix{l.underlying() ^ r.underlying()}; }

        constexpr friend fix<bool> operator&&(const fix& l, const fix& r) { return fix<bool>{l.underlying() && r.underlying()}; }
        constexpr friend fix<bool> operator||(const fix& l, const fix& r) { return fix<bool>{l.underlying() || r.underlying()}; }

        constexpr friend bool operator<(const fix& l, const fix& r) { return l.underlying() < r.underlying(); }
        constexpr friend bool operator==(const fix& l, const fix& r) { return l.underlying() == r.underlying(); }
        constexpr friend bool operator!=(const fix& l, const fix& r) { return l.underlying() != r.underlying(); }
    private:
        T underlying_{};
    };

    using namespace vmath_hpp;
    using namespace vmath_tests;

    using qfix = qua<fix<float>>;

    using fix2b = vec<fix<bool>, 2>;
    using fix3b = vec<fix<bool>, 3>;
    using fix4b = vec<fix<bool>, 4>;

    using fix2i = vec<fix<int>, 2>;
    using fix3i = vec<fix<int>, 3>;
    using fix4i = vec<fix<int>, 4>;

    using fix2f = vec<fix<float>, 2>;
    using fix3f = vec<fix<float>, 3>;
    using fix4f = vec<fix<float>, 4>;

    using fix2x2b = mat<fix<bool>, 2>;
    using fix3x3b = mat<fix<bool>, 3>;
    using fix4x4b = mat<fix<bool>, 4>;

    using fix2x2i = mat<fix<int>, 2>;
    using fix3x3i = mat<fix<int>, 3>;
    using fix4x4i = mat<fix<int>, 4>;

    using fix2x2f = mat<fix<float>, 2>;
    using fix3x3f = mat<fix<float>, 3>;
    using fix4x4f = mat<fix<float>, 4>;
}

//
// Common Functions
//

namespace vmath_hpp
{
    template fix2f abs(const fix2f&);
    template fix2f sqr(const fix2f&);
    template fix2f sign(const fix2f&);

    template fix2f rcp(const fix2f&);
    template fix2f floor(const fix2f&);
    template fix2f trunc(const fix2f&);
    template fix2f round(const fix2f&);
    template fix2f ceil(const fix2f&);
    template fix2f fract(const fix2f&);

    template fix2f fmod(const fix2f&, fix<float>);
    template fix2f fmod(const fix2f&, const fix2f&);

    template fix2f modf(const fix2f&, fix2f*);

    template fix2f copysign(const fix2f&, fix<float>);
    template fix2f copysign(const fix2f&, const fix2f&);

    template fix<float> min(const fix2f&);
    template fix2f min(const fix2f&, fix<float>);
    template fix2f min(fix<float>, const fix2f&);
    template fix2f min(const fix2f&, const fix2f&);

    template fix<float> max(const fix2f&);
    template fix2f max(const fix2f&, fix<float>);
    template fix2f max(fix<float>, const fix2f&);
    template fix2f max(const fix2f&, const fix2f&);

    template fix2f clamp(const fix2f&, fix<float>, fix<float>);
    template fix2f clamp(const fix2f&, const fix2f&, const fix2f&);

    template fix2f saturate(const fix2f&);

    template fix2f lerp(const fix2f&, const fix2f&, fix<float>);
    template fix2f lerp(const fix2f&, const fix2f&, fix<float>, fix<float>);
    template fix2f lerp(const fix2f&, const fix2f&, const fix2f&);
    template fix2f lerp(const fix2f&, const fix2f&, const fix2f&, const fix2f&);

    template fix2f step(fix<float>, const fix2f&);
    template fix2f step(const fix2f&, const fix2f&);
    template fix2f smoothstep(fix<float>, fix<float>, const fix2f&);
    template fix2f smoothstep(const fix2f&, const fix2f&, const fix2f&);

    template fix2f fma(const fix2f&, const fix2f&, const fix2f&);
}

namespace vmath_hpp
{
    template qfix lerp(const qfix&, const qfix&, fix<float>);
    template qfix lerp(const qfix&, const qfix&, fix<float>, fix<float>);
    template qfix nlerp(const qfix&, const qfix&, fix<float>);
    template qfix slerp(const qfix&, const qfix&, fix<float>);
}

//
// Angle and Trigonometric Functions
//

namespace vmath_hpp
{
    template fix2f radians(const fix2f&);
    template fix2f degrees(const fix2f&);
    template fix2f sin(const fix2f&);
    template fix2f cos(const fix2f&);
    template fix2f tan(const fix2f&);
    template fix2f asin(const fix2f&);
    template fix2f acos(const fix2f&);
    template fix2f atan(const fix2f&);
    template fix2f atan2(const fix2f&, const fix2f&);
    template fix2f sinh(const fix2f&);
    template fix2f cosh(const fix2f&);
    template fix2f tanh(const fix2f&);
    template fix2f asinh(const fix2f&);
    template fix2f acosh(const fix2f&);
    template fix2f atanh(const fix2f&);
    template std::pair<fix2f, fix2f> sincos(const fix2f&);
    template void sincos(const fix2f&, fix2f*, fix2f*);
}

//
// Exponential Functions
//

namespace vmath_hpp
{
    template fix2f pow(const fix2f&, const fix2f&);
    template fix2f exp(const fix2f&);
    template fix2f log(const fix2f&);
    template fix2f exp2(const fix2f&);
    template fix2f log2(const fix2f&);
    template fix2f sqrt(const fix2f&);
    template fix2f rsqrt(const fix2f&);
}

//
// Geometric Functions
//

namespace vmath_hpp
{
    template fix<float> dot(const fix2f&, const fix2f&);
    template fix<float> length(const fix2f&);
    template fix<float> rlength(const fix2f&);
    template fix<float> length2(const fix2f&);
    template fix<float> rlength2(const fix2f&);
    template fix<float> distance(const fix2f&, const fix2f&);
    template fix<float> distance2(const fix2f&, const fix2f&);
    template fix<float> cross(const fix2f&, const fix2f&);
    template fix3f cross(const fix3f&, const fix3f&);
    template fix2f normalize(const fix2f&);
}

namespace vmath_hpp
{
    template fix<float> dot(const qfix&, const qfix&);
    template fix<float> length(const qfix&);
    template fix<float> rlength(const qfix&);
    template fix<float> length2(const qfix&);
    template fix<float> rlength2(const qfix&);
    template fix<float> distance(const qfix&, const qfix&);
    template qfix normalize(const qfix&);
}

//
// Relational Functions
//

namespace vmath_hpp
{
    template fix<bool> any(const fix2f&);
    template fix<bool> all(const fix2f&);
    template fix2b approx(const fix2f&, const fix2f&);
    template fix2b approx(const fix2f&, const fix2f&, fix<float>);
    template fix2b less(const fix2f&, const fix2f&);
    template fix2b less_equal(const fix2f&, const fix2f&);
    template fix2b greater(const fix2f&, const fix2f&);
    template fix2b greater_equal(const fix2f&, const fix2f&);
    template fix2b equal_to(const fix2f&, const fix2f&);
    template fix2b not_equal_to(const fix2f&, const fix2f&);
}

namespace vmath_hpp
{
    template fix<bool> any(const fix2x2f&);
    template fix<bool> all(const fix2x2f&);
    template fix2x2b approx(const fix2x2f&, const fix2x2f&);
    template fix2x2b approx(const fix2x2f&, const fix2x2f&, fix<float>);
    template fix2x2b less(const fix2x2f&, const fix2x2f&);
    template fix2x2b less_equal(const fix2x2f&, const fix2x2f&);
    template fix2x2b greater(const fix2x2f&, const fix2x2f&);
    template fix2x2b greater_equal(const fix2x2f&, const fix2x2f&);
    template fix2x2b equal_to(const fix2x2f&, const fix2x2f&);
    template fix2x2b not_equal_to(const fix2x2f&, const fix2x2f&);
}

namespace vmath_hpp
{
    template fix<bool> any(const qfix&);
    template fix<bool> all(const qfix&);
    template fix4b approx(const qfix&, const qfix&);
    template fix4b approx(const qfix&, const qfix&, fix<float>);
    template fix4b less(const qfix&, const qfix&);
    template fix4b less_equal(const qfix&, const qfix&);
    template fix4b greater(const qfix&, const qfix&);
    template fix4b greater_equal(const qfix&, const qfix&);
    template fix4b equal_to(const qfix&, const qfix&);
    template fix4b not_equal_to(const qfix&, const qfix&);
}

//
// Matrix Functions
//

namespace vmath_hpp
{
    template fix2x2f transpose(const fix2x2f&);
    template fix3x3f transpose(const fix3x3f&);
    template fix4x4f transpose(const fix4x4f&);

    template fix<float> determinant(const fix2x2f&);
    template fix<float> determinant(const fix3x3f&);
    template fix<float> determinant(const fix4x4f&);

    template fix2x2f inverse(const fix2x2f&);
    template fix3x3f inverse(const fix3x3f&);
    template fix4x4f inverse(const fix4x4f&);
}

//
// Quaternion Functions
//

namespace vmath_hpp
{
    template qfix conjugate(const qfix&);
    template qfix inverse(const qfix&);
}

//
// Access
//

namespace vmath_hpp
{
    template fix<float> component(const fix2f&, std::size_t);
    template fix2f component(fix2f, std::size_t, fix<float>);

    template fix2f row(const fix2x2f&, std::size_t);
    template fix2x2f row(fix2x2f, std::size_t, const fix2f&);

    template fix2f column(const fix2x2f&, std::size_t);
    template fix2x2f column(const fix2x2f&, std::size_t, const fix2f&);

    template fix<float> real(const qfix&);
    template qfix real(qfix, fix<float>);

    template fix3f imag(const qfix&);
    template qfix imag(qfix, const fix3f&);
}

//
// Matrix Transform 3D
//

namespace vmath_hpp
{
    template fix4x4f translate(fix<float> x, fix<float> y, fix<float> z);
    template fix4x4f translate(const fix4x4f&, fix<float>, fix<float>, fix<float>);
    template fix4x4f translate(const fix3f&);
    template fix4x4f translate(const fix4x4f&, const fix3f&);

    template fix4x4f rotate(const qfix&);
    template fix4x4f rotate(const fix4x4f&, const qfix&);
    template fix4x4f rotate(fix<float>, const fix3f&);
    template fix4x4f rotate(const fix4x4f&, fix<float>, const fix3f&);

    template fix4x4f rotate_x(fix<float>);
    template fix4x4f rotate_x(const fix4x4f&, fix<float>);

    template fix4x4f rotate_y(fix<float>);
    template fix4x4f rotate_y(const fix4x4f&, fix<float>);

    template fix4x4f rotate_z(fix<float>);
    template fix4x4f rotate_z(const fix4x4f&, fix<float>);

    template fix4x4f scale(fix<float>, fix<float>, fix<float>);
    template fix4x4f scale(const fix4x4f&, fix<float>, fix<float>, fix<float>);
    template fix4x4f scale(const fix3f&);
    template fix4x4f scale(const fix4x4f&, const fix3f&);

    template fix4x4f look_at_lh(const fix3f&, const fix3f&, const fix3f&);
    template fix4x4f look_at_rh(const fix3f&, const fix3f&, const fix3f&);
}

//
// Matrix Transform 2D
//

namespace vmath_hpp
{
    template fix3x3f translate(fix<float>, fix<float>);
    template fix3x3f translate(const fix3x3f&, fix<float>, fix<float>);
    template fix3x3f translate(const fix2f&);
    template fix3x3f translate(const fix3x3f&, const fix2f&);

    template fix3x3f rotate(fix<float>);
    template fix3x3f rotate(const fix3x3f&, fix<float>);

    template fix3x3f scale(fix<float>, fix<float>);
    template fix3x3f scale(const fix3x3f&, fix<float>, fix<float>);
    template fix3x3f scale(const fix2f&);
    template fix3x3f scale(const fix3x3f&, const fix2f&);

    template fix3x3f shear(fix<float>, fix<float>);
    template fix3x3f shear(const fix3x3f&, fix<float>, fix<float>);
    template fix3x3f shear(const fix2f&);
    template fix3x3f shear(const fix3x3f&, const fix2f&);

    template fix3x3f shear_x(fix<float>);
    template fix3x3f shear_x(const fix3x3f&, fix<float>);

    template fix3x3f shear_y(fix<float>);
    template fix3x3f shear_y(const fix3x3f&, fix<float>);
}

//
// Matrix Projections
//

namespace vmath_hpp
{
    template fix4x4f orthographic_lh(fix<float>, fix<float>, fix<float>, fix<float>);
    template fix4x4f orthographic_rh(fix<float>, fix<float>, fix<float>, fix<float>);

    template fix4x4f orthographic_lh(fix<float>, fix<float>, fix<float>, fix<float>, fix<float>, fix<float>);
    template fix4x4f orthographic_rh(fix<float>, fix<float>, fix<float>, fix<float>, fix<float>, fix<float>);

    template fix4x4f perspective_lh(fix<float>, fix<float>, fix<float>, fix<float>);
    template fix4x4f perspective_rh(fix<float>, fix<float>, fix<float>, fix<float>);

    template fix4x4f perspective_lh(fix<float>, fix<float>, fix<float>, fix<float>, fix<float>, fix<float>);
    template fix4x4f perspective_rh(fix<float>, fix<float>, fix<float>, fix<float>, fix<float>, fix<float>);

    template fix4x4f perspective_fov_lh(fix<float>, fix<float>, fix<float>, fix<float>);
    template fix4x4f perspective_fov_rh(fix<float>, fix<float>, fix<float>, fix<float>);
}

//
// Vector Transform
//

namespace vmath_hpp
{
    template fix<float> angle(const fix3f&, const fix3f&);
    template fix2f rotate(const fix2f&, fix<float>);
    template fix3f rotate_x(const fix3f&, fix<float>);
    template fix3f rotate_y(const fix3f&, fix<float>);
    template fix3f rotate_z(const fix3f&, fix<float>);
    template fix3f rotate(const fix3f&, const qfix&);
    template fix3f rotate(const fix3f&, fix<float>, const fix3f&);
    template fix3f project(const fix3f&, const fix3f&);
    template fix3f perpendicular(const fix3f&, const fix3f&);
}

//
// Quaternion Transform
//

namespace vmath_hpp
{
    template qfix qrotate(const fix3x3f&);
    template qfix qrotate(const qfix&, const fix3x3f&);

    template qfix qrotate(const fix3f&, const fix3f&);
    template qfix qrotate(const qfix&, const fix3f&, const fix3f&);

    template qfix qrotate(fix<float>, const fix3f&);
    template qfix qrotate(const qfix&, fix<float>, const fix3f&);

    template qfix qrotate_x(fix<float>);
    template qfix qrotate_x(const qfix&, fix<float>);

    template qfix qrotate_y(fix<float>);
    template qfix qrotate_y(const qfix&, fix<float>);

    template qfix qrotate_z(fix<float>);
    template qfix qrotate_z(const qfix&, fix<float>);

    template qfix qlook_at_lh(const fix3f&, const fix3f&);
    template qfix qlook_at_rh(const fix3f&, const fix3f&);
}

//
// fix_vec
//

TEST_CASE("vmath/fix_vec") {
    SUBCASE("fix2 ctors") {
        constexpr fix2i v0{};
        constexpr fix2i v1{fix(1)};
        constexpr fix2i v2{fix(1), fix(2)};
        constexpr fix2i v3{fix3i{fix(1), fix(2), fix(3)}};
        constexpr fix2i v4{fix4i{fix(1), fix(2), fix(3), fix(4)}};

        STATIC_CHECK((v0[0] == fix(0)));
        STATIC_CHECK((v1[0] == fix(1) && v1[1] == fix(1)));
        STATIC_CHECK((v2[0] == fix(1) && v2[1] == fix(2)));
        STATIC_CHECK((v3[0] == fix(1) && v3[1] == fix(2)));
        STATIC_CHECK((v4[0] == fix(1) && v4[1] == fix(2)));
    }

    SUBCASE("fix3 ctors") {
        constexpr fix3i v0{};
        constexpr fix3i v1{fix(1)};
        constexpr fix3i v2{fix(1), fix(2), fix(3)};
        constexpr fix3i v3{fix2i{fix(1), fix(2)}, fix(3)};
        constexpr fix3i v4{fix(1), fix2i{fix(2), fix(3)}};
        constexpr fix3i v5{fix4i{fix(1), fix(2), fix(3), fix(4)}};

        STATIC_CHECK((v0[0] == fix(0)));
        STATIC_CHECK((v1[0] == fix(1) && v1[1] == fix(1) && v1[2] == fix(1)));
        STATIC_CHECK((v2[0] == fix(1) && v2[1] == fix(2) && v2[2] == fix(3)));
        STATIC_CHECK((v3[0] == fix(1) && v3[1] == fix(2) && v3[2] == fix(3)));
        STATIC_CHECK((v4[0] == fix(1) && v4[1] == fix(2) && v4[2] == fix(3)));
        STATIC_CHECK((v5[0] == fix(1) && v5[1] == fix(2) && v5[2] == fix(3)));
    }

    SUBCASE("fix4 ctors") {
        constexpr fix4i v0{};
        constexpr fix4i v1{fix(1)};
        constexpr fix4i v2{fix(1), fix(2), fix(3), fix(4)};
        constexpr fix4i v3{fix2i{fix(1), fix(2)}, fix(3), fix(4)};
        constexpr fix4i v4{fix(1), fix2i{fix(2), fix(3)}, fix(4)};
        constexpr fix4i v5{fix(1), fix(2), fix2i{fix(3), fix(4)}};
        constexpr fix4i v6{fix2i{fix(1), fix(2)}, fix2i{fix(3), fix(4)}};
        constexpr fix4i v7{fix3i{fix(1), fix(2), fix(3)}, fix(4)};
        constexpr fix4i v8{fix(1), fix3i{fix(2), fix(3), fix(4)}};

        STATIC_CHECK((v0.at(0) == fix(0)));
        STATIC_CHECK((v1.at(0) == fix(1) && v1.at(1) == fix(1) && v1.at(2) == fix(1) && v1.at(3) == fix(1)));
        STATIC_CHECK((v2.at(0) == fix(1) && v2.at(1) == fix(2) && v2.at(2) == fix(3) && v2.at(3) == fix(4)));
        STATIC_CHECK((v3.at(0) == fix(1) && v3.at(1) == fix(2) && v3.at(2) == fix(3) && v3.at(3) == fix(4)));
        STATIC_CHECK((v4.at(0) == fix(1) && v4.at(1) == fix(2) && v4.at(2) == fix(3) && v4.at(3) == fix(4)));
        STATIC_CHECK((v5.at(0) == fix(1) && v5.at(1) == fix(2) && v5.at(2) == fix(3) && v5.at(3) == fix(4)));
        STATIC_CHECK((v6.at(0) == fix(1) && v6.at(1) == fix(2) && v6.at(2) == fix(3) && v6.at(3) == fix(4)));
        STATIC_CHECK((v7.at(0) == fix(1) && v7.at(1) == fix(2) && v7.at(2) == fix(3) && v7.at(3) == fix(4)));
        STATIC_CHECK((v8.at(0) == fix(1) && v8.at(1) == fix(2) && v8.at(2) == fix(3) && v8.at(3) == fix(4)));
    }

    SUBCASE("swap") {
        {
            vec v0{fix(1), fix(2)};
            vec v1{fix(3), fix(4)};
            swap(v0, v1);
            CHECK(v0 == fix2i(fix(3),fix(4)));
            CHECK(v1 == fix2i(fix(1),fix(2)));
        }
        {
            vec v0{fix{1},fix{2},fix{3}};
            vec v1{fix2i{fix(3),fix(4)}, fix{5}};
            swap(v0, v1);
            CHECK(v0 == fix3i(fix(3),fix(4),fix(5)));
            CHECK(v1 == fix3i(fix(1),fix(2),fix(3)));
        }
        {
            vec v0{fix{1},fix{2},fix{3},fix{4}};
            vec v1{fix{3},fix3i{fix(4),fix(5),fix(6)}};
            swap(v0, v1);
            CHECK(v0 == fix4i(fix(3),fix(4),fix(5),fix(6)));
            CHECK(v1 == fix4i(fix(1),fix(2),fix(3),fix(4)));
        }
    }

    SUBCASE("operators") {
        fix2b vb{};
        fix2i vi{};
        bool b{};

        vi = {+fix2i{fix(1),fix(2)}};
        vi = {-fix2i{fix(1),fix(2)}};
        vi = {~fix2i{fix(1),fix(2)}};
        vb = {!fix2i{fix(1),fix(2)}};

        vi = {fix2i{fix(1),fix(2)} + fix{3}};
        vi = {fix{3} + fix2i{fix(1),fix(2)}};
        vi = {fix2i{fix(1),fix(2)} + fix2i{fix(1),fix(2)}};

        vi = {fix2i{fix(1),fix(2)} - fix{3}};
        vi = {fix{3} - fix2i{fix(1),fix(2)}};
        vi = {fix2i{fix(1),fix(2)} - fix2i{fix(1),fix(2)}};

        vi = {fix2i{fix(1),fix(2)} * fix{3}};
        vi = {fix{3} * fix2i{fix(1),fix(2)}};
        vi = {fix2i{fix(1),fix(2)} * fix2i{fix(1),fix(2)}};

        vi = {fix2i{fix(1),fix(2)} / fix{3}};
        vi = {fix{3} / fix2i{fix(1),fix(2)}};
        vi = {fix2i{fix(1),fix(2)} / fix2i{fix(1),fix(2)}};

        vi = {fix2i{fix(1),fix(2)} & fix{3}};
        vi = {fix{3} & fix2i{fix(1),fix(2)}};
        vi = {fix2i{fix(1),fix(2)} & fix2i{fix(1),fix(2)}};

        vi = {fix2i{fix(1),fix(2)} | fix{3}};
        vi = {fix{3} | fix2i{fix(1),fix(2)}};
        vi = {fix2i{fix(1),fix(2)} | fix2i{fix(1),fix(2)}};

        vi = {fix2i{fix(1),fix(2)} ^ fix{3}};
        vi = {fix{3} ^ fix2i{fix(1),fix(2)}};
        vi = {fix2i{fix(1),fix(2)} ^ fix2i{fix(1),fix(2)}};

        vb = {fix2i{fix(1),fix(2)} && fix{3}};
        vb = {fix{3} && fix2i{fix(1),fix(2)}};
        vb = {fix2i{fix(1),fix(2)} && fix2i{fix(1),fix(2)}};

        vb = {fix2i{fix(1),fix(2)} || fix{3}};
        vb = {fix{3} || fix2i{fix(1),fix(2)}};
        vb = {fix2i{fix(1),fix(2)} || fix2i{fix(1),fix(2)}};

        b = {fix2i{fix(1),fix(2)} == fix2i{fix(1),fix(2)}};
        b = {fix2i{fix(1),fix(2)} != fix2i{fix(1),fix(2)}};
        b = {fix2i{fix(1),fix(2)} < fix2i{fix(1),fix(2)}};

        CHECK_FALSE(b);

        {
            vi = {vi += fix{3}};
            vi = {vi += fix2i{fix(4),fix(5)}};
            vi = {vi -= fix{3}};
            vi = {vi -= fix2i{fix(4),fix(5)}};
            vi = {vi *= fix{3}};
            vi = {vi *= fix2i{fix(4),fix(5)}};
            vi = {vi /= fix{3}};
            vi = {vi /= fix2i{fix(4),fix(5)}};
            vi = {vi &= fix{3}};
            vi = {vi &= fix2i{fix(4),fix(5)}};
            vi = {vi |= fix{3}};
            vi = {vi |= fix2i{fix(4),fix(5)}};
            vi = {vi ^= fix{3}};
            vi = {vi ^= fix2i{fix(4),fix(5)}};
        }
    }
}

//
// fix_mat
//

TEST_CASE("vmath/fix_mat") {
    SUBCASE("fix2x2 ctors") {
        constexpr fix2x2i v0{};
        constexpr fix2x2i v1{fix(2)};
        constexpr fix2x2i v2{fix2i{fix(1), fix(2)}};
        constexpr fix2x2i v3{fix(1), fix(2), fix(3), fix(4)};
        constexpr fix2x2i v4{{fix(1), fix(2)}, {fix(3), fix(4)}};
        constexpr fix2x2i v5{fix3x3i{fix(1)}};
        constexpr fix2x2i v6{fix4x4i{fix(1)}};

        STATIC_CHECK((v0[0] == fix2i(fix(1),fix(0)) && v0[1] == fix2i(fix(0),fix(1))));
        STATIC_CHECK((v1[0] == fix2i(fix(2),fix(0)) && v1[1] == fix2i(fix(0),fix(2))));
        STATIC_CHECK((v2[0] == fix2i(fix(1),fix(0)) && v2[1] == fix2i(fix(0),fix(2))));
        STATIC_CHECK((v3[0] == fix2i(fix(1),fix(2)) && v3[1] == fix2i(fix(3),fix(4))));
        STATIC_CHECK((v4[0] == fix2i(fix(1),fix(2)) && v4[1] == fix2i(fix(3),fix(4))));
        STATIC_CHECK((v5[0] == fix2i(fix(1),fix(0)) && v5[1] == fix2i(fix(0),fix(1))));
        STATIC_CHECK((v6[0] == fix2i(fix(1),fix(0)) && v6[1] == fix2i(fix(0),fix(1))));
    }

    SUBCASE("fix3x3 ctors") {
        constexpr fix3x3i v0{};
        constexpr fix3x3i v1{fix(2)};
        constexpr fix3x3i v2{fix3i{fix(1), fix(2), fix(3)}};
        constexpr fix3x3i v3{fix(1),fix(2),fix(3),fix(4),fix(5),fix(6),fix(7),fix(8),fix(9)};
        constexpr fix3x3i v4{{fix(1),fix(2),fix(3)},{fix(4),fix(5),fix(6)},{fix(7),fix(8),fix(9)}};
        constexpr fix3x3i v5{fix2x2i{fix(1)},fix2i{fix(0)}};
        constexpr fix3x3i v6{fix2x2i{fix(1)}};
        constexpr fix3x3i v7{fix4x4i{fix(1)}};

        STATIC_CHECK((v0[0] == fix3i(fix(1),fix(0),fix(0)) && v0[1] == fix3i(fix(0),fix(1),fix(0)) && v0[2] == fix3i(fix(0),fix(0),fix(1))));
        STATIC_CHECK((v1[0] == fix3i(fix(2),fix(0),fix(0)) && v1[1] == fix3i(fix(0),fix(2),fix(0)) && v1[2] == fix3i(fix(0),fix(0),fix(2))));
        STATIC_CHECK((v2[0] == fix3i(fix(1),fix(0),fix(0)) && v2[1] == fix3i(fix(0),fix(2),fix(0)) && v2[2] == fix3i(fix(0),fix(0),fix(3))));
        STATIC_CHECK((v3[0] == fix3i(fix(1),fix(2),fix(3)) && v3[1] == fix3i(fix(4),fix(5),fix(6)) && v3[2] == fix3i(fix(7),fix(8),fix(9))));
        STATIC_CHECK((v4[0] == fix3i(fix(1),fix(2),fix(3)) && v4[1] == fix3i(fix(4),fix(5),fix(6)) && v4[2] == fix3i(fix(7),fix(8),fix(9))));
        STATIC_CHECK((v5[0] == fix3i(fix(1),fix(0),fix(0)) && v5[1] == fix3i(fix(0),fix(1),fix(0)) && v5[2] == fix3i(fix(0),fix(0),fix(1))));
        STATIC_CHECK((v6[0] == fix3i(fix(1),fix(0),fix(0)) && v6[1] == fix3i(fix(0),fix(1),fix(0)) && v6[2] == fix3i(fix(0),fix(0),fix(1))));
        STATIC_CHECK((v7[0] == fix3i(fix(1),fix(0),fix(0)) && v7[1] == fix3i(fix(0),fix(1),fix(0)) && v7[2] == fix3i(fix(0),fix(0),fix(1))));
    }

    SUBCASE("fix4x4 ctors") {
        constexpr fix4x4i v0{};
        constexpr fix4x4i v1{fix(2)};
        constexpr fix4x4i v2{fix4i{fix(1),fix(2),fix(3),fix(4)}};
        constexpr fix4x4i v3{fix(1),fix(2),fix(3),fix(4),fix(5),fix(6),fix(7),fix(8),fix(9),fix(10),fix(11),fix(12),fix(13),fix(14),fix(15),fix(16)};
        constexpr fix4x4i v4{{fix(1),fix(2),fix(3),fix(4)},{fix(5),fix(6),fix(7),fix(8)},{fix(9),fix(10),fix(11),fix(12)},{fix(13),fix(14),fix(15),fix(16)}};
        constexpr fix4x4i v5{fix3x3i{fix(1)},fix3i{fix(0)}};
        constexpr fix4x4i v6{fix2x2i{fix(1)}};
        constexpr fix4x4i v7{fix3x3i{fix(1)}};

        STATIC_CHECK((v0[0] == fix4i(fix(1),fix(0),fix(0),fix(0)) && v0[1] == fix4i(fix(0),fix(1),fix(0),fix(0)) && v0[2] == fix4i(fix(0),fix(0),fix(1),fix(0)) && v0[3] == fix4i(fix(0),fix(0),fix(0),fix(1))));
        STATIC_CHECK((v1[0] == fix4i(fix(2),fix(0),fix(0),fix(0)) && v1[1] == fix4i(fix(0),fix(2),fix(0),fix(0)) && v1[2] == fix4i(fix(0),fix(0),fix(2),fix(0)) && v1[3] == fix4i(fix(0),fix(0),fix(0),fix(2))));
        STATIC_CHECK((v2[0] == fix4i(fix(1),fix(0),fix(0),fix(0)) && v2[1] == fix4i(fix(0),fix(2),fix(0),fix(0)) && v2[2] == fix4i(fix(0),fix(0),fix(3),fix(0)) && v2[3] == fix4i(fix(0),fix(0),fix(0),fix(4))));
        STATIC_CHECK((v3[0] == fix4i(fix(1),fix(2),fix(3),fix(4)) && v3[1] == fix4i(fix(5),fix(6),fix(7),fix(8)) && v3[2] == fix4i(fix(9),fix(10),fix(11),fix(12)) && v3[3] == fix4i(fix(13),fix(14),fix(15),fix(16))));
        STATIC_CHECK((v4[0] == fix4i(fix(1),fix(2),fix(3),fix(4)) && v4[1] == fix4i(fix(5),fix(6),fix(7),fix(8)) && v4[2] == fix4i(fix(9),fix(10),fix(11),fix(12)) && v4[3] == fix4i(fix(13),fix(14),fix(15),fix(16))));
        STATIC_CHECK((v5[0] == fix4i(fix(1),fix(0),fix(0),fix(0)) && v5[1] == fix4i(fix(0),fix(1),fix(0),fix(0)) && v5[2] == fix4i(fix(0),fix(0),fix(1),fix(0)) && v5[3] == fix4i(fix(0),fix(0),fix(0),fix(1))));
        STATIC_CHECK((v6[0] == fix4i(fix(1),fix(0),fix(0),fix(0)) && v6[1] == fix4i(fix(0),fix(1),fix(0),fix(0)) && v6[2] == fix4i(fix(0),fix(0),fix(1),fix(0)) && v6[3] == fix4i(fix(0),fix(0),fix(0),fix(1))));
        STATIC_CHECK((v7[0] == fix4i(fix(1),fix(0),fix(0),fix(0)) && v7[1] == fix4i(fix(0),fix(1),fix(0),fix(0)) && v7[2] == fix4i(fix(0),fix(0),fix(1),fix(0)) && v7[3] == fix4i(fix(0),fix(0),fix(0),fix(1))));
    }

    SUBCASE("swap") {
        {
            fix2x2i v0{fix(1)};
            fix2x2i v1{fix(2)};
            swap(v0, v1);
            CHECK(v0 == fix2x2i(fix(2)));
            CHECK(v1 == fix2x2i(fix(1)));
        }
        {
            fix3x3i v0{fix(1)};
            fix3x3i v1{fix(2)};
            swap(v0, v1);
            CHECK(v0 == fix3x3i(fix(2)));
            CHECK(v1 == fix3x3i(fix(1)));
        }
        {
            fix4x4i v0{fix(1)};
            fix4x4i v1{fix(2)};
            swap(v0, v1);
            CHECK(v0 == fix4x4i(fix(2)));
            CHECK(v1 == fix4x4i(fix(1)));
        }
    }

    SUBCASE("operators") {
        fix2x2b mb{};
        fix2x2i mi{};
        fix2i vi{};
        bool b{};

        mi = {+fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mi = {-fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mi = {~fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mb = {!fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} + fix{3}};
        mi = {fix{3} + fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} + fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} - fix{3}};
        mi = {fix{3} - fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} - fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} * fix{3}};
        mi = {fix{3} * fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        vi = {vi * mi};
        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} * fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} / fix{3}};
        mi = {fix{3} / fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        // mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} / fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} & fix{3}};
        mi = {fix{3} & fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} & fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} | fix{3}};
        mi = {fix{3} | fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} | fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} ^ fix{3}};
        mi = {fix{3} ^ fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mi = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} ^ fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mb = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} && fix{3}};
        mb = {fix{3} && fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mb = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} && fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        mb = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} || fix{3}};
        mb = {fix{3} || fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        mb = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} || fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        b = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} == fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        b = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} != fix2x2i{fix(1),fix(2),fix(3),fix(4)}};
        b = {fix2x2i{fix(1),fix(2),fix(3),fix(4)} < fix2x2i{fix(1),fix(2),fix(3),fix(4)}};

        CHECK_FALSE(b);

        {
            mi = {mi += fix{3}};
            mi = {mi += fix2x2i{fix(4),fix(5),fix(6),fix(7)}};
            mi = {mi -= fix{3}};
            mi = {mi -= fix2x2i{fix(4),fix(5),fix(6),fix(7)}};
            mi = {mi *= fix{3}};
            vi = {vi *= fix2x2i{fix(4),fix(5),fix(6),fix(7)}};
            mi = {mi *= fix2x2i{fix(4),fix(5),fix(6),fix(7)}};
            mi = {mi /= fix{3}};
            //mi = {mi /= fix2x2i{fix(4),fix(5),fix(6),fix(7)}};
            mi = {mi &= fix{3}};
            mi = {mi &= fix2x2i{fix(4),fix(5),fix(6),fix(7)}};
            mi = {mi |= fix{3}};
            mi = {mi |= fix2x2i{fix(4),fix(5),fix(6),fix(7)}};
            mi = {mi ^= fix{3}};
            mi = {mi ^= fix2x2i{fix(4),fix(5),fix(6),fix(7)}};
        }
    }
}

//
// fix_qua
//

TEST_CASE("vmath/fix_qua") {
    SUBCASE("ctors") {
        constexpr qfix v0{};
        constexpr qfix v1{fix(1.f), fix(2.f), fix(3.f), fix(4.f)};
        constexpr qfix v2{fix3f{fix(1.f), fix(2.f), fix(3.f)}, fix(4.f)};
        constexpr qfix v3{fix4f{fix(1.f), fix(2.f), fix(3.f), fix(4.f)}};

        STATIC_CHECK((v0.at(0) == fix(0.f)));
        STATIC_CHECK((v1.at(0) == fix(1.f) && v1.at(1) == fix(2.f) && v1.at(2) == fix(3.f) && v1.at(3) == fix(4.f)));
        STATIC_CHECK((v2.at(0) == fix(1.f) && v2.at(1) == fix(2.f) && v2.at(2) == fix(3.f) && v2.at(3) == fix(4.f)));
        STATIC_CHECK((v3.at(0) == fix(1.f) && v3.at(1) == fix(2.f) && v3.at(2) == fix(3.f) && v3.at(3) == fix(4.f)));
    }

    SUBCASE("swap") {
        qfix v0{fix(1.f),fix(2.f),fix(3.f),fix(4.f)};
        qfix v1{fix(4.f),fix(3.f),fix(2.f),fix(1.f)};
        swap(v0, v1);
        CHECK(v0 == qfix(fix(4.f),fix(3.f),fix(2.f),fix(1.f)));
        CHECK(v1 == qfix(fix(1.f),fix(2.f),fix(3.f),fix(4.f)));
    }

    SUBCASE("operators") {
        qfix qf;
        fix3f vf;
        bool b{};

        qf = {+qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {-qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};

        qf = {qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)} + qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)} - qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)} * fix{1.f}};
        qf = {fix{1.f} * qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        vf = {fix3f{fix(1.f),fix(2.f),fix(3.f)} * qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)} * qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)} / fix{1.f}};
        qf = {fix{1.f} / qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};

        qf = {qf += qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {qf -= qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {qf *= fix{1.f}};
        vf = {vf *= qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {qf *= qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        qf = {qf /= fix{1.f}};

        b = {qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)} == qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        b = {qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)} != qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};
        b = {qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)} < qfix{fix(1.f),fix(2.f),fix(3.f),fix(4.f)}};

        CHECK_FALSE(b);
    }
}

//
// Units
//

TEST_CASE("vmath/fix_units") {
    {
        STATIC_CHECK(zero2<fix<float>> == fix2f{fix(0.f),fix(0.f)});
        STATIC_CHECK(zero3<fix<float>> == fix3f{fix(0.f),fix(0.f),fix(0.f)});
        STATIC_CHECK(zero4<fix<float>> == fix4f{fix(0.f),fix(0.f),fix(0.f),fix(0.f)});
    }
    {
        STATIC_CHECK(unit2<fix<float>> == fix2f{fix(1.f),fix(1.f)});
        STATIC_CHECK(unit3<fix<float>> == fix3f{fix(1.f),fix(1.f),fix(1.f)});
        STATIC_CHECK(unit4<fix<float>> == fix4f{fix(1.f),fix(1.f),fix(1.f),fix(1.f)});
    }
    {
        STATIC_CHECK(unit2_x<fix<float>> == fix2f{fix(1.f),fix(0.f)});
        STATIC_CHECK(unit2_y<fix<float>> == fix2f{fix(0.f),fix(1.f)});

        STATIC_CHECK(unit3_x<fix<float>> == fix3f{fix(1.f),fix(0.f),fix(0.f)});
        STATIC_CHECK(unit3_y<fix<float>> == fix3f{fix(0.f),fix(1.f),fix(0.f)});
        STATIC_CHECK(unit3_z<fix<float>> == fix3f{fix(0.f),fix(0.f),fix(1.f)});

        STATIC_CHECK(unit4_x<fix<float>> == fix4f{fix(1.f),fix(0.f),fix(0.f),fix(0.f)});
        STATIC_CHECK(unit4_y<fix<float>> == fix4f{fix(0.f),fix(1.f),fix(0.f),fix(0.f)});
        STATIC_CHECK(unit4_z<fix<float>> == fix4f{fix(0.f),fix(0.f),fix(1.f),fix(0.f)});
        STATIC_CHECK(unit4_w<fix<float>> == fix4f{fix(0.f),fix(0.f),fix(0.f),fix(1.f)});
    }
    {
        STATIC_CHECK(zero2x2<fix<float>> == fix2x2f{
            fix(0.f),fix(0.f),
            fix(0.f),fix(0.f)});
        STATIC_CHECK(zero3x3<fix<float>> == fix3x3f{
            fix(0.f),fix(0.f),fix(0.f),
            fix(0.f),fix(0.f),fix(0.f),
            fix(0.f),fix(0.f),fix(0.f)});
        STATIC_CHECK(zero4x4<fix<float>> == fix4x4f{
            fix(0.f),fix(0.f),fix(0.f),fix(0.f),
            fix(0.f),fix(0.f),fix(0.f),fix(0.f),
            fix(0.f),fix(0.f),fix(0.f),fix(0.f),
            fix(0.f),fix(0.f),fix(0.f),fix(0.f)});
    }
    {
        STATIC_CHECK(unit2x2<fix<float>> == fix2x2f{
            fix(1.f),fix(1.f),
            fix(1.f),fix(1.f)});
        STATIC_CHECK(unit3x3<fix<float>> == fix3x3f{
            fix(1.f),fix(1.f),fix(1.f),
            fix(1.f),fix(1.f),fix(1.f),
            fix(1.f),fix(1.f),fix(1.f)});
        STATIC_CHECK(unit4x4<fix<float>> == fix4x4f{
            fix(1.f),fix(1.f),fix(1.f),fix(1.f),
            fix(1.f),fix(1.f),fix(1.f),fix(1.f),
            fix(1.f),fix(1.f),fix(1.f),fix(1.f),
            fix(1.f),fix(1.f),fix(1.f),fix(1.f)});
    }
    {
        STATIC_CHECK(identity2x2<fix<float>> == fix2x2f{
            fix(1.f),fix(0.f),
            fix(0.f),fix(1.f)});
        STATIC_CHECK(identity3x3<fix<float>> == fix3x3f{
            fix(1.f),fix(0.f),fix(0.f),
            fix(0.f),fix(1.f),fix(0.f),
            fix(0.f),fix(0.f),fix(1.f)});
        STATIC_CHECK(identity4x4<fix<float>> == fix4x4f{
            fix(1.f),fix(0.f),fix(0.f),fix(0.f),
            fix(0.f),fix(1.f),fix(0.f),fix(0.f),
            fix(0.f),fix(0.f),fix(1.f),fix(0.f),
            fix(0.f),fix(0.f),fix(0.f),fix(1.f)});
    }
    {
        STATIC_CHECK(qidentity<fix<float>> == qfix{
            fix(0.f),fix(0.f),fix(0.f),
            fix(1.f)});
    }
}
