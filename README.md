# vmath.hpp

> C++17 tiny vector math library

[![travis][badge.travis]][travis]
[![appveyor][badge.appveyor]][appveyor]
[![codecov][badge.codecov]][codecov]
[![language][badge.language]][language]
[![license][badge.license]][license]
[![paypal][badge.paypal]][paypal]

[badge.travis]: https://img.shields.io/travis/BlackMATov/vmath.hpp/main.svg?logo=travis
[badge.appveyor]: https://img.shields.io/appveyor/ci/BlackMATov/vmath-hpp/main.svg?logo=appveyor
[badge.codecov]: https://img.shields.io/codecov/c/github/BlackMATov/vmath.hpp/main.svg?logo=codecov
[badge.language]: https://img.shields.io/badge/language-C%2B%2B17-yellow.svg
[badge.license]: https://img.shields.io/badge/license-MIT-blue.svg
[badge.paypal]: https://img.shields.io/badge/donate-PayPal-orange.svg?logo=paypal&colorA=00457C

[travis]: https://travis-ci.org/BlackMATov/vmath.hpp
[appveyor]: https://ci.appveyor.com/project/BlackMATov/vmath-hpp
[codecov]: https://codecov.io/gh/BlackMATov/vmath.hpp
[language]: https://en.wikipedia.org/wiki/C%2B%2B17
[license]: https://en.wikipedia.org/wiki/MIT_License
[paypal]: https://www.paypal.me/matov

[vmath]: https://github.com/BlackMATov/vmath.hpp

## Requirements

