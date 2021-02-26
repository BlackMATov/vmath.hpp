/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/vmath.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2020-2021, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include "vmath_fwd.hpp"

#include "vmath_fun.hpp"
#include "vmath_vec_fun.hpp"
#include "vmath_mat_fun.hpp"
#include "vmath_qua_fun.hpp"

//
// Units
//

namespace vmath_hpp
{
    template < typename T > inline constexpr vec<T, 2> zero2{zero_init};
    template < typename T > inline constexpr vec<T, 3> zero3{zero_init};
    template < typename T > inline constexpr vec<T, 4> zero4{zero_init};

    template < typename T > inline constexpr vec<T, 2> unit2{unit_init};
    template < typename T > inline constexpr vec<T, 3> unit3{unit_init};
    template < typename T > inline constexpr vec<T, 4> unit4{unit_init};

    template < typename T > inline constexpr vec<T, 2> unit2_x{T{1}, T{0}};
    template < typename T > inline constexpr vec<T, 2> unit2_y{T{0}, T{1}};

    template < typename T > inline constexpr vec<T, 3> unit3_x{T{1}, T{0}, T{0}};
    template < typename T > inline constexpr vec<T, 3> unit3_y{T{0}, T{1}, T{0}};
    template < typename T > inline constexpr vec<T, 3> unit3_z{T{0}, T{0}, T{1}};

    template < typename T > inline constexpr vec<T, 4> unit4_x{T{1}, T{0}, T{0}, T{0}};
    template < typename T > inline constexpr vec<T, 4> unit4_y{T{0}, T{1}, T{0}, T{0}};
    template < typename T > inline constexpr vec<T, 4> unit4_z{T{0}, T{0}, T{1}, T{0}};
    template < typename T > inline constexpr vec<T, 4> unit4_w{T{0}, T{0}, T{0}, T{1}};

    template < typename T > inline constexpr mat<T, 2> mzero2{zero_init};
    template < typename T > inline constexpr mat<T, 3> mzero3{zero_init};
    template < typename T > inline constexpr mat<T, 4> mzero4{zero_init};

    template < typename T > inline constexpr mat<T, 2> munit2{unit_init};
    template < typename T > inline constexpr mat<T, 3> munit3{unit_init};
    template < typename T > inline constexpr mat<T, 4> munit4{unit_init};

    template < typename T > inline constexpr mat<T, 2> midentity2{identity_init};
    template < typename T > inline constexpr mat<T, 3> midentity3{identity_init};
    template < typename T > inline constexpr mat<T, 4> midentity4{identity_init};

    template < typename T > inline constexpr qua<T> qzero{zero_init};
    template < typename T > inline constexpr qua<T> qidentity{identity_init};
}

//
// Hash
//

namespace vmath_hpp::detail
{
    struct hash_combiner {
        template < typename T >
        [[nodiscard]] std::size_t operator()(std::size_t seed, const T& x) noexcept {
            return (seed ^= std::hash<T>{}(x) + 0x9e3779b9 + (seed << 6) + ( seed >> 2));
        }
    };

    template < typename T, size_t Size >
    [[nodiscard]] std::size_t hash(const vec<T, Size>& v) noexcept {
        return fold_join(hash_combiner{}, std::size_t{}, v);
    }

    template < typename T, size_t Size >
    [[nodiscard]] std::size_t hash(const mat<T, Size>& m) noexcept {
        return fold_join(hash_combiner{}, std::size_t{}, m);
    }

    template < typename T >
    [[nodiscard]] std::size_t hash(const qua<T>& q) noexcept {
        return fold_join(hash_combiner{}, std::size_t{}, q);
    }
}

namespace std
{
    template < typename T, size_t Size >
    struct hash<vmath_hpp::vec<T, Size>> {
        size_t operator()(const vmath_hpp::vec<T, Size>& v) const noexcept {
            return vmath_hpp::detail::hash(v);
        }
    };

    template < typename T, size_t Size >
    struct hash<vmath_hpp::mat<T, Size>> {
        size_t operator()(const vmath_hpp::mat<T, Size>& m) const noexcept {
            return vmath_hpp::detail::hash(m);
        }
    };

