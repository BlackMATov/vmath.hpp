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
    template < typename T > inline constexpr vec<T, 2> zero2{0, 0};
    template < typename T > inline constexpr vec<T, 3> zero3{0, 0, 0};
    template < typename T > inline constexpr vec<T, 4> zero4{0, 0, 0, 0};

    template < typename T > inline constexpr vec<T, 2> unit2{1, 1};
    template < typename T > inline constexpr vec<T, 3> unit3{1, 1, 1};
    template < typename T > inline constexpr vec<T, 4> unit4{1, 1, 1, 1};

    template < typename T > inline constexpr vec<T, 2> unit2_x{1, 0};
    template < typename T > inline constexpr vec<T, 2> unit2_y{0, 1};

    template < typename T > inline constexpr vec<T, 3> unit3_x{1, 0, 0};
    template < typename T > inline constexpr vec<T, 3> unit3_y{0, 1, 0};
    template < typename T > inline constexpr vec<T, 3> unit3_z{0, 0, 1};

    template < typename T > inline constexpr vec<T, 4> unit4_x{1, 0, 0, 0};
    template < typename T > inline constexpr vec<T, 4> unit4_y{0, 1, 0, 0};
    template < typename T > inline constexpr vec<T, 4> unit4_z{0, 0, 1, 0};
    template < typename T > inline constexpr vec<T, 4> unit4_w{0, 0, 0, 1};

    template < typename T > inline constexpr mat<T, 2> zero2x2{0, 0, 0, 0};
    template < typename T > inline constexpr mat<T, 3> zero3x3{0, 0, 0, 0, 0, 0, 0, 0, 0};
    template < typename T > inline constexpr mat<T, 4> zero4x4{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    template < typename T > inline constexpr mat<T, 2> unit2x2{1, 1, 1, 1};
    template < typename T > inline constexpr mat<T, 3> unit3x3{1, 1, 1, 1, 1, 1, 1, 1, 1};
    template < typename T > inline constexpr mat<T, 4> unit4x4{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    template < typename T > inline constexpr mat<T, 2> identity2x2{1, 0, 0, 1};
    template < typename T > inline constexpr mat<T, 3> identity3x3{1, 0, 0, 0, 1, 0, 0, 0, 1};
    template < typename T > inline constexpr mat<T, 4> identity4x4{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
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
        return hash(vec{q});
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
        return detail::map_join([](From x){ return cast_to<To>(x); }, v);
    }

    template < typename To, typename From, std::size_t Size >
    [[nodiscard]] constexpr mat<To, Size> cast_to(const mat<From, Size>& m) {
        return detail::map_join([](const vec<From, Size>& v){ return cast_to<To>(v); }, m);
    }

    template < typename To, typename From >
    [[nodiscard]] constexpr qua<To> cast_to(const qua<From>& q) {
        return qua(cast_to<To>(vec{q}));
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
    [[nodiscard]] constexpr vec<T, Size> component(vec<T, Size> v, std::size_t index, T x) {
        v[index] = x;
        return v;
    }

    // row

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> row(const mat<T, Size>& m, std::size_t index) {
        return m.rows[index];
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> row(mat<T, Size> m, std::size_t index, const vec<T, Size>& v) {
        m.rows[index] = v;
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
        mat<T, Size> column_impl(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& v, std::index_sequence<Is...>) {
            return { component(m[Is], index, v[Is])... };
        }
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> column(const mat<T, Size>& m, std::size_t index) {
        return impl::column_impl(m, index, std::make_index_sequence<Size>{});
    }

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr mat<T, Size> column(const mat<T, Size>& m, std::size_t index, const vec<T, Size>& v) {
        return impl::column_impl(m, index, v, std::make_index_sequence<Size>{});
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
        return {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {x, y, z, 1}};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> translate(const vec<T, 3>& v) {
        return translate(v.x, v.y, v.z);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> translate(const mat<T, 4>& m, T x, T y, T z) {
        return m * translate(x, y, z);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> translate(const mat<T, 4>& m, const vec<T, 3>& v) {
        return m * translate(v);
    }

    // rotate

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate(const qua<T>& q) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/

        const auto [qv, qs] = normalize(q);

        const T xx = qv.x * qv.x;
        const T yy = qv.y * qv.y;
        const T zz = qv.z * qv.z;

        const T xy = qv.x * qv.y;
        const T xz = qv.x * qv.z;
        const T yz = qv.y * qv.z;

        const T xw = qv.x * qs;
        const T yw = qv.y * qs;
        const T zw = qv.z * qs;

        return {
            T(1) - (T(2) * (yy + zz)), T(2) * (xy + zw),          T(2) * (xz - yw),          0,
            T(2) * (xy - zw),          T(1) - (T(2) * (xx + zz)), T(2) * (yz + xw),          0,
            T(2) * (xz + yw),          T(2) * (yz - xw),          T(1) - (T(2) * (xx + yy)), 0,
            0,                         0,                         0,                         1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate(T angle, const vec<T, 3>& axis) {
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

        const T ic = T(1) - c;

        const T xxm = xx * ic;
        const T yym = yy * ic;
        const T zzm = zz * ic;

        const T xym = x * y * ic;
        const T xzm = x * z * ic;
        const T yzm = y * z * ic;

        return {
            xxm + c,  xym + zs, xzm - ys, 0,
            xym - zs, yym + c,  yzm + xs, 0,
            xzm + ys, yzm - xs, zzm + c,  0,
            0,        0,        0,        1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate(const mat<T, 4>& m, T angle, const vec<T, 3>& axis) {
        return m * rotate(angle, axis);
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate_x(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);
        return {
            1,  0, 0, 0,
            0,  c, s, 0,
            0, -s, c, 0,
            0,  0, 0, 1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate_x(const mat<T, 4>& m, T angle) {
        return m * rotate_x(angle);
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate_y(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);
        return {
            c, 0, -s, 0,
            0, 1,  0, 0,
            s, 0,  c, 0,
            0, 0,  0, 1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate_y(const mat<T, 4>& m, T angle) {
        return m * rotate_y(angle);
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate_z(T angle) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/algebra/matrix/orthogonal/rotation/

        const auto [s, c] = sincos(angle);
        return {
             c, s, 0, 0,
            -s, c, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> rotate_z(const mat<T, 4>& m, T angle) {
        return m * rotate_z(angle);
    }

    // scale

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> scale(T x, T y, T z) {
        return {
            {x, 0, 0, 0},
            {0, y, 0, 0},
            {0, 0, z, 0},
            {0, 0, 0, 1}};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> scale(const vec<T, 3>& v) {
        return scale(v.x, v.y, v.z);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> scale(const mat<T, 4>& m, T x, T y, T z) {
        return m * scale(x, y, z);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 4> scale(const mat<T, 4>& m, const vec<T, 3>& v) {
        return m * scale(v);
    }

    // look_at

    template < typename T >
    [[nodiscard]] mat<T, 4> look_at_lh(const vec<T, 3>& eye, const vec<T, 3>& at, const vec<T, 3>& up) {
        const vec az = normalize(at - eye);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        const T dx = dot(ax, eye);
        const T dy = dot(ay, eye);
        const T dz = dot(az, eye);

        return {
            ax.x, ay.x, az.x, 0,
            ax.y, ay.y, az.y, 0,
            ax.z, ay.z, az.z, 0,
            -dx,  -dy,  -dz,  1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> look_at_rh(const vec<T, 3>& eye, const vec<T, 3>& at, const vec<T, 3>& up) {
        const vec az = normalize(eye - at);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        const T dx = dot(ax, eye);
        const T dy = dot(ay, eye);
        const T dz = dot(az, eye);

        return {
            ax.x, ay.x, az.x, 0,
            ax.y, ay.y, az.y, 0,
            ax.z, ay.z, az.z, 0,
            -dx,  -dy,  -dz,  1};
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
        return {
            {1, 0, 0},
            {0, 1, 0},
            {x, y, 1}};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> translate(const vec<T, 2>& v) {
        return translate(v.x, v.y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> translate(const mat<T, 3>& m, T x, T y) {
        return m * translate(x, y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> translate(const mat<T, 3>& m, const vec<T, 2>& v) {
        return m * translate(v);
    }

    // rotate

    template < typename T >
    [[nodiscard]] mat<T, 3> rotate(T angle) {
        const auto [s, c] = sincos(angle);
        return {
             c, s, 0,
            -s, c, 0,
             0, 0, 1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 3> rotate(const mat<T, 3>& m, T angle) {
        return m * rotate(angle);
    }

    // scale

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(T x, T y) {
        return {
            {x, 0, 0},
            {0, y, 0},
            {0, 0, 1}};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(const vec<T, 2>& v) {
        return scale(v.x, v.y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(const mat<T, 3>& m, T x, T y) {
        return m * scale(x, y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> scale(const mat<T, 3>& m, const vec<T, 2>& v) {
        return m * scale(v);
    }

    // shear

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear(T x, T y) {
        return {
            {1, y, 0},
            {x, 1, 0},
            {0, 0, 1}};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear(const vec<T, 2>& v) {
        return shear(v.x, v.y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear(const mat<T, 3>& m, T x, T y) {
        return m * shear(x, y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear(const mat<T, 3>& m, const vec<T, 2>& v) {
        return m * shear(v);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear_x(T y) {
        return {
            {1, 0, 0},
            {y, 1, 0},
            {0, 0, 1}};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear_x(const mat<T, 3>& m, T y) {
        return m * shear_x(y);
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear_y(T x) {
        return {
            {1, x, 0},
            {0, 1, 0},
            {0, 0, 1}};
    }

    template < typename T >
    [[nodiscard]] constexpr mat<T, 3> shear_y(const mat<T, 3>& m, T x) {
        return m * shear_y(x);
    }
}

//
// Matrix Projections
//

namespace vmath_hpp
{
    // orthographic

    template < typename T >
    [[nodiscard]] mat<T, 4> orthographic_lh_zo(T left, T right, T bottom, T top, T znear, T zfar) {
        const T sx = T(2) * rcp(right - left);
        const T sy = T(2) * rcp(top - bottom);
        const T sz = T(1) * rcp(zfar - znear);

        const T tx = - (right + left) / (right - left);
        const T ty = - (top + bottom) / (top - bottom);
        const T tz = - znear / (zfar - znear);

        return {
            sx, 0,  0,  0,
            0,  sy, 0,  0,
            0,  0,  sz, 0,
            tx, ty, tz, 1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> orthographic_lh_no(T left, T right, T bottom, T top, T znear, T zfar) {
        const T sx = T(2) * rcp(right - left);
        const T sy = T(2) * rcp(top - bottom);
        const T sz = T(2) * rcp(zfar - znear);

        const T tx = - (right + left) / (right - left);
        const T ty = - (top + bottom) / (top - bottom);
        const T tz = - (zfar + znear) / (zfar - znear);

        return {
            sx, 0,  0,  0,
            0,  sy, 0,  0,
            0,  0,  sz, 0,
            tx, ty, tz, 1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> orthographic_rh_zo(T left, T right, T bottom, T top, T znear, T zfar) {
        const T sx = T(2) * rcp(right - left);
        const T sy = T(2) * rcp(top - bottom);
        const T sz = -T(1) * rcp(zfar - znear);

        const T tx = - (right + left) / (right - left);
        const T ty = - (top + bottom) / (top - bottom);
        const T tz = - znear / (zfar - znear);

        return {
            sx, 0,  0,  0,
            0,  sy, 0,  0,
            0,  0,  sz, 0,
            tx, ty, tz, 1};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> orthographic_rh_no(T left, T right, T bottom, T top, T znear, T zfar) {
        const T sx = T(2) * rcp(right - left);
        const T sy = T(2) * rcp(top - bottom);
        const T sz = -T(2) * rcp(zfar - znear);

        const T tx = - (right + left) / (right - left);
        const T ty = - (top + bottom) / (top - bottom);
        const T tz = - (zfar + znear) / (zfar - znear);

        return {
            sx, 0,  0,  0,
            0,  sy, 0,  0,
            0,  0,  sz, 0,
            tx, ty, tz, 1};
    }

    // perspective

    template < typename T >
    [[nodiscard]] mat<T, 4> perspective_lh_zo(T fov, T aspect, T znear, T zfar) {
        const T sy = rcp(tan(fov * T(0.5)));
        const T sx = sy / aspect;
        const T sz = zfar / (zfar - znear);
        const T tz = (znear * zfar) / (znear - zfar);
        return {
            sx, 0,  0,  0,
            0,  sy, 0,  0,
            0,  0,  sz, 1,
            0,  0,  tz, 0};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> perspective_lh_no(T fov, T aspect, T znear, T zfar) {
        const T sy = rcp(tan(fov * T(0.5)));
        const T sx = sy / aspect;
        const T sz = (zfar + znear) / (zfar - znear);
        const T tz = (T(2) * znear * zfar) / (znear - zfar);
        return {
            sx, 0,  0,  0,
            0,  sy, 0,  0,
            0,  0,  sz, 1,
            0,  0,  tz, 0};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> perspective_rh_zo(T fov, T aspect, T znear, T zfar) {
        const T sy = rcp(tan(fov * T(0.5)));
        const T sx = sy / aspect;
        const T sz = zfar / (znear - zfar);
        const T tz = (znear * zfar) / (znear - zfar);
        return  {
            sx, 0,  0,   0,
            0,  sy, 0,   0,
            0,  0,  sz, -1,
            0,  0,  tz,  0};
    }

    template < typename T >
    [[nodiscard]] mat<T, 4> perspective_rh_no(T fov, T aspect, T znear, T zfar) {
        const T sy = rcp(tan(fov * T(0.5)));
        const T sx = sy / aspect;
        const T sz = (zfar + znear) / (znear - zfar);
        const T tz = (T(2) * znear * zfar) / (znear - zfar);
        return  {
            sx, 0,  0,   0,
            0,  sy, 0,   0,
            0,  0,  sz, -1,
            0,  0,  tz,  0};
    }
}

//
// Vector Transform
//

namespace vmath_hpp
{
    // angle

    template < typename T, std::size_t Size >
    [[nodiscard]] T angle(const vec<T, Size>& x, const vec<T, Size>& y) {
        return acos(dot(x, y) * rsqrt(length2(x) * length2(y)));
    }

    // rotate

    template < typename T >
    [[nodiscard]] vec<T, 2> rotate(const vec<T, 2>& v, T angle) {
        const auto [s, c] = sincos(angle);
        return {
            v.x * c - v.y * s,
            v.x * s + v.y * c};
    }

    template < typename T >
    [[nodiscard]] vec<T, 3> rotate_x(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_x<T>);
    }

    template < typename T >
    [[nodiscard]] vec<T, 3> rotate_y(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_y<T>);
    }

    template < typename T >
    [[nodiscard]] vec<T, 3> rotate_z(const vec<T, 3>& v, T angle) {
        return v * qrotate(angle, unit3_z<T>);
    }

    template < typename T >
    [[nodiscard]] vec<T, 3> rotate(const vec<T, 3>& v, const qua<T>& q) {
        return v * q;
    }

    template < typename T >
    [[nodiscard]] vec<T, 3> rotate(const vec<T, 3>& v, T angle, const vec<T, 3>& axis) {
        return v * qrotate(angle, axis);
    }

    template < typename T >
    [[nodiscard]] vec<T, 4> rotate_x(const vec<T, 4>& v, T angle) {
        return v * qrotate(angle, unit3_x<T>);
    }

    template < typename T >
    [[nodiscard]] vec<T, 4> rotate_y(const vec<T, 4>& v, T angle) {
        return v * qrotate(angle, unit3_y<T>);
    }

    template < typename T >
    [[nodiscard]] vec<T, 4> rotate_z(const vec<T, 4>& v, T angle) {
        return v * qrotate(angle, unit3_z<T>);
    }

    template < typename T >
    [[nodiscard]] vec<T, 4> rotate(const vec<T, 4>& v, const qua<T>& q) {
        return v * q;
    }

    template < typename T >
    [[nodiscard]] vec<T, 4> rotate(const vec<T, 4>& v, T angle, const vec<T, 3>& axis) {
        return v * qrotate(angle, axis);
    }

    // project

    template < typename T, std::size_t Size >
    [[nodiscard]] constexpr vec<T, Size> project(const vec<T, Size>& v, const vec<T, Size>& normal) {
        return dot(v, normal) / dot(normal, normal) * normal;
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
    [[nodiscard]] qua<T> qrotate(const mat<T, 3>& m) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/

        const T wv = m[0][0] + m[1][1] + m[2][2];
        const T xv = m[0][0] - m[1][1] - m[2][2];
        const T yv = m[1][1] - m[0][0] - m[2][2];
        const T zv = m[2][2] - m[0][0] - m[1][1];

        struct pmv {
            const T v{};
            const int i{};
        };

        const auto [mv,mi] = max<pmv>({
            {wv, 0},
            {xv, 1},
            {yv, 2},
            {zv, 3},
        }, [](auto&& l, auto&& r){
            return l.v < r.v;
        });

        const T qv = T(0.5) * sqrt(T(1) + mv);
        const T rqv = T(0.25) * rcp(qv);

        switch ( mi ) {
        default:
        case 0:
            return {
                (m[1][2] - m[2][1]) * rqv,
                (m[2][0] - m[0][2]) * rqv,
                (m[0][1] - m[1][0]) * rqv,
                qv};
        case 1:
            return {
                qv,
                (m[1][0] + m[0][1]) * rqv,
                (m[2][0] + m[0][2]) * rqv,
                (m[1][2] - m[2][1]) * rqv};
        case 2:
            return {
                (m[1][0] + m[0][1]) * rqv,
                qv,
                (m[2][1] + m[1][2]) * rqv,
                (m[2][0] - m[0][2]) * rqv};
        case 3:
            return {
                (m[2][0] + m[0][2]) * rqv,
                (m[2][1] + m[1][2]) * rqv,
                qv,
                (m[0][1] - m[1][0]) * rqv};
        }
    }

    template < typename T >
    [[nodiscard]] qua<T> qrotate(T angle, const vec<T, 3>& axis) {
        /// REFERENCE:
        /// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

        const auto [s, c] = sincos(angle * T(0.5));
        const auto [x, y, z] = normalize(axis);
        return {vec{x,y,z} * s, c};
    }

    template < typename T >
    [[nodiscard]] qua<T> qrotate(const qua<T>& q, T angle, const vec<T, 3>& axis) {
        return q * qrotate(angle, axis);
    }

    template < typename T >
    [[nodiscard]] qua<T> qrotate_x(T angle) {
        const auto [s, c] = sincos(angle * T(0.5));
        return {s, T(0), T(0), c};
    }

    template < typename T >
    [[nodiscard]] qua<T> qrotate_x(const qua<T>& q, T angle) {
        return qrotate(q, angle, unit3_x<T>);
    }

    template < typename T >
    [[nodiscard]] qua<T> qrotate_y(T angle) {
        const auto [s, c] = sincos(angle * T(0.5));
        return {T(0), s, T(0), c};
    }

    template < typename T >
    [[nodiscard]] qua<T> qrotate_y(const qua<T>& q, T angle) {
        return qrotate(q, angle, unit3_y<T>);
    }

    template < typename T >
    [[nodiscard]] qua<T> qrotate_z(T angle) {
        const auto [s, c] = sincos(angle * T(0.5));
        return {T(0), T(0), s, c};
    }

    template < typename T >
    [[nodiscard]] qua<T> qrotate_z(const qua<T>& q, T angle) {
        return qrotate(q, angle, unit3_z<T>);
    }

    // look_at

    template < typename T >
    [[nodiscard]] qua<T> qlook_at_lh(const vec<T, 3>& dir, const vec<T, 3>& up) {
        const vec az = normalize(dir);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        return qrotate(mat{
            ax.x, ay.x, az.x,
            ax.y, ay.y, az.y,
            ax.z, ay.z, az.z});
    }

    template < typename T >
    [[nodiscard]] qua<T> qlook_at_rh(const vec<T, 3>& dir, const vec<T, 3>& up) {
        const vec az = normalize(-dir);
        const vec ax = normalize(cross(up, az));
        const vec ay = cross(az, ax);

        return qrotate(mat{
            ax.x, ay.x, az.x,
            ax.y, ay.y, az.y,
            ax.z, ay.z, az.z});
    }
}