- [gcc](https://www.gnu.org/software/gcc/) **>= 7**
- [clang](https://clang.llvm.org/) **>= 5.0**
- [msvc](https://visualstudio.microsoft.com/) **>= 2017**

## Installation

[vmath.hpp][vmath] is a header-only library. All you need to do is copy the headers files from `headers` directory into your project and include them:

```cpp
#include "vmath.hpp/vmath.hpp"
```

Also, you can add the root repository directory to your [cmake](https://cmake.org) project:

```cmake
add_subdirectory(external/vmath.hpp)
target_link_libraries(your_project_target vmath.hpp)
```

## Disclaimer

The [vmath.hpp][vmath] is a tiny vector math library mainly for games, game engines, and other graphics software. It will never be mathematically strict (e.g. the vector class has operator plus for adding scalars to a vector, which is convenient for developing CG applications but makes no sense in "real" math). For the same reason, the library does not provide flexible vector and matrix sizes. The library functions follow the same principles.

Most functions and types are based on the HLSL ([High-Level Shading Language for DirectX](https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl)) specification. Matrices are row-major, which implies that vector, matrix multiplication is: v * M, not M * v.

## API

- [Vector Types](#Vector-Types)
- [Matrix Types](#Matrix-Types)
- [Vector Operators](#Vector-Operators)
- [Matrix Operators](#Matrix-Operators)
- [Angle and Trigonometry Functions](#Angle-and-Trigonometry-Functions)
- [Exponential Functions](#Exponential-Functions)
- [Common Functions](#Common-Functions)
- [Geometric Functions](#Geometric-Functions)
- [Relational Functions](#Relational-Functions)
- [Matrix Functions](#Matrix-Functions)
- [Units](#Units)
- [Cast](#Cast)
- [Access](#Access)
- [Matrix Transform 3D](#Matrix-Transform-3D)
- [Matrix Transform 2D](#Matrix-Transform-2D)
- [Matrix Projections](#Matrix-Projections)
- [Vector Transform](#Vector-Transform)

### Vector Types

```cpp
template < typename T, size_t Size >
class vec_base;

template < typename T >
class vec_base<T, 2> {
public:
    T x{}, y{};

    constexpr vec_base() = default;
    constexpr explicit vec_base(T v);
    constexpr vec_base(T x, T y);
    constexpr explicit vec_base(const vec_base<T, 3>& xy);
    constexpr explicit vec_base(const vec_base<T, 4>& xy);
};

template < typename T >
class vec_base<T, 3> {
public:
    T x{}, y{}, z{};

    constexpr vec_base() = default;
    constexpr explicit vec_base(T v);
    constexpr vec_base(T x, T y, T z);
    constexpr vec_base(const vec_base<T, 2>& xy, T z);
    constexpr vec_base(T x, const vec_base<T, 2>& yz);
    constexpr explicit vec_base(const vec_base<T, 4>& xyz);
};

template < typename T >
class vec_base<T, 4> {
public:
    T x{}, y{}, z{}, w{};

    constexpr vec_base() = default;
    constexpr explicit vec_base(T v);
    constexpr vec_base(T x, T y, T z, T w);
    constexpr vec_base(const vec_base<T, 2>& xy, T z, T w);
    constexpr vec_base(T x, const vec_base<T, 2>& yz, T w);
    constexpr vec_base(T x, T y, const vec_base<T, 2>& zw);
    constexpr vec_base(const vec_base<T, 2>& xy, const vec_base<T, 2>& zw);
    constexpr vec_base(const vec_base<T, 3>& xyz, T w);
    constexpr vec_base(T x, const vec_base<T, 3>& yzw);
};

template < typename T, size_t Size >
class vec final : public vec_base<T, Size> {
public:
    using component_type = T;

    using pointer = component_type*;
    using const_pointer = const component_type*;

    using reference = component_type&;
    using const_reference = const component_type&;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr size_t size = Size;

    void swap(vec& other) noexcept(is_nothrow_swappable_v<T>);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    pointer data() noexcept;
    const_pointer data() const noexcept;

    constexpr reference at(size_t index);
    constexpr const_reference at(size_t index) const;

    constexpr reference operator[](size_t index) noexcept;
    constexpr const_reference operator[](size_t index) const noexcept;
};

using bool2 = vec<bool, 2>;
using bool3 = vec<bool, 3>;
using bool4 = vec<bool, 4>;

using int2 = vec<int, 2>;
using int3 = vec<int, 3>;
using int4 = vec<int, 4>;

using uint2 = vec<unsigned, 2>;
using uint3 = vec<unsigned, 3>;
using uint4 = vec<unsigned, 4>;

using float2 = vec<float, 2>;
using float3 = vec<float, 3>;
using float4 = vec<float, 4>;

using double2 = vec<double, 2>;
using double3 = vec<double, 3>;
using double4 = vec<double, 4>;

using size2 = vec<size_t, 2>;
using size3 = vec<size_t, 3>;
using size4 = vec<size_t, 4>;

using ptrdiff2 = vec<std::ptrdiff_t, 2>;
using ptrdiff3 = vec<std::ptrdiff_t, 3>;
using ptrdiff4 = vec<std::ptrdiff_t, 4>;
```

### Matrix Types

```cpp
template < typename T, size_t Size >
class mat_base;

template < typename T >
class mat_base<T, 2> {
public:
    using row_type = vec<T, 2>;

    row_type rows[2] = {
        {1, 0},
        {0, 1}};

    constexpr mat_base() = default;
    constexpr explicit mat_base(T d);
    constexpr explicit mat_base(const row_type& d);

    constexpr mat_base(
        T m11, T m12,
        T m21, T m22);

    constexpr mat_base(
        const row_type& row0,
        const row_type& row1);

    constexpr explicit mat_base(const mat_base<T, 3>& other);
    constexpr explicit mat_base(const mat_base<T, 4>& other);
};

template < typename T >
class mat_base<T, 3> {
public:
    using row_type = vec<T, 3>;

    row_type rows[3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};

    constexpr mat_base() = default;
    constexpr explicit mat_base(T d);
    constexpr explicit mat_base(const row_type& d);

    constexpr mat_base(
        T m11, T m12, T m13,
        T m21, T m22, T m23,
        T m31, T m32, T m33);

    constexpr mat_base(
        const row_type& row0,
        const row_type& row1,
        const row_type& row2);

    constexpr mat_base(
        const mat_base<T, 2>& m,
        const vec_base<T, 2>& v);

    constexpr explicit mat_base(const mat_base<T, 2>& other);
    constexpr explicit mat_base(const mat_base<T, 4>& other);
};

template < typename T >
class mat_base<T, 4> {
public:
    using row_type = vec<T, 4>;

    row_type rows[4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};

    constexpr mat_base() = default;
    constexpr explicit mat_base(T d);
    constexpr explicit mat_base(const row_type& d);

    constexpr mat_base(
        T m11, T m12, T m13, T m14,
        T m21, T m22, T m23, T m24,
        T m31, T m32, T m33, T m34,
        T m41, T m42, T m43, T m44);

    constexpr mat_base(
        const row_type& row0,
        const row_type& row1,
        const row_type& row2,
        const row_type& row3);

    constexpr mat_base(
        const mat_base<T, 3>& m,
        const vec_base<T, 3>& v);

    constexpr explicit mat_base(const mat_base<T, 2>& other);
    constexpr explicit mat_base(const mat_base<T, 3>& other);
};

template < typename T, size_t Size >
class mat final : public mat_base<T, Size> {
public:
    using row_type = vec<T, Size>;

    using pointer = row_type*;
    using const_pointer = const row_type*;

    using reference = row_type&;
    using const_reference = const row_type&;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr size_t size = Size;

    void swap(mat& other) noexcept(is_nothrow_swappable_v<T>);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    pointer data() noexcept;
    const_pointer data() const noexcept;

    constexpr reference at(size_t index);
    constexpr const_reference at(size_t index) const;

    constexpr reference operator[](size_t index) noexcept;
    constexpr const_reference operator[](size_t index) const noexcept;
};

using bool2x2 = mat<bool, 2>;
using bool3x3 = mat<bool, 3>;
using bool4x4 = mat<bool, 4>;

using int2x2 = mat<int, 2>;
using int3x3 = mat<int, 3>;
using int4x4 = mat<int, 4>;

using uint2x2 = mat<unsigned, 2>;
using uint3x3 = mat<unsigned, 3>;
using uint4x4 = mat<unsigned, 4>;

using float2x2 = mat<float, 2>;
using float3x3 = mat<float, 3>;
using float4x4 = mat<float, 4>;

using double2x2 = mat<double, 2>;
using double3x3 = mat<double, 3>;
using double4x4 = mat<double, 4>;

using size2x2 = mat<size_t, 2>;
using size3x3 = mat<size_t, 3>;
using size4x4 = mat<size_t, 4>;

using ptrdiff2x2 = mat<std::ptrdiff_t, 2>;
using ptrdiff3x3 = mat<std::ptrdiff_t, 3>;
using ptrdiff4x4 = mat<std::ptrdiff_t, 4>;
```

### Vector Operators

```cpp
// -operator

template < typename T, size_t Size >
constexpr vec<T, Size> operator-(const vec<T, Size>& xs);

// operator+

template < typename T, size_t Size >
constexpr vec<T, Size> operator+(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size> operator+(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<T, Size> operator+(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator+=

template < typename T, size_t Size >
constexpr vec<T, Size>& operator+=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size>& operator+=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator-

template < typename T, size_t Size >
constexpr vec<T, Size> operator-(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size> operator-(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<T, Size> operator-(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator-=

template < typename T, size_t Size >
constexpr vec<T, Size>& operator-=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size>& operator-=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator*

template < typename T, size_t Size >
constexpr vec<T, Size> operator*(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size> operator*(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<T, Size> operator*(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator*=

template < typename T, size_t Size >
constexpr vec<T, Size>& operator*=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size>& operator*=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator/

template < typename T, size_t Size >
constexpr vec<T, Size> operator/(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size> operator/(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<T, Size> operator/(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator/=

template < typename T, size_t Size >
constexpr vec<T, Size>& operator/=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size>& operator/=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator==

template < typename T, size_t Size >
constexpr bool operator==(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr bool operator!=(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator<

template < typename T, size_t Size >
constexpr bool operator<(const vec<T, Size>& xs, const vec<T, Size>& ys);
```

### Matrix Operators

```cpp
// -operator

template < typename T, size_t Size >
constexpr mat<T, Size> operator-(const mat<T, Size>& xs);

// operator+

template < typename T, size_t Size >
constexpr mat<T, Size> operator+(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr mat<T, Size> operator+(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
constexpr mat<T, Size> operator+(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator+=

template < typename T, size_t Size >
constexpr mat<T, Size>& operator+=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr mat<T, Size>& operator+=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator-

template < typename T, size_t Size >
constexpr mat<T, Size> operator-(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr mat<T, Size> operator-(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
constexpr mat<T, Size> operator-(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator-=

template < typename T, size_t Size >
constexpr mat<T, Size>& operator-=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr mat<T, Size>& operator-=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator*

template < typename T, size_t Size >
constexpr mat<T, Size> operator*(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr mat<T, Size> operator*(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<T, Size> operator*(const vec<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size >
constexpr mat<T, Size> operator*(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator*=

template < typename T, size_t Size >
constexpr mat<T, Size>& operator*=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size>& operator*=(vec<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size >
constexpr mat<T, Size>& operator*=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator/

template < typename T, size_t Size >
constexpr mat<T, Size> operator/(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr mat<T, Size> operator/(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
constexpr mat<T, Size> operator/(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator/=

template < typename T, size_t Size >
constexpr mat<T, Size>& operator/=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr mat<T, Size>& operator/=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator==

template < typename T, size_t Size >
constexpr bool operator==(const mat<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size >
constexpr bool operator!=(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator<

template < typename T, size_t Size >
constexpr bool operator<(const mat<T, Size>& xs, const mat<T, Size>& ys);
```

### Angle and Trigonometry Functions

```cpp
// Scalar

template < floating_point T >
constexpr T radians(T degrees) noexcept;

template < floating_point T >
constexpr T degrees(T radians) noexcept;

template < floating_point T >
T sin(T x) noexcept;

template < floating_point T >
T cos(T x) noexcept;

template < floating_point T >
T tan(T x) noexcept;

template < floating_point T >
T asin(T x) noexcept;

template < floating_point T >
T acos(T x) noexcept;

template < floating_point T >
T atan(T x) noexcept;

template < floating_point T >
T atan2(T y, T x) noexcept;

template < floating_point T >
T sinh(T x) noexcept;

template < floating_point T >
T cosh(T x) noexcept;

template < floating_point T >
T tanh(T x) noexcept;

template < floating_point T >
T asinh(T x) noexcept;

template < floating_point T >
T acosh(T x) noexcept;

template < floating_point T >
T atanh(T x) noexcept;

// Vector

template < typename T, size_t Size >
constexpr vec<T, Size> radians(const vec<T, Size>& degrees);

template < typename T, size_t Size >
constexpr vec<T, Size> degrees(const vec<T, Size>& radians);

template < typename T, size_t Size >
vec<T, Size> sin(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> cos(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> tan(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> asin(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> acos(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> atan(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> atan2(const vec<T, Size>& ys, const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> sinh(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> cosh(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> tanh(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> asinh(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> acosh(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> atanh(const vec<T, Size>& xs);
```

### Exponential Functions

```cpp
// Scalar

template < floating_point T >
T pow(T x, T y) noexcept;

template < floating_point T >
T exp(T x) noexcept;

template < floating_point T >
T log(T x) noexcept;

template < floating_point T >
T exp2(T x) noexcept;

template < floating_point T >
T log2(T x) noexcept;

template < floating_point T >
T sqrt(T x) noexcept;

template < floating_point T >
T rsqrt(T x) noexcept;

// Vector

template < typename T, size_t Size >
vec<T, Size> pow(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
vec<T, Size> exp(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> log(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> exp2(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> log2(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> sqrt(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> rsqrt(const vec<T, Size>& xs);
```

### Common Functions

```cpp
// Scalar

template < arithmetic T >
constexpr T abs(T x) noexcept;

template < arithmetic T >
constexpr T sign(T x) noexcept;

template < floating_point T >
constexpr T reciprocal(T x) noexcept;

template < floating_point T >
T floor(T x) noexcept;

template < floating_point T >
T trunc(T x) noexcept;

template < floating_point T >
T round(T x) noexcept;

template < floating_point T >
T ceil(T x) noexcept;

template < floating_point T >
T fract(T x) noexcept;

template < floating_point T >
T fmod(T x, T y) noexcept;

template < floating_point T >
T modf(T x, T* y) noexcept;

template < arithmetic T >
constexpr T min(T x, T y) noexcept;

template < arithmetic T >
constexpr T max(T x, T y) noexcept;

template < arithmetic T >
constexpr T clamp(T x, T min_x, T max_x) noexcept;

template < arithmetic T >
constexpr T saturate(T x) noexcept;

template < floating_point T >
constexpr T lerp(T x, T y, T a) noexcept;

template < floating_point T >
constexpr T step(T edge, T x) noexcept;

template < floating_point T >
constexpr T smoothstep(T edge0, T edge1, T x) noexcept;

template < arithmetic T >
bool isnan(T x) noexcept;

template < arithmetic T >
bool isinf(T x) noexcept;

template < arithmetic T >
bool isfinite(T x) noexcept;

template < floating_point T >
T fma(T x, T y, T z) noexcept;

template < floating_point T >
T frexp(T x, int* exp) noexcept;

template < floating_point T >
T ldexp(T x, int exp) noexcept;

// Vector

template < typename T, size_t Size >
constexpr vec<T, Size> abs(const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> sign(const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> reciprocal(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> floor(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> trunc(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> round(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> ceil(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> fract(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> fmod(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size> fmod(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
vec<T, Size> modf(const vec<T, Size>& xs, vec<T, Size>* is);

template < typename T, size_t Size >
constexpr T min(const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> min(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size> min(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr T max(const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> max(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
constexpr vec<T, Size> max(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<T, Size> clamp(const vec<T, Size>& xs, T min_x, T max_x);

template < typename T, size_t Size >
constexpr vec<T, Size> clamp(const vec<T, Size>& xs, const vec<T, Size>& min_xs, const vec<T, Size>& max_xs);

template < typename T, size_t Size >
constexpr vec<T, Size> saturate(const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> lerp(const vec<T, Size>& xs, const vec<T, Size>& ys, T a);

template < typename T, size_t Size >
constexpr vec<T, Size> lerp(const vec<T, Size>& xs, const vec<T, Size>& ys, const vec<T, Size>& as);

template < typename T, size_t Size >
constexpr vec<T, Size> step(T edge, const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> step(const vec<T, Size>& edges, const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> smoothstep(T edge0, T edge1, const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> smoothstep(const vec<T, Size>& edges0, const vec<T, Size>& edges1, const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<bool, Size> isnan(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<bool, Size> isinf(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<bool, Size> isfinite(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> fma(const vec<T, Size>& as, const vec<T, Size>& bs, const vec<T, Size>& cs);

template < typename T, size_t Size >
vec<T, Size> frexp(const vec<T, Size>& xs, vec<int, Size>* exps);

template < typename T, size_t Size >
vec<T, Size> ldexp(const vec<T, Size>& xs, const vec<int, Size>& exps);
```

### Geometric Functions

```cpp
// Scalar

template < arithmetic T >
constexpr T dot(T x, T y) noexcept;

template < arithmetic T >
constexpr T length(T x) noexcept;

template < arithmetic T >
constexpr T length2(T x) noexcept;

template < arithmetic T >
constexpr T distance(T x, T y) noexcept;

template < arithmetic T >
constexpr T distance2(T x, T y) noexcept;

template < floating_point T >
T normalize(T x) noexcept;

template < floating_point T >
constexpr T faceforward(T n, T i, T nref) noexcept;

template < floating_point T >
constexpr T reflect(T i, T n) noexcept;

template < floating_point T >
T refract(T i, T n, T eta) noexcept;

// Vector

template < typename T, size_t Size >
constexpr T dot(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
T length(const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr T length2(const vec<T, Size>& xs);

template < typename T, size_t Size >
T distance(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr T distance2(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T >
constexpr T cross(const vec<T, 2>& xs, const vec<T, 2>& ys);

template < typename T >
constexpr vec<T, 3> cross(const vec<T, 3>& xs, const vec<T, 3>& ys);

template < typename T, size_t Size >
vec<T, Size> normalize(const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr vec<T, Size> faceforward(const vec<T, Size>& n, const vec<T, Size>& i, const vec<T, Size>& nref);

template < typename T, size_t Size >
constexpr vec<T, Size> reflect(const vec<T, Size>& i, const vec<T, Size>& n);

template < typename T, size_t Size >
vec<T, Size> refract(const vec<T, Size>& i, const vec<T, Size>& n, T eta);
```

### Relational Functions

```cpp
// Scalar

template < arithmetic T >
constexpr bool less(T x, T y) noexcept;

template < arithmetic T >
constexpr bool less_equal(T x, T y) noexcept;

template < arithmetic T >
constexpr bool greater(T x, T y) noexcept;

template < arithmetic T >
constexpr bool greater_equal(T x, T y) noexcept;

template < arithmetic T >
constexpr bool equal_to(T x, T y) noexcept;

template < arithmetic T >
constexpr bool equal_to(T x, T y, T epsilon) noexcept;

template < arithmetic T >
constexpr bool not_equal_to(T x, T y) noexcept;

template < arithmetic T >
constexpr bool not_equal_to(T x, T y, T epsilon) noexcept;

template < arithmetic T >
constexpr bool any(T x) noexcept;

template < arithmetic T >
constexpr bool all(T x) noexcept;

// Vector

template < typename T, size_t Size >
constexpr vec<bool, Size> less(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<bool, Size> less_equal(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<bool, Size> greater(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<bool, Size> greater_equal(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<bool, Size> equal_to(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<bool, Size> equal_to(const vec<T, Size>& xs, const vec<T, Size>& ys, T epsilon);

template < typename T, size_t Size >
constexpr vec<bool, Size> not_equal_to(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
constexpr vec<bool, Size> not_equal_to(const vec<T, Size>& xs, const vec<T, Size>& ys, T epsilon);

template < typename T, size_t Size >
constexpr bool any(const vec<T, Size>& xs);

template < typename T, size_t Size >
constexpr bool all(const vec<T, Size>& xs);
```

### Matrix Functions

```cpp
template < typename T >
constexpr mat<T, 2> transpose(const mat<T, 2>& m);

template < typename T >
constexpr mat<T, 3> transpose(const mat<T, 3>& m);

template < typename T >
constexpr mat<T, 4> transpose(const mat<T, 4>& m);

template < typename T >
constexpr T determinant(const mat<T, 2>& m);

template < typename T >
constexpr T determinant(const mat<T, 3>& m);

template < typename T >
constexpr T determinant(const mat<T, 4>& m);

template < typename T >
constexpr mat<T, 2> inverse(const mat<T, 2>& m);

template < typename T >
constexpr mat<T, 3> inverse(const mat<T, 3>& m);

template < typename T >
constexpr mat<T, 4> inverse(const mat<T, 4>& m);
```

### Units

```cpp
template < typename T > inline constexpr vec<T, 2> zero2;
template < typename T > inline constexpr vec<T, 3> zero3;
template < typename T > inline constexpr vec<T, 4> zero4;

template < typename T > inline constexpr vec<T, 2> unit2;
template < typename T > inline constexpr vec<T, 3> unit3;
template < typename T > inline constexpr vec<T, 4> unit4;

template < typename T > inline constexpr vec<T, 2> unit2_x;
template < typename T > inline constexpr vec<T, 2> unit2_y;

template < typename T > inline constexpr vec<T, 3> unit3_x;
template < typename T > inline constexpr vec<T, 3> unit3_y;
template < typename T > inline constexpr vec<T, 3> unit3_z;

template < typename T > inline constexpr vec<T, 4> unit4_x;
template < typename T > inline constexpr vec<T, 4> unit4_y;
template < typename T > inline constexpr vec<T, 4> unit4_z;
template < typename T > inline constexpr vec<T, 4> unit4_w;

template < typename T > inline constexpr mat<T, 2> zero2x2;
template < typename T > inline constexpr mat<T, 3> zero3x3;
template < typename T > inline constexpr mat<T, 4> zero4x4;

template < typename T > inline constexpr mat<T, 2> unit2x2;
template < typename T > inline constexpr mat<T, 3> unit3x3;
template < typename T > inline constexpr mat<T, 4> unit4x4;

template < typename T > inline constexpr mat<T, 2> identity2x2;
template < typename T > inline constexpr mat<T, 3> identity3x3;
template < typename T > inline constexpr mat<T, 4> identity4x4;
```

### Cast

```cpp
template < arithmetic To, arithmetic From >
constexpr To cast_to(From x) noexcept;

template < typename To, typename From, size_t Size >
constexpr vec<To, Size> cast_to(const vec<From, Size>& v);

template < typename To, typename From, size_t Size >
constexpr mat<To, Size> cast_to(const mat<From, Size>& m);
```

### Access

```cpp
template < typename T, size_t Size >
constexpr T component(const vec<T, Size>& v, size_t index);

template < typename T, size_t Size >
constexpr vec<T, Size> component(vec<T, Size> v, size_t index, T x);

template < typename T, size_t Size >
constexpr vec<T, Size> row(const mat<T, Size>& m, size_t index);

template < typename T, size_t Size >
constexpr mat<T, Size> row(mat<T, Size> m, size_t index, const vec<T, Size>& v);

template < typename T, size_t Size >
constexpr vec<T, Size> column(const mat<T, Size>& m, size_t index);

template < typename T, size_t Size >
constexpr mat<T, Size> column(const mat<T, Size>& m, size_t index, const vec<T, Size>& v);
```

### Matrix Transform 3D

```cpp
template < typename T >
constexpr mat<T, 4> translate(T x, T y, T z);

template < typename T >
constexpr mat<T, 4> translate(const vec<T, 3>& v);

template < typename T >
constexpr mat<T, 4> translate(const mat<T, 4>& m, T x, T y, T z);

template < typename T >
constexpr mat<T, 4> translate(const mat<T, 4>& m, const vec<T, 3>& v);

template < typename T >
mat<T, 4> rotate(T angle, const vec<T, 3>& axis);

template < typename T >
mat<T, 4> rotate(const mat<T, 4>& m, T angle, const vec<T, 3>& axis);

template < typename T >
mat<T, 4> rotate_x(T angle);

template < typename T >
mat<T, 4> rotate_x(const mat<T, 4>& m, T angle);

template < typename T >
mat<T, 4> rotate_y(T angle);

template < typename T >
mat<T, 4> rotate_y(const mat<T, 4>& m, T angle);

template < typename T >
mat<T, 4> rotate_z(T angle);

template < typename T >
mat<T, 4> rotate_z(const mat<T, 4>& m, T angle);

template < typename T >
constexpr mat<T, 4> scale(T x, T y, T z);

template < typename T >
constexpr mat<T, 4> scale(const vec<T, 3>& v);

template < typename T >
constexpr mat<T, 4> scale(const mat<T, 4>& m, T x, T y, T z);

template < typename T >
constexpr mat<T, 4> scale(const mat<T, 4>& m, const vec<T, 3>& v);

// look_at

template < typename T >
mat<T, 4> look_at_lh(const vec<T, 3>& eye, const vec<T, 3>& at, const vec<T, 3>& up);

template < typename T >
mat<T, 4> look_at_rh(const vec<T, 3>& eye, const vec<T, 3>& at, const vec<T, 3>& up);
```

### Matrix Transform 2D

```cpp
template < typename T >
constexpr mat<T, 3> translate(T x, T y);

template < typename T >
constexpr mat<T, 3> translate(const vec<T, 2>& v);

template < typename T >
constexpr mat<T, 3> translate(const mat<T, 3>& m, T x, T y);

template < typename T >
constexpr mat<T, 3> translate(const mat<T, 3>& m, const vec<T, 2>& v);

template < typename T >
mat<T, 3> rotate(T angle);

template < typename T >
mat<T, 3> rotate(const mat<T, 3>& m, T angle);

template < typename T >
constexpr mat<T, 3> scale(T x, T y);

template < typename T >
constexpr mat<T, 3> scale(const vec<T, 2>& v);

template < typename T >
constexpr mat<T, 3> scale(const mat<T, 3>& m, T x, T y);

template < typename T >
constexpr mat<T, 3> scale(const mat<T, 3>& m, const vec<T, 2>& v);

template < typename T >
constexpr mat<T, 3> shear(T x, T y);

template < typename T >
constexpr mat<T, 3> shear(const vec<T, 2>& v);

template < typename T >
constexpr mat<T, 3> shear(const mat<T, 3>& m, T x, T y);

template < typename T >
constexpr mat<T, 3> shear(const mat<T, 3>& m, const vec<T, 2>& v);

template < typename T >
constexpr mat<T, 3> shear_x(T y);

template < typename T >
constexpr mat<T, 3> shear_x(const mat<T, 3>& m, T y);

template < typename T >
constexpr mat<T, 3> shear_y(T x);

template < typename T >
constexpr mat<T, 3> shear_y(const mat<T, 3>& m, T x);
```

### Matrix Projections

```cpp
template < typename T >
mat<T, 4> orthographic_lh_zo(T left, T right, T bottom, T top, T znear, T zfar);

template < typename T >
mat<T, 4> orthographic_lh_no(T left, T right, T bottom, T top, T znear, T zfar);

template < typename T >
mat<T, 4> orthographic_rh_zo(T left, T right, T bottom, T top, T znear, T zfar);

template < typename T >
mat<T, 4> orthographic_rh_no(T left, T right, T bottom, T top, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_lh_zo(T fov, T aspect, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_lh_no(T fov, T aspect, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_rh_zo(T fov, T aspect, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_rh_no(T fov, T aspect, T znear, T zfar);
```

### Vector Transform

```cpp
template < typename T, size_t Size >
T angle(const vec<T, Size>& x, const vec<T, Size>& y);

template < typename T >
vec<T, 2> rotate(const vec<T, 2>& v, T angle);

template < typename T >
vec<T, 3> rotate(const vec<T, 3>& v, T angle, const vec<T, 3>& normal);

template < typename T >
vec<T, 4> rotate(const vec<T, 4>& v, T angle, const vec<T, 3>& normal);

template < typename T, std::size_t Size >
vec<T, Size> project(const vec<T, Size>& v, const vec<T, Size>& normal);
```

## [License (MIT)](./LICENSE.md)