    template < typename T >
    struct hash<vmath_hpp::qua<T>> {
        size_t operator()(const vmath_hpp::qua<T>& q) const noexcept {
            return vmath_hpp::detail::hash(q);
        }
    };
}

//
// Cast
//

namespace vmath_hpp
{
    template < typename To, typename From >
    [[nodiscard]] std::enable_if_t<
        std::is_arithmetic_v<To> && std::is_arithmetic_v<From>
    , To>
    constexpr cast_to(From x) noexcept {
        return static_cast<To>(x);
    }

    template < typename To, typename From, std::size_t Size >
    [[nodiscard]] constexpr vec<To, Size> cast_to(const vec<From, Size>& v) {
        return map_join([](From x){ return cast_to<To>(x); }, v);
    }

    template < typename To, typename From, std::size_t Size >
    [[nodiscard]] constexpr mat<To, Size> cast_to(const mat<From, Size>& m) {
        return map_join([](const vec<From, Size>& v){ return cast_to<To>(v); }, m);
    }

    template < typename To, typename From >
    [[nodiscard]] constexpr qua<To> cast_to(const qua<From>& q) {
        return map_join([](From x){ return cast_to<To>(x); }, q);
    }
}

//
// Access
//

namespace vmath_hpp
{
    // component

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T component(const vec<T, Size>& v, std::size_t index) {
        return v[index];
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> component(vec<T, Size> v, std::size_t index, T component) {
        v[index] = component;
        return v;
    }

    // row

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> row(const mat<T, Size>& m, std::size_t index) {
        return m.rows[index];
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> row(mat<T, Size> m, std::size_t index, const vec<T, Size>& row) {
        m.rows[index] = row;
        return m;
    }

    // column

    namespace impl
    {
        template < typename T, std::size_t Size, std::size_t... Is >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        vec<T, Size> column_impl(const mat<T, Size>& m, std::size_t index, std::index_sequence<Is...>) {
            return { m[Is][index]... };
        }

        template < typename T, std::size_t Size, std::size_t... Is >
        [[nodiscard]] constexpr VMATH_HPP_FORCE_INLINE
        mat<T, Size> column_impl(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& column, std::index_sequence<Is...>) {
            return { component(m[Is], index, column[Is])... };
        }
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> column(const mat<T, Size>& m, std::size_t index) {
        return impl::column_impl(m, index, std::make_index_sequence<Size>{});
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> column(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& column) {
        return impl::column_impl(m, index, column, std::make_index_sequence<Size>{});
    }

    // real

    template < typename T >
    [[nodiscard]] constexpr T real(const qua<T>& q) {
        return q.s;
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> real(qua<T> q, T real) {
        q.s = real;
        return q;
    }

    // imag

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> imag(const qua<T>& q) {
        return q.v;
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> imag(qua<T> q, const vec<T, 3>& imag) {
        q.v = imag;
        return q;
    }
}

//
// Matrix Transform 3D
//

namespace vmath_hpp
{
    // translate

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> translate(T x, T y, T z) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Translation_(geometry)

        return {
            { T{1}, T{0}, T{0}, T{0} },
            { T{0}, T{1}, T{0}, T{0} },
            { T{0}, T{0}, T{1}, T{0} },
            {   x,    y,    z,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> translate(const mat<T, 4>& m, T x, T y, T z) {
        return m * translate(x, y, z);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> translate(const vec<T, 3>& v) {
        return translate(v.x, v.y, v.z);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> translate(const mat<T, 4>& m, const vec<T, 3>& v) {
        return m * translate(v);
    }

    // rotate

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate(const qua<T>& q) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/

        const auto [qv, qs] = normalize(q);

        const T x2 = qv.x * T{2};
        const T y2 = qv.y * T{2};
        const T z2 = qv.z * T{2};

        const T sx2 = qs * x2;
        const T sy2 = qs * y2;
        const T sz2 = qs * z2;

        const T xx2 = qv.x * x2;
        const T xy2 = qv.x * y2;
        const T xz2 = qv.x * z2;

        const T yy2 = qv.y * y2;
        const T yz2 = qv.y * z2;
        const T zz2 = qv.z * z2;

        return {
            { T{1} - (yy2 + zz2), (xy2 + sz2),        (xz2 - sy2)        },
            { (xy2 - sz2),        T{1} - (xx2 + zz2), (yz2 + sx2)        },
            { (xz2 + sy2),        (yz2 - sx2),        T{1} - (xx2 + yy2) }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate(const mat<T, 3>& m, const qua<T>& q) {
        return m * rotate(q);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate(T angle, const vec<T, 3>& axis) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/

        const auto [s, c] = sincos(angle);
        const auto [x, y, z] = normalize(axis);

        const T xx = x * x;
        const T yy = y * y;
        const T zz = z * z;

        const T xs = x * s;
        const T ys = y * s;
        const T zs = z * s;

        const T ic = T{1} - c;

        const T xxm = xx * ic;
        const T yym = yy * ic;
        const T zzm = zz * ic;

        const T xym = x * y * ic;
        const T xzm = x * z * ic;
        const T yzm = y * z * ic;

        return {
            { xxm + c,  xym + zs, xzm - ys },
            { xym - zs, yym + c,  yzm + xs },
            { xzm + ys, yzm - xs, zzm + c  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate(const mat<T, 3>& m, T angle, const vec<T, 3>& axis) {
        return m * rotate(angle, axis);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_x(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);

        return {
            { T{1}, T{0}, T{0} },
            { T{0},   c,    s  },
            { T{0},  -s,    c  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_x(const mat<T, 3>& m, T angle) {
        return m * rotate_x(angle);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_y(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);

        return {
            {   c,  T{0},  -s  },
            { T{0}, T{1}, T{0} },
            {   s,  T{0},   c  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_y(const mat<T, 3>& m, T angle) {
        return m * rotate_y(angle);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_z(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);

        return {
            {   c,    s,  T{0} },
            {  -s,    c,  T{0} },
            { T{0}, T{0}, T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> rotate_z(const mat<T, 3>& m, T angle) {
        return m * rotate_z(angle);
    }

    // scale

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(T x, T y, T z) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Scaling_(geometry)

        return {
            {   x,  T{0}, T{0} },
            { T{0},   y,  T{0} },
            { T{0}, T{0},   z  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(const mat<T, 3>& m, T x, T y, T z) {
        return m * scale(x, y, z);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(const vec<T, 3>& v) {
        return scale(v.x, v.y, v.z);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(const mat<T, 3>& m, const vec<T, 3>& v) {
        return m * scale(v);
    }

    // look_at

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> look_at_lh(
        const vec<T, 3>& dir,
        const vec<T, 3>& up)
    {
        /// REFERENCE:
        /// https://www.euclideanspace.com/maths/algebra/vectors/lookat/

        const vec az = normalize(dir);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        return {
            { ax.x, ay.x, az.x },
            { ax.y, ay.y, az.y },
            { ax.z, ay.z, az.z }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> look_at_lh(
        const vec<T, 3>& eye,
        const vec<T, 3>& at,
        const vec<T, 3>& up)
    {
        /// REFERENCE:
        /// https://www.euclideanspace.com/maths/algebra/vectors/lookat/

        const vec az = normalize(at - eye);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        const T dx = dot(ax, eye);
        const T dy = dot(ay, eye);
        const T dz = dot(az, eye);

        return {
            { ax.x, ay.x, az.x, T{0} },
            { ax.y, ay.y, az.y, T{0} },
            { ax.z, ay.z, az.z, T{0} },
            { -dx,  -dy,  -dz,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> look_at_rh(
        const vec<T, 3>& dir,
        const vec<T, 3>& up)
    {
        /// REFERENCE:
        /// https://www.euclideanspace.com/maths/algebra/vectors/lookat/

        const vec az = normalize(-dir);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        return {
            { ax.x, ay.x, az.x },
            { ax.y, ay.y, az.y },
            { ax.z, ay.z, az.z }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> look_at_rh(
        const vec<T, 3>& eye,
        const vec<T, 3>& at,
        const vec<T, 3>& up)
    {
        /// REFERENCE:
        /// https://www.euclideanspace.com/maths/algebra/vectors/lookat/

        const vec az = normalize(eye - at);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        const T dx = dot(ax, eye);
        const T dy = dot(ay, eye);
        const T dz = dot(az, eye);

        return {
            { ax.x, ay.x, az.x, T{0} },
            { ax.y, ay.y, az.y, T{0} },
            { ax.z, ay.z, az.z, T{0} },
            { -dx,  -dy,  -dz,  T{1} }};
    }
}

//
// Matrix Transform 2D
//

namespace vmath_hpp
{
    // translate

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> translate(T x, T y) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Translation_(geometry)

        return {
            { T{1}, T{0}, T{0} },
            { T{0}, T{1}, T{0} },
            {   x,    y,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> translate(const mat<T, 3>& m, T x, T y) {
        return m * translate(x, y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> translate(const vec<T, 2>& v) {
        return translate(v.x, v.y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> translate(const mat<T, 3>& m, const vec<T, 2>& v) {
        return m * translate(v);
    }

    // rotate

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> rotate(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);

        return {
            {  c, s },
            { -s, c }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> rotate(const mat<T, 2>& m, T angle) {
        return m * rotate(angle);
    }

    // scale

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> scale(T x, T y) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Scaling_(geometry)

        return {
            {   x,  T{0} },
            { T{0},   y  }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> scale(const mat<T, 2>& m, T x, T y) {
        return m * scale(x, y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> scale(const vec<T, 2>& v) {
        return scale(v.x, v.y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> scale(const mat<T, 2>& m, const vec<T, 2>& v) {
        return m * scale(v);
    }

    // shear

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear(T x, T y) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Shear_matrix

        return {
            { T{1},   y  },
            {   x,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear(const mat<T, 2>& m, T x, T y) {
        return m * shear(x, y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear(const vec<T, 2>& v) {
        return shear(v.x, v.y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear(const mat<T, 2>& m, const vec<T, 2>& v) {
        return m * shear(v);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear_x(T x) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Shear_matrix

        return {
            { T{1}, T{0} },
            {   x,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear_x(const mat<T, 2>& m, T x) {
        return m * shear_x(x);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear_y(T y) {
        /// REFERENCE:
        /// https://en.wikipedia.org/wiki/Shear_matrix

        return {
            { T{1},   y  },
            { T{0}, T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 2> shear_y(const mat<T, 2>& m, T y) {
        return m * shear_y(y);
    }
}

//
// Matrix Projections
//

namespace vmath_hpp
{
    // orthographic

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> orthographic_lh(T width, T height, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixortholh

        const T rwidth = rcp(width);
        const T rheight = rcp(height);
        const T frange = rcp(zfar - znear);

        const T sx = T{2} * rwidth;
        const T sy = T{2} * rheight;
        const T sz = frange;
        const T tz = -frange * znear;

        return {
            {  sx,   T{0},  T{0},  T{0} },
            { T{0},   sy,   T{0},  T{0} },
            { T{0},  T{0},   sz,   T{0} },
            { T{0},  T{0},   tz,   T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> orthographic_rh(T width, T height, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixorthorh

        const T rwidth = rcp(width);
        const T rheight = rcp(height);
        const T frange = rcp(znear - zfar);

        const T sx = T{2} * rwidth;
        const T sy = T{2} * rheight;
        const T sz = frange;
        const T tz = frange * znear;

        return {
            {  sx,  T{0}, T{0}, T{0} },
            { T{0},  sy,  T{0}, T{0} },
            { T{0}, T{0},  sz,  T{0} },
            { T{0}, T{0},  tz,  T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> orthographic_lh(T left, T right, T bottom, T top, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixorthooffcenterlh

        const T rwidth = rcp(right - left);
        const T rheight = rcp(top - bottom);
        const T frange = rcp(zfar - znear);

        return {
            { T{2} * rwidth,            T{0},                      T{0},            T{0} },
            { T{0},                     T{2} * rheight,            T{0},            T{0} },
            { T{0},                     T{0},                      frange,          T{0} },
            { -(left + right) * rwidth, -(top + bottom) * rheight, -frange * znear, T{1} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> orthographic_rh(T left, T right, T bottom, T top, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixorthooffcenterrh

        const T rwidth = rcp(right - left);
        const T rheight = rcp(top - bottom);
        const T frange = rcp(znear - zfar);

        return {
            { T{2} * rwidth,            T{0},                      T{0},           T{0} },
            { T{0},                     T{2} * rheight,            T{0},           T{0} },
            { T{0},                     T{0},                      frange,         T{0} },
            { -(left + right) * rwidth, -(top + bottom) * rheight, frange * znear, T{1} }};
    }

    // perspective

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_lh(T width, T height, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectivelh

        const T sx = T{2} * znear * rcp(width);
        const T sy = T{2} * znear * rcp(height);
        const T sz = zfar * rcp(zfar - znear);
        const T tz = (znear * zfar) * rcp(znear - zfar);

        return {
            { T{sx}, T{0},  T{0},  T{0} },
            { T{0},  T{sy}, T{0},  T{0} },
            { T{0},  T{0},  T{sz}, T{1} },
            { T{0},  T{0},  T{tz}, T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_rh(T width, T height, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectiverh

        const T sx = T{2} * znear * rcp(width);
        const T sy = T{2} * znear * rcp(height);
        const T sz = zfar * rcp(znear - zfar);
        const T tz = (znear * zfar) * rcp(znear - zfar);

        return {
            {  sx,  T{0}, T{0},  T{0} },
            { T{0},  sy,  T{0},  T{0} },
            { T{0}, T{0},  sz,  -T{1} },
            { T{0}, T{0},  tz,   T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_lh(T left, T right, T bottom, T top, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectiveoffcenterlh

        const T znear2 = T{2} * znear;
        const T rwidth = rcp(right - left);
        const T rheight = rcp(top - bottom);
        const T frange = zfar * rcp(zfar - znear);

        return {
            { znear2 * rwidth,          T{0},                      T{0},            T{0} },
            { T{0},                     znear2 * rheight,          T{0},            T{0} },
            { -(left + right) * rwidth, -(top + bottom) * rheight, frange,          T{1} },
            { T{0},                     T{0},                      -frange * znear, T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_rh(T left, T right, T bottom, T top, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectiveoffcenterrh

        const T znear2 = T{2} * znear;
        const T rwidth = rcp(right - left);
        const T rheight = rcp(top - bottom);
        const T frange = zfar * rcp(znear - zfar);

        return {
            { znear2 * rwidth,         T{0},                     T{0},            T{0} },
            { T{0},                    znear2 * rheight,         T{0},            T{0} },
            { (left + right) * rwidth, (top + bottom) * rheight, frange,         -T{1} },
            { T{0},                    T{0},                     frange * znear,  T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_fov_lh(T fovy, T aspect, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectivefovlh

        const T sy = rcp(tan(fovy * T{0.5f}));
        const T sx = sy * rcp(aspect);
        const T sz = zfar * rcp(zfar - znear);
        const T tz = (znear * zfar) * rcp(znear - zfar);

        return {
            {  sx,  T{0}, T{0}, T{0} },
            { T{0},  sy,  T{0}, T{0} },
            { T{0}, T{0},  sz,  T{1} },
            { T{0}, T{0},  tz,  T{0} }};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> perspective_fov_rh(T fovy, T aspect, T znear, T zfar) {
        /// REFERENCE:
        /// https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrixperspectivefovrh

        const T sy = rcp(tan(fovy * T{0.5f}));
        const T sx = sy * rcp(aspect);
        const T sz = zfar * rcp(znear - zfar);
        const T tz = (znear * zfar) * rcp(znear - zfar);
        return  {
            {  sx,  T{0}, T{0},  T{0} },
            { T{0},  sy,  T{0},  T{0} },
            { T{0}, T{0},  sz,  -T{1} },
            { T{0}, T{0},  tz,   T{0} }};
    }
}

//
// Vector Transform
//

namespace vmath_hpp
{
    // angle

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr T angle(const vec<T, Size>& x, const vec<T, Size>& y) {
        const T rs = rsqrt(length2(x) * length2(y));
        return acos(clamp(dot(x, y) * rs, -T{1}, T{1}));
    }

    // rotate

    template < typename T >
    [[nodiscard]] constexpr vec<T, 2> rotate(const vec<T, 2>& v, T angle) {
        return v * rotate(angle);
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate_x(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_x<T>);
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate_y(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_y<T>);
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate_z(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_z<T>);
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate(const vec<T, 3>& v, const qua<T>& q) {
        return v * q;
    }

    template < typename T >
    [[nodiscard]] constexpr vec<T, 3> rotate(const vec<T, 3>& v, T angle, const vec<T, 3>& axis) {
        return v * qrotate(angle, axis);
    }

    // project

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> project(const vec<T, Size>& v, const vec<T, Size>& normal) {
        return dot(v, normal) * rlength2(normal) * normal;
    }

    // perpendicular

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> perpendicular(const vec<T, Size>& v, const vec<T, Size>& normal) {
        return v - project(v, normal);
    }
}

//
// Quaternion Transform
//

namespace vmath_hpp
{
    // qrotate

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(const mat<T, 3>& m) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/

        auto xyzw = T{0.5f} * sqrt(max(T{0}, vec{
            T{1} + m[0][0] - m[1][1] - m[2][2],
            T{1} - m[0][0] + m[1][1] - m[2][2],
            T{1} - m[0][0] - m[1][1] + m[2][2],
            T{1} + m[0][0] + m[1][1] + m[2][2]}));

        return qua(copysign(xyzw, {
            m[1][2] - m[2][1],
            m[2][0] - m[0][2],
            m[0][1] - m[1][0],
            T{1}}));
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(const qua<T>& q, const mat<T, 3>& m) {
        return q * qrotate(m);
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(const vec<T, 3>& from, const vec<T, 3>& to) {
        /// REFERENCE:
        /// http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final

        const T n = sqrt(length2(from) * length2(to));
        const T s = dot(from, to) + n;

        if ( s < T{0.000001f} * n ) {
            return abs(from.z) < abs(from.x)
                ? normalize(qua{vec{-from.y, from.x, T{0}}, T{0}})
                : normalize(qua{vec{T{0}, -from.z, from.y}, T{0}});
        }

        return normalize(qua{cross(from, to), s});
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(const qua<T>& q, const vec<T, 3>& from, const vec<T, 3>& to) {
        return q * qrotate(from, to);
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(T angle, const vec<T, 3>& axis) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T{0.5f});
        const auto [x, y, z] = normalize(axis);

        return {vec{x, y, z} * s, c};
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate(const qua<T>& q, T angle, const vec<T, 3>& axis) {
        return q * qrotate(angle, axis);
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_x(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T{0.5f});

        return {vec{s, T{0}, T{0}}, c};
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_x(const qua<T>& q, T angle) {
        return qrotate(q, angle, unit3_x<T>);
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_y(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T{0.5f});

        return {vec{T{0}, s, T{0}}, c};
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_y(const qua<T>& q, T angle) {
        return qrotate(q, angle, unit3_y<T>);
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_z(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T{0.5f});

        return {vec{T{0}, T{0}, s}, c};
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qrotate_z(const qua<T>& q, T angle) {
        return qrotate(q, angle, unit3_z<T>);
    }

    // look_at

    template < typename T >
    [[nodiscard]] constexpr qua<T> qlook_at_lh(const vec<T, 3>& dir, const vec<T, 3>& up) {
        return qrotate(look_at_lh(dir, up));
    }

    template < typename T >
    [[nodiscard]] constexpr qua<T> qlook_at_rh(const vec<T, 3>& dir, const vec<T, 3>& up) {
        return qrotate(look_at_rh(dir, up));
    }
}
