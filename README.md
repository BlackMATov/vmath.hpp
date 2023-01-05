# vmath.hpp

> C++17 tiny vector math library

[![linux][badge.linux]][linux]
[![darwin][badge.darwin]][darwin]
[![windows][badge.windows]][windows]
[![language][badge.language]][language]
[![license][badge.license]][license]

[badge.darwin]: https://img.shields.io/github/actions/workflow/status/BlackMATov/vmath.hpp/.github/workflows/darwin.yml?label=Xcode&logo=xcode
[badge.linux]: https://img.shields.io/github/actions/workflow/status/BlackMATov/vmath.hpp/.github/workflows/linux.yml?label=GCC%2FClang&logo=linux
[badge.windows]: https://img.shields.io/github/actions/workflow/status/BlackMATov/vmath.hpp/.github/workflows/windows.yml?label=Visual%20Studio&logo=visual-studio
[badge.language]: https://img.shields.io/badge/language-C%2B%2B17-yellow
[badge.license]: https://img.shields.io/badge/license-MIT-blue

[darwin]: https://github.com/BlackMATov/vmath.hpp/actions?query=workflow%3Adarwin
[linux]: https://github.com/BlackMATov/vmath.hpp/actions?query=workflow%3Alinux
[windows]: https://github.com/BlackMATov/vmath.hpp/actions?query=workflow%3Awindows
[language]: https://en.wikipedia.org/wiki/C%2B%2B17
[license]: https://en.wikipedia.org/wiki/MIT_License

[vmath]: https://github.com/BlackMATov/vmath.hpp

## Requirements

- [clang](https://clang.llvm.org/) **>= 7**
- [gcc](https://www.gnu.org/software/gcc/) **>= 7**
- [msvc](https://visualstudio.microsoft.com/) **>= 2019**
- [xcode](https://developer.apple.com/xcode/) **>= 10.3**

## Installation

[vmath.hpp][vmath] is a header-only library. All you need to do is copy the headers files from `headers` directory into your project and include them:

```cpp
#include "vmath.hpp/vmath_all.hpp"
```

Also, you can add the root repository directory to your [cmake](https://cmake.org) project:

```cmake
add_subdirectory(external/vmath.hpp)
target_link_libraries(your_project_target PUBLIC vmath.hpp::vmath.hpp)
```

## Disclaimer

The [vmath.hpp][vmath] is a tiny vector math library mainly for games, game engines, and other graphics software. It will never be mathematically strict (e.g. the vector class has operator plus for adding scalars to a vector, which is convenient for developing CG applications but makes no sense in "real" math). For the same reason, the library does not provide flexible vector and matrix sizes. The library functions follow the same principles.

Most functions and types are based on the HLSL ([High-Level Shading Language for DirectX](https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl)) specification. Matrices are row-major, which implies that vector, matrix multiplication is: v * M, not M * v.

## API

- [Vector Types](#Vector-Types)
- [Matrix Types](#Matrix-Types)
- [Quaternion Types](#Quaternion-Types)
- [Vector Operators](#Vector-Operators)
- [Matrix Operators](#Matrix-Operators)
- [Quaternion Operators](#Quaternion-Operators)
- [Common Functions](#Common-Functions)
- [Angle and Trigonometric Functions](#Angle-and-Trigonometric-Functions)
- [Exponential Functions](#Exponential-Functions)
- [Geometric Functions](#Geometric-Functions)
- [Relational Functions](#Relational-Functions)
- [Matrix Functions](#Matrix-Functions)
- [Quaternion Functions](#Quaternion-Functions)
- [Units](#Units)
- [Cast](#Cast)
- [Access](#Access)
- [Matrix Transform 3D](#Matrix-Transform-3D)
- [Matrix Transform 2D](#Matrix-Transform-2D)
- [Matrix Projections](#Matrix-Projections)
- [Vector Transform](#Vector-Transform)
- [Quaternion Transform](#Quaternion-Transform)

### Vector Types

```cpp
template < typename T, size_t Size >
class vec_base;

template < typename T >
class vec_base<T, 2> {
public:
    T x, y;

    vec_base();

    vec_base(uninit_t);
    vec_base(zero_init_t);
    vec_base(unit_init_t);

    explicit vec_base(T v);
    vec_base(T x, T y);

    template < typename U > vec_base(const vec_base<U, 2>& other);
    template < typename U > explicit vec_base(const vec_base<U, 3>& other);
    template < typename U > explicit vec_base(const vec_base<U, 4>& other);

    template < typename U > explicit vec_base(const U* p);
};

template < typename T >
class vec_base<T, 3> {
public:
    T x, y, z;

    vec_base();

    vec_base(uninit_t);
    vec_base(zero_init_t);
    vec_base(unit_init_t);

    explicit vec_base(T v);
    vec_base(T x, T y, T z);

    vec_base(const vec_base<T, 2>& xy, T z);
    vec_base(T x, const vec_base<T, 2>& yz);

    template < typename U > vec_base(const vec_base<U, 3>& other);
    template < typename U > explicit vec_base(const vec_base<U, 4>& other);

    template < typename U > explicit vec_base(const U* p);
};

template < typename T >
class vec_base<T, 4> {
public:
    T x, y, z, w;

    vec_base();

    vec_base(uninit_t);
    vec_base(zero_init_t);
    vec_base(unit_init_t);

    explicit vec_base(T v);
    vec_base(T x, T y, T z, T w);

    vec_base(const vec_base<T, 2>& xy, T z, T w);
    vec_base(T x, const vec_base<T, 2>& yz, T w);
    vec_base(T x, T y, const vec_base<T, 2>& zw);
    vec_base(const vec_base<T, 2>& xy, const vec_base<T, 2>& zw);

    vec_base(const vec_base<T, 3>& xyz, T w);
    vec_base(T x, const vec_base<T, 3>& yzw);

    template < typename U > vec_base(const vec_base<U, 4>& other);

    template < typename U > explicit vec_base(const U* p);
};

template < typename T, size_t Size >
class vec final : public vec_base<T, Size> {
public:
    using self_type = vec;
    using base_type = vec_base<T, Size>;
    using component_type = T;

    using pointer = component_type*;
    using const_pointer = const component_type*;

    using reference = component_type&;
    using const_reference = const component_type&;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static inline size_t size = Size;

    void swap(vec& other);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    pointer data();
    const_pointer data() const;

    reference at(size_t index);
    const_reference at(size_t index) const;

    reference operator[](size_t index);
    const_reference operator[](size_t index) const;
};

using bvec2 = vec<bool, 2>;
using bvec3 = vec<bool, 3>;
using bvec4 = vec<bool, 4>;

using ivec2 = vec<int, 2>;
using ivec3 = vec<int, 3>;
using ivec4 = vec<int, 4>;

using uvec2 = vec<unsigned, 2>;
using uvec3 = vec<unsigned, 3>;
using uvec4 = vec<unsigned, 4>;

using fvec2 = vec<float, 2>;
using fvec3 = vec<float, 3>;
using fvec4 = vec<float, 4>;

using dvec2 = vec<double, 2>;
using dvec3 = vec<double, 3>;
using dvec4 = vec<double, 4>;
```

### Matrix Types

```cpp
template < typename T, size_t Size >
class mat_base;

template < typename T >
class mat_base<T, 2> {
public:
    using row_type = vec<T, 2>;
    row_type rows[2];

    mat_base();

    mat_base(uninit_t);
    mat_base(zero_init_t);
    mat_base(unit_init_t);
    mat_base(identity_init_t);

    explicit mat_base(T d);
    explicit mat_base(const row_type& d);

    mat_base(
        T m11, T m12,
        T m21, T m22);

    mat_base(
        const row_type& row0,
        const row_type& row1);

    template < typename U > mat_base(const mat_base<U, 2>& other);
    template < typename U > explicit mat_base(const mat_base<U, 3>& other);
    template < typename U > explicit mat_base(const mat_base<U, 4>& other);

    template < typename U > explicit mat_base(const U* p);
};

template < typename T >
class mat_base<T, 3> {
public:
    using row_type = vec<T, 3>;
    row_type rows[3];

    mat_base();

    mat_base(uninit_t);
    mat_base(zero_init_t);
    mat_base(unit_init_t);
    mat_base(identity_init_t);

    explicit mat_base(T d);
    explicit mat_base(const row_type& d);

    mat_base(
        T m11, T m12, T m13,
        T m21, T m22, T m23,
        T m31, T m32, T m33);

    mat_base(
        const row_type& row0,
        const row_type& row1,
        const row_type& row2);

    mat_base(
        const mat_base<T, 2>& m,
        const vec_base<T, 2>& v);

    template < typename U > mat_base(const mat_base<U, 3>& other);
    template < typename U > explicit mat_base(const mat_base<U, 2>& other);
    template < typename U > explicit mat_base(const mat_base<U, 4>& other);

    template < typename U > explicit mat_base(const U* p);
};

template < typename T >
class mat_base<T, 4> {
public:
    using row_type = vec<T, 4>;
    row_type rows[4];

    mat_base();

    mat_base(uninit_t);
    mat_base(zero_init_t);
    mat_base(unit_init_t);
    mat_base(identity_init_t);

    explicit mat_base(T d);
    explicit mat_base(const row_type& d);

    mat_base(
        T m11, T m12, T m13, T m14,
        T m21, T m22, T m23, T m24,
        T m31, T m32, T m33, T m34,
        T m41, T m42, T m43, T m44);

    mat_base(
        const row_type& row0,
        const row_type& row1,
        const row_type& row2,
        const row_type& row3);

    mat_base(
        const mat_base<T, 3>& m,
        const vec_base<T, 3>& v);

    template < typename U > mat_base(const mat_base<U, 4>& other);
    template < typename U > explicit mat_base(const mat_base<U, 2>& other);
    template < typename U > explicit mat_base(const mat_base<U, 3>& other);

    template < typename U > explicit mat_base(const U* p);
};

template < typename T, size_t Size >
class mat final : public mat_base<T, Size> {
public:
    using self_type = mat;
    using base_type = mat_base<T, Size>;
    using component_type = T;

    using row_type = vec<T, Size>;

    using pointer = row_type*;
    using const_pointer = const row_type*;

    using reference = row_type&;
    using const_reference = const row_type&;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static inline size_t size = Size;

    void swap(mat& other);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    pointer data();
    const_pointer data() const;

    reference at(size_t index);
    const_reference at(size_t index) const;

    reference operator[](size_t index);
    const_reference operator[](size_t index) const;
};

using bmat2 = mat<bool, 2>;
using bmat3 = mat<bool, 3>;
using bmat4 = mat<bool, 4>;

using imat2 = mat<int, 2>;
using imat3 = mat<int, 3>;
using imat4 = mat<int, 4>;

using umat2 = mat<unsigned, 2>;
using umat3 = mat<unsigned, 3>;
using umat4 = mat<unsigned, 4>;

using fmat2 = mat<float, 2>;
using fmat3 = mat<float, 3>;
using fmat4 = mat<float, 4>;

using dmat2 = mat<double, 2>;
using dmat3 = mat<double, 3>;
using dmat4 = mat<double, 4>;
```

### Quaternion Types

```cpp
template < typename T >
class qua_base {
public:
    vec<T, 3> v;
    T s;

    qua_base();

    qua_base(uninit_t);
    qua_base(zero_init_t);
    qua_base(identity_init_t);

    qua_base(T vx, T vy, T vz, T s);
    qua_base(const vec<T, 3>& v, T s);
    explicit qua_base(const vec<T, 4>& vs);

    template < typename U > qua_base(const qua_base<U, 4>& other);
    template < typename U > explicit operator vec<U, 4>() const;

    template < typename U > explicit qua_base(const U* p);
};

template < typename T >
class qua final {
public:
    using self_type = qua;
    using base_type = qua_base<T>;
    using component_type = T;

    using imag_type = vec<T, 3>;
    using real_type = T;

    using pointer = component_type*;
    using const_pointer = const component_type*;

    using reference = component_type&;
    using const_reference = const component_type&;

    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static inline size_t size = 4;

    void swap(qua& other);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    pointer data();
    const_pointer data() const;

    reference at(size_t index);
    const_reference at(size_t index) const;

    reference operator[](size_t index);
    const_reference operator[](size_t index) const;
};

using fqua = qua<float>;
using dqua = qua<double>;
```

### Vector Operators

```cpp
// +operator

template < typename T, size_t Size >
auto operator+(const vec<T, Size>& xs);

// -operator

template < typename T, size_t Size >
auto operator-(const vec<T, Size>& xs);

// ~operator

template < typename T, size_t Size >
auto operator~(const vec<T, Size>& xs);

// !operator

template < typename T, size_t Size >
auto operator!(const vec<T, Size>& xs);

// ++operator

template < typename T, size_t Size >
vec<T, Size>& operator++(vec<T, Size>& xs);

// --operator

template < typename T, size_t Size >
vec<T, Size>& operator--(vec<T, Size>& xs);

// operator++

template < typename T, size_t Size >
vec<T, Size> operator++(vec<T, Size>& xs, int);

// operator--

template < typename T, size_t Size >
vec<T, Size> operator--(vec<T, Size>& xs, int);

// operator+

template < typename T, typename U, size_t Size >
auto operator+(const vec<T, Size>& xs, U y);

template < typename T, typename U, size_t Size >
auto operator+(T x, const vec<U, Size>& ys);

template < typename T, typename U, size_t Size >
auto operator+(const vec<T, Size>& xs, const vec<U, Size>& ys);

// operator+=

template < typename T, size_t Size >
vec<T, Size>& operator+=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator+=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator-

template < typename T, typename U, size_t Size >
auto operator-(const vec<T, Size>& xs, U y);

template < typename T, typename U, size_t Size >
auto operator-(T x, const vec<U, Size>& ys);

template < typename T, typename U, size_t Size >
auto operator-(const vec<T, Size>& xs, const vec<U, Size>& ys);

// operator-=

template < typename T, size_t Size >
vec<T, Size>& operator-=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator-=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator*

template < typename T, typename U, size_t Size >
auto operator*(const vec<T, Size>& xs, U y);

template < typename T, typename U, size_t Size >
auto operator*(T x, const vec<U, Size>& ys);

template < typename T, typename U, size_t Size >
auto operator*(const vec<T, Size>& xs, const vec<U, Size>& ys);

// operator*=

template < typename T, size_t Size >
vec<T, Size>& operator*=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator*=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator/

template < typename T, typename U, size_t Size >
auto operator/(const vec<T, Size>& xs, U y);

template < typename T, typename U, size_t Size >
auto operator/(T x, const vec<U, Size>& ys);

template < typename T, typename U, size_t Size >
auto operator/(const vec<T, Size>& xs, const vec<U, Size>& ys);

// operator/=

template < typename T, size_t Size >
vec<T, Size>& operator/=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator/=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator&

template < typename T, size_t Size >
auto operator&(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator&(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
auto operator&(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator&=

template < typename T, size_t Size >
vec<T, Size>& operator&=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator&=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator|

template < typename T, size_t Size >
auto operator|(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator|(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
auto operator|(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator|=

template < typename T, size_t Size >
vec<T, Size>& operator|=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator|=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator^

template < typename T, size_t Size >
auto operator^(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator^(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
auto operator^(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator^=

template < typename T, size_t Size >
vec<T, Size>& operator^=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator^=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator<<

template < typename T, size_t Size >
auto operator<<(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator<<(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
auto operator<<(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator<<=

template < typename T, size_t Size >
vec<T, Size>& operator<<=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator<<=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator>>

template < typename T, size_t Size >
auto operator>>(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator>>(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
auto operator>>(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator>>=

template < typename T, size_t Size >
vec<T, Size>& operator>>=(vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator>>=(vec<T, Size>& xs, const vec<T, Size>& ys);

// operator&&

template < typename T, size_t Size >
auto operator&&(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator&&(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
auto operator&&(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator||

template < typename T, size_t Size >
auto operator||(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator||(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
auto operator||(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator==

template < typename T, size_t Size >
bool operator==(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator!=

template < typename T, size_t Size >
bool operator!=(const vec<T, Size>& xs, const vec<T, Size>& ys);

// operator<

template < typename T, size_t Size >
bool operator<(const vec<T, Size>& xs, const vec<T, Size>& ys);
```

### Matrix Operators

```cpp
// +operator

template < typename T, size_t Size >
auto operator+(const mat<T, Size>& xs);

// -operator

template < typename T, size_t Size >
auto operator-(const mat<T, Size>& xs);

// ~operator

template < typename T, size_t Size >
auto operator~(const mat<T, Size>& xs);

// !operator

template < typename T, size_t Size >
auto operator!(const mat<T, Size>& xs);

// ++operator

template < typename T, size_t Size >
mat<T, Size>& operator++(mat<T, Size>& xs);

// --operator

template < typename T, size_t Size >
mat<T, Size>& operator--(mat<T, Size>& xs);

// operator++

template < typename T, size_t Size >
mat<T, Size> operator++(mat<T, Size>& xs, int);

// operator--

template < typename T, size_t Size >
mat<T, Size> operator--(mat<T, Size>& xs, int);

// operator+

template < typename T, typename U, size_t Size >
auto operator+(const mat<T, Size>& xs, U y);

template < typename T, typename U, size_t Size >
auto operator+(T x, const mat<U, Size>& ys);

template < typename T, typename U, size_t Size >
auto operator+(const mat<T, Size>& xs, const mat<U, Size>& ys);

// operator+=

template < typename T, size_t Size >
mat<T, Size>& operator+=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
mat<T, Size>& operator+=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator-

template < typename T, typename U, size_t Size >
auto operator-(const mat<T, Size>& xs, U y);

template < typename T, typename U, size_t Size >
auto operator-(T x, const mat<U, Size>& ys);

template < typename T, typename U, size_t Size >
auto operator-(const mat<T, Size>& xs, const mat<U, Size>& ys);

// operator-=

template < typename T, size_t Size >
mat<T, Size>& operator-=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
mat<T, Size>& operator-=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator*

template < typename T, typename U, size_t Size >
auto operator*(const mat<T, Size>& xs, U y);

template < typename T, typename U, size_t Size >
auto operator*(T x, const mat<U, Size>& ys);

template < typename T, typename U, size_t Size >
auto operator*(const vec<T, Size>& xs, const mat<U, Size>& ys);

template < typename T, typename U, size_t Size >
auto operator*(const mat<T, Size>& xs, const mat<U, Size>& ys);

// operator*=

template < typename T, size_t Size >
mat<T, Size>& operator*=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size>& operator*=(vec<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size >
mat<T, Size>& operator*=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator/

template < typename T, typename U, size_t Size >
auto operator/(const mat<T, Size>& xs, U y);

template < typename T, typename U, size_t Size >
auto operator/(T x, const mat<U, Size>& ys);

// operator/=

template < typename T, size_t Size >
mat<T, Size>& operator/=(mat<T, Size>& xs, T y);

// operator&

template < typename T, size_t Size >
auto operator&(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator&(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
auto operator&(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator&=

template < typename T, size_t Size >
mat<T, Size>& operator&=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
mat<T, Size>& operator&=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator|

template < typename T, size_t Size >
auto operator|(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator|(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
auto operator|(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator|=

template < typename T, size_t Size >
mat<T, Size>& operator|=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
mat<T, Size>& operator|=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator^

template < typename T, size_t Size >
auto operator^(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator^(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
auto operator^(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator^=

template < typename T, size_t Size >
mat<T, Size>& operator^=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
mat<T, Size>& operator^=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator<<

template < typename T, size_t Size >
auto operator<<(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator<<(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
auto operator<<(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator<<=

template < typename T, size_t Size >
mat<T, Size>& operator<<=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
mat<T, Size>& operator<<=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator>>

template < typename T, size_t Size >
auto operator>>(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator>>(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
auto operator>>(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator>>=

template < typename T, size_t Size >
mat<T, Size>& operator>>=(mat<T, Size>& xs, T y);

template < typename T, size_t Size >
mat<T, Size>& operator>>=(mat<T, Size>& xs, const mat<T, Size>& ys);

// operator&&

template < typename T, size_t Size >
auto operator&&(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator&&(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
auto operator&&(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator||

template < typename T, size_t Size >
auto operator||(const mat<T, Size>& xs, T y);

template < typename T, size_t Size >
auto operator||(T x, const mat<T, Size>& ys);

template < typename T, size_t Size >
auto operator||(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator==

template < typename T, size_t Size >
bool operator==(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator!=

template < typename T, size_t Size >
bool operator!=(const mat<T, Size>& xs, const mat<T, Size>& ys);

// operator<

template < typename T, size_t Size >
bool operator<(const mat<T, Size>& xs, const mat<T, Size>& ys);
```

### Quaternion Operators

```cpp
// +operator

template < typename T >
auto operator+(const qua<T>& xs);

// -operator

template < typename T >
auto operator-(const qua<T>& xs);

// operator+

template < typename T, typename U >
auto operator+(const qua<T>& xs, const qua<U>& ys);

// operator+=

template < typename T >
qua<T>& operator+=(qua<T>& xs, const qua<T>& ys);

// operator-

template < typename T, typename U >
auto operator-(const qua<T>& xs, const qua<U>& ys);

// operator-=

template < typename T >
qua<T>& operator-=(qua<T>& xs, const qua<T>& ys);

// operator*

template < typename T, typename U >
auto operator*(const qua<T>& xs, U y);

template < typename T, typename U >
auto operator*(T x, const qua<U>& ys);

template < typename T, typename U >
auto operator*(const vec<T, 3>& xs, const qua<U>& ys);

template < typename T, typename U >
auto operator*(const qua<T>& xs, const qua<U>& ys);

// operator*=

template < typename T >
qua<T>& operator*=(qua<T>& xs, T y);

template < typename T >
vec<T, 3>& operator*=(vec<T, 3>& xs, const qua<T>& ys);

template < typename T >
qua<T>& operator*=(qua<T>& xs, const qua<T>& ys);

// operator/

template < typename T, typename U >
auto operator/(const qua<T>& xs, U y);

template < typename T, typename U >
auto operator/(T x, const qua<U>& ys);

// operator/=

template < typename T >
qua<T>& operator/=(qua<T>& xs, T y);

// operator==

template < typename T >
bool operator==(const qua<T>& xs, const qua<T>& ys);

// operator!=

template < typename T >
bool operator!=(const qua<T>& xs, const qua<T>& ys);

// operator<

template < typename T >
bool operator<(const qua<T>& xs, const qua<T>& ys);
```

### Common Functions

#### Scalar

```cpp
template < arithmetic T >
T abs(T x);

template < arithmetic T >
T sqr(T x);

template < arithmetic T >
T sign(T x);

template < floating_point T >
T rcp(T x);

template < floating_point T >
T floor(T x);

template < floating_point T >
T trunc(T x);

template < floating_point T >
T round(T x);

template < floating_point T >
T ceil(T x);

template < floating_point T >
T fract(T x);

template < floating_point T >
T fmod(T x, T y);

template < floating_point T >
T modf(T x, T* y);

template < floating_point T >
T copysign(T x, T s);

template < arithmetic T >
T min(T x, T y);

template < arithmetic T >
T max(T x, T y);

template < arithmetic T >
T clamp(T x, T min_x, T max_x);

template < arithmetic T >
T saturate(T x);

template < floating_point T >
T lerp(T x, T y, T a);

template < floating_point T >
T lerp(T x, T y, T x_a, T y_a);

template < floating_point T >
T step(T edge, T x);

template < floating_point T >
T smoothstep(T edge0, T edge1, T x);
```

#### Vector

```cpp
template < typename T, size_t Size >
vec<T, Size> abs(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> sqr(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> sign(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> rcp(const vec<T, Size>& xs);

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
vec<T, Size> copysign(const vec<T, Size>& xs, T s);

template < typename T, size_t Size >
vec<T, Size> copysign(const vec<T, Size>& xs, const vec<T, Size>& ss);

template < typename T, size_t Size >
T min(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> min(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size> min(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
vec<T, Size> min(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
T max(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> max(const vec<T, Size>& xs, T y);

template < typename T, size_t Size >
vec<T, Size> max(T x, const vec<T, Size>& ys);

template < typename T, size_t Size >
vec<T, Size> max(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
vec<T, Size> clamp(const vec<T, Size>& xs, T min_x, T max_x);

template < typename T, size_t Size >
vec<T, Size> clamp(const vec<T, Size>& xs, const vec<T, Size>& min_xs, const vec<T, Size>& max_xs);

template < typename T, size_t Size >
vec<T, Size> saturate(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> lerp(const vec<T, Size>& xs, const vec<T, Size>& ys, T a);

template < typename T, size_t Size >
vec<T, Size> lerp(const vec<T, Size>& xs, const vec<T, Size>& ys, T x_a, T y_a);

template < typename T, size_t Size >
vec<T, Size> lerp(const vec<T, Size>& xs, const vec<T, Size>& ys, const vec<T, Size>& as);

template < typename T, size_t Size >
vec<T, Size> lerp(const vec<T, Size>& xs, const vec<T, Size>& ys, const vec<T, Size>& xs_a, const vec<T, Size>& ys_a);

template < typename T, size_t Size >
vec<T, Size> step(T edge, const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> step(const vec<T, Size>& edges, const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> smoothstep(T edge0, T edge1, const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> smoothstep(const vec<T, Size>& edges0, const vec<T, Size>& edges1, const vec<T, Size>& xs);
```

#### Quaternion

```cpp
template < typename T >
qua<T> lerp(const qua<T>& xs, const qua<T>& ys, T a);

template < typename T >
qua<T> lerp(const qua<T>& xs, const qua<T>& ys, T xs_a, T ys_a);

template < typename T >
qua<T> nlerp(const qua<T>& unit_xs, const qua<T>& unit_ys, T a);

template < typename T >
qua<T> slerp(const qua<T>& unit_xs, const qua<T>& unit_ys, T a);
```

### Angle and Trigonometric Functions

#### Scalar

```cpp
template < floating_point T >
T radians(T degrees);

template < floating_point T >
T degrees(T radians);

template < floating_point T >
T sin(T x);

template < floating_point T >
T cos(T x);

template < floating_point T >
T tan(T x);

template < floating_point T >
T asin(T x);

template < floating_point T >
T acos(T x);

template < floating_point T >
T atan(T x);

template < floating_point T >
T atan2(T y, T x);

template < floating_point T >
T sinh(T x);

template < floating_point T >
T cosh(T x);

template < floating_point T >
T tanh(T x);

template < floating_point T >
T asinh(T x);

template < floating_point T >
T acosh(T x);

template < floating_point T >
T atanh(T x);

template < floating_point T >
pair<T, T> sincos(T x);

template < floating_point T >
void sincos(T x, T* s, T* c);
```

#### Vector

```cpp
template < typename T, size_t Size >
vec<T, Size> radians(const vec<T, Size>& degrees);

template < typename T, size_t Size >
vec<T, Size> degrees(const vec<T, Size>& radians);

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

template < typename T, size_t Size >
pair<vec<T, Size>, vec<T, Size>> sincos(const vec<T, Size>& xs);

template < typename T, size_t Size >
void sincos(const vec<T, Size>& xs, vec<T, Size>* ss, vec<T, Size>* cs);
```

### Exponential Functions

#### Scalar

```cpp
template < floating_point T >
T pow(T x, T y);

template < floating_point T >
T exp(T x);

template < floating_point T >
T log(T x);

template < floating_point T >
T exp2(T x);

template < floating_point T >
T log2(T x);

template < floating_point T >
T sqrt(T x);

template < floating_point T >
T rsqrt(T x);
```

#### Vector

```cpp
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

### Geometric Functions

#### Scalar

```cpp
template < arithmetic T, arithmetic U
         , arithmetic V = decltype(declval<T>() * declval<U>()) >
V dot(T x, U y);

template < arithmetic T >
T length(T x);

template < arithmetic T >
T rlength(T x);

template < arithmetic T >
T length2(T x);

template < arithmetic T >
T rlength2(T x);

template < arithmetic T >
T distance(T x, T y);

template < arithmetic T >
T distance2(T x, T y);

template < floating_point T >
T normalize(T x);

template < floating_point T >
T faceforward(T n, T i, T nref);

template < floating_point T >
T reflect(T i, T n);

template < floating_point T >
T refract(T i, T n, T eta);
```

#### Vector

```cpp
template < typename T, typename U, size_t Size
         , typename V = decltype(declval<T>() * declval<U>()) >
V dot(const vec<T, Size>& xs, const vec<U, Size>& ys);

template < typename T, size_t Size >
T length(const vec<T, Size>& xs);

template < typename T, size_t Size >
T rlength(const vec<T, Size>& xs);

template < typename T, size_t Size >
T length2(const vec<T, Size>& xs);

template < typename T, size_t Size >
T rlength2(const vec<T, Size>& xs);

template < typename T, size_t Size >
T distance(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size >
T distance2(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, typename U
         , typename V = decltype(declval<T>() * declval<U>()) >
V cross(const vec<T, 2>& xs, const vec<U, 2>& ys);

template < typename T, typename U
         , typename V = decltype(declval<T>() * declval<U>()) >
vec<V, 3> cross(const vec<T, 3>& xs, const vec<U, 3>& ys);

template < typename T, size_t Size >
vec<T, Size> normalize(const vec<T, Size>& xs);

template < typename T, size_t Size >
vec<T, Size> faceforward(const vec<T, Size>& n, const vec<T, Size>& i, const vec<T, Size>& nref);

template < typename T, size_t Size >
vec<T, Size> reflect(const vec<T, Size>& i, const vec<T, Size>& n);

template < typename T, size_t Size >
vec<T, Size> refract(const vec<T, Size>& i, const vec<T, Size>& n, T eta);
```

#### Quaternion

```cpp
template < typename T, typename U
         , typename V = decltype(dot(
             declval<vec<T, 4>>(),
             declval<vec<U, 4>>())) >
V dot(const qua<T>& xs, const qua<U>& ys);

template < typename T >
T length(const qua<T>& xs);

template < typename T >
T rlength(const qua<T>& xs);

template < typename T >
T length2(const qua<T>& xs);

template < typename T >
T rlength2(const qua<T>& xs);

template < typename T >
T distance(const qua<T>& xs, const qua<T>& ys);

template < typename T >
qua<T> normalize(const qua<T>& xs);
```

### Relational Functions

#### Scalar

```cpp
template < arithmetic T >
bool any(T x);

template < arithmetic T >
bool all(T x);

template < arithmetic T >
bool approx(T x, T y);

template < arithmetic T >
bool approx(T x, T y, T epsilon);

template < arithmetic T >
bool less(T x, T y);

template < arithmetic T >
bool less_equal(T x, T y);

template < arithmetic T >
bool greater(T x, T y);

template < arithmetic T >
bool greater_equal(T x, T y);

template < arithmetic T >
bool equal_to(T x, T y);

template < arithmetic T >
bool not_equal_to(T x, T y);
```

#### Vector

```cpp
template < typename T, size_t Size
         , typename U = decltype(any(declval<T>())) >
U any(const vec<T, Size>& xs);

template < typename T, size_t Size
         , typename U = decltype(all(declval<T>())) >
U all(const vec<T, Size>& xs);

template < typename T, size_t Size
         , typename U = decltype(approx(
             declval<T>(),
             declval<T>())) >
vec<U, Size> approx(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size
         , typename U = decltype(approx(
             declval<T>(),
             declval<T>(),
             declval<T>())) >
vec<U, Size> approx(const vec<T, Size>& xs, const vec<T, Size>& ys, T epsilon);

template < typename T, size_t Size
         , typename U = decltype(less(
             declval<T>(),
             declval<T>())) >
vec<U, Size> less(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size
         , typename U = decltype(less_equal(
             declval<T>(),
             declval<T>())) >
vec<U, Size> less_equal(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size
         , typename U = decltype(greater(
             declval<T>(),
             declval<T>())) >
vec<U, Size> greater(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size
         , typename U = decltype(greater_equal(
             declval<T>(),
             declval<T>())) >
vec<U, Size> greater_equal(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size
         , typename U = decltype(equal_to(
             declval<T>(),
             declval<T>())) >
vec<U, Size> equal_to(const vec<T, Size>& xs, const vec<T, Size>& ys);

template < typename T, size_t Size
         , typename U = decltype(not_equal_to(
             declval<T>(),
             declval<T>())) >
vec<U, Size> not_equal_to(const vec<T, Size>& xs, const vec<T, Size>& ys);
```

#### Matrix

```cpp
template < typename T, size_t Size
         , typename U = decltype(any(declval<vec<T, Size>>())) >
U any(const mat<T, Size>& xs);

template < typename T, size_t Size
         , typename U = decltype(all(declval<vec<T, Size>>())) >
U all(const mat<T, Size>& xs);

template < typename T, size_t Size
         , typename U = typename decltype(approx(
             declval<vec<T, Size>>(),
             declval<vec<T, Size>>()))::component_type >
mat<U, Size> approx(const mat<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size
         , typename U = typename decltype(approx(
             declval<vec<T, Size>>(),
             declval<vec<T, Size>>(),
             declval<T>()))::component_type >
mat<U, Size> approx(const mat<T, Size>& xs, const mat<T, Size>& ys, T epsilon);

template < typename T, size_t Size
         , typename U = typename decltype(less(
             declval<vec<T, Size>>(),
             declval<vec<T, Size>>()))::component_type >
mat<U, Size> less(const mat<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size
         , typename U = typename decltype(less_equal(
             declval<vec<T, Size>>(),
             declval<vec<T, Size>>()))::component_type >
mat<U, Size> less_equal(const mat<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size
         , typename U = typename decltype(greater(
             declval<vec<T, Size>>(),
             declval<vec<T, Size>>()))::component_type >
mat<U, Size> greater(const mat<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size
         , typename U = typename decltype(greater_equal(
             declval<vec<T, Size>>(),
             declval<vec<T, Size>>()))::component_type >
mat<U, Size> greater_equal(const mat<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size
         , typename U = typename decltype(equal_to(
             declval<vec<T, Size>>(),
             declval<vec<T, Size>>()))::component_type >
mat<U, Size> equal_to(const mat<T, Size>& xs, const mat<T, Size>& ys);

template < typename T, size_t Size
         , typename U = typename decltype(not_equal_to(
             declval<vec<T, Size>>(),
             declval<vec<T, Size>>()))::component_type >
mat<U, Size> not_equal_to(const mat<T, Size>& xs, const mat<T, Size>& ys);
```

#### Quaternion

```cpp
template < typename T
         , typename U = decltype(any(declval<vec<T, 4>>())) >
U any(const qua<T>& xs);

template < typename T
         , typename U = decltype(all(declval<vec<T, 4>>())) >
U all(const qua<T>& xs);

template < typename T
         , typename U = typename decltype(approx(
             declval<vec<T, 4>>(),
             declval<vec<T, 4>>()))::component_type >
vec<U, 4> approx(const qua<T>& xs, const qua<T>& ys);

template < typename T
         , typename U = typename decltype(approx(
             declval<vec<T, 4>>(),
             declval<vec<T, 4>>(),
             declval<T>()))::component_type >
vec<U, 4> approx(const qua<T>& xs, const qua<T>& ys, T epsilon);

template < typename T
         , typename U = typename decltype(less(
             declval<vec<T, 4>>(),
             declval<vec<T, 4>>()))::component_type >
vec<U, 4> less(const qua<T>& xs, const qua<T>& ys);

template < typename T
         , typename U = typename decltype(less_equal(
             declval<vec<T, 4>>(),
             declval<vec<T, 4>>()))::component_type >
vec<U, 4> less_equal(const qua<T>& xs, const qua<T>& ys);

template < typename T
         , typename U = typename decltype(greater(
             declval<vec<T, 4>>(),
             declval<vec<T, 4>>()))::component_type >
vec<U, 4> greater(const qua<T>& xs, const qua<T>& ys);

template < typename T
         , typename U = typename decltype(greater_equal(
             declval<vec<T, 4>>(),
             declval<vec<T, 4>>()))::component_type >
vec<U, 4> greater_equal(const qua<T>& xs, const qua<T>& ys);

template < typename T
         , typename U = typename decltype(equal_to(
             declval<vec<T, 4>>(),
             declval<vec<T, 4>>()))::component_type >
vec<U, 4> equal_to(const qua<T>& xs, const qua<T>& ys);

template < typename T
         , typename U = typename decltype(not_equal_to(
             declval<vec<T, 4>>(),
             declval<vec<T, 4>>()))::component_type >
vec<U, 4> not_equal_to(const qua<T>& xs, const qua<T>& ys);
```

### Matrix Functions

```cpp
template < typename T, size_t Size >
mat<T, Size> transpose(const mat<T, Size>& m);

template < typename T, size_t Size >
mat<T, Size> adjugate(const mat<T, Size>& m);

template < typename T, size_t Size >
T determinant(const mat<T, Size>& m);

template < typename T, size_t Size >
mat<T, Size> inverse(const mat<T, Size>& m);
```

### Quaternion Functions

```cpp
template < typename T >
qua<T> conjugate(const qua<T>& q);

template < typename T >
qua<T> inverse(const qua<T>& q);
```

### Units

```cpp
template < typename T > inline vec<T, 2> zero2;
template < typename T > inline vec<T, 3> zero3;
template < typename T > inline vec<T, 4> zero4;

template < typename T > inline vec<T, 2> unit2;
template < typename T > inline vec<T, 3> unit3;
template < typename T > inline vec<T, 4> unit4;

template < typename T > inline vec<T, 2> unit2_x;
template < typename T > inline vec<T, 2> unit2_y;

template < typename T > inline vec<T, 3> unit3_x;
template < typename T > inline vec<T, 3> unit3_y;
template < typename T > inline vec<T, 3> unit3_z;

template < typename T > inline vec<T, 4> unit4_x;
template < typename T > inline vec<T, 4> unit4_y;
template < typename T > inline vec<T, 4> unit4_z;
template < typename T > inline vec<T, 4> unit4_w;

template < typename T > inline mat<T, 2> mzero2;
template < typename T > inline mat<T, 3> mzero3;
template < typename T > inline mat<T, 4> mzero4;

template < typename T > inline mat<T, 2> munit2;
template < typename T > inline mat<T, 3> munit3;
template < typename T > inline mat<T, 4> munit4;

template < typename T > inline mat<T, 2> midentity2;
template < typename T > inline mat<T, 3> midentity3;
template < typename T > inline mat<T, 4> midentity4;

template < typename T > inline qua<T> qzero;
template < typename T > inline qua<T> qidentity;
```

### Cast

```cpp
template < arithmetic To, arithmetic From >
To cast_to(From x);

template < typename To, typename From, size_t Size >
vec<To, Size> cast_to(const vec<From, Size>& v);

template < typename To, typename From, size_t Size >
mat<To, Size> cast_to(const mat<From, Size>& m);

template < typename To, typename From >
qua<To> cast_to(const qua<From>& q);
```

### Access

```cpp
template < typename T, size_t Size >
T component(const vec<T, Size>& v, size_t index);

template < typename T, size_t Size >
vec<T, Size> component(const vec<T, Size>& v, size_t index, T x);

template < typename T, size_t Size >
vec<T, Size> row(const mat<T, Size>& m, size_t index);

template < typename T, size_t Size >
mat<T, Size> row(const mat<T, Size>& m, size_t index, const vec<T, Size>& v);

template < typename T, size_t Size >
vec<T, Size> column(const mat<T, Size>& m, size_t index);

template < typename T, size_t Size >
mat<T, Size> column(const mat<T, Size>& m, size_t index, const vec<T, Size>& v);

template < typename T, size_t Size >
vec<T, Size> diagonal(const mat<T, Size>& m);

template < typename T, size_t Size >
mat<T, Size> diagonal(const mat<T, Size>& m, const vec<T, Size>& diagonal);

template < typename T >
T real(const qua<T>& q);

template < typename T >
qua<T> real(qua<T> q, T real);

template < typename T >
vec<T, 3> imag(const qua<T>& q);

template < typename T >
qua<T> imag(qua<T> q, const vec<T, 3>& imag);
```

### Matrix Transform 3D

```cpp
template < typename T >
mat<T, 4> trs(const vec<T, 3>& t, const mat<T, 3>& r);

template < typename T >
mat<T, 4> trs(const vec<T, 3>& t, const mat<T, 3>& r, const vec<T, 3>& s);

template < typename T >
mat<T, 4> trs(const vec<T, 3>& t, const qua<T>& r);

template < typename T >
mat<T, 4> trs(const vec<T, 3>& t, const qua<T>& r, const vec<T, 3>& s);

template < typename T >
mat<T, 4> translate(const vec<T, 3>& v);

template < typename T >
mat<T, 3> rotate(const qua<T>& q);

template < typename T >
mat<T, 4> rotate4(const qua<T>& q);

template < typename T >
mat<T, 3> rotate(T angle, const vec<T, 3>& axis);

template < typename T >
mat<T, 4> rotate4(T angle, const vec<T, 3>& axis);

template < typename T >
mat<T, 3> rotate_x(T angle);

template < typename T >
mat<T, 4> rotate4_x(T angle);

template < typename T >
mat<T, 3> rotate_y(T angle);

template < typename T >
mat<T, 4> rotate4_y(T angle);

template < typename T >
mat<T, 3> rotate_z(T angle);

template < typename T >
mat<T, 4> rotate4_z(T angle);

template < typename T >
mat<T, 3> scale(const vec<T, 3>& v);

template < typename T >
mat<T, 4> scale4(const vec<T, 3>& v);

template < typename T >
mat<T, 3> look_at_lh(const vec<T, 3>& dir, const vec<T, 3>& up);

template < typename T >
mat<T, 4> look_at_lh(const vec<T, 3>& eye, const vec<T, 3>& at, const vec<T, 3>& up);

template < typename T >
mat<T, 3> look_at_rh(const vec<T, 3>& dir, const vec<T, 3>& up);

template < typename T >
mat<T, 4> look_at_rh(const vec<T, 3>& eye, const vec<T, 3>& at, const vec<T, 3>& up);
```

### Matrix Transform 2D

```cpp
template < typename T >
mat<T, 3> trs(const vec<T, 2>& t, const mat<T, 2>& r);

template < typename T >
mat<T, 3> trs(const vec<T, 2>& t, const mat<T, 2>& r, const vec<T, 2>& s);

template < typename T >
mat<T, 3> translate(const vec<T, 2>& v);

template < typename T >
mat<T, 2> rotate(T angle);

template < typename T >
mat<T, 3> rotate3(T angle);

template < typename T >
mat<T, 2> scale(const vec<T, 2>& v);

template < typename T >
mat<T, 3> scale3(const vec<T, 2>& v);

template < typename T >
mat<T, 2> shear(const vec<T, 2>& v);

template < typename T >
mat<T, 3> shear3(const vec<T, 2>& v);
```

### Matrix Projections

```cpp
template < typename T >
mat<T, 4> orthographic_lh(T width, T height, T znear, T zfar);

template < typename T >
mat<T, 4> orthographic_rh(T width, T height, T znear, T zfar);

template < typename T >
mat<T, 4> orthographic_lh(T left, T right, T bottom, T top, T znear, T zfar);

template < typename T >
mat<T, 4> orthographic_rh(T left, T right, T bottom, T top, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_lh(T width, T height, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_rh(T width, T height, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_lh(T left, T right, T bottom, T top, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_rh(T left, T right, T bottom, T top, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_fov_lh(T fovy, T aspect, T znear, T zfar);

template < typename T >
mat<T, 4> perspective_fov_rh(T fovy, T aspect, T znear, T zfar);
```

### Vector Transform

```cpp
template < typename T, size_t Size >
T angle(const vec<T, Size>& x, const vec<T, Size>& y);

template < typename T >
vec<T, 2> rotate(const vec<T, 2>& v, T angle);

template < typename T >
vec<T, 3> rotate_x(const vec<T, 3>& v, T angle);

template < typename T >
vec<T, 3> rotate_y(const vec<T, 3>& v, T angle);

template < typename T >
vec<T, 3> rotate_z(const vec<T, 3>& v, T angle);

template < typename T >
vec<T, 3> rotate(const vec<T, 3>& v, T angle, const vec<T, 3>& axis);

template < typename T, size_t Size >
vec<T, Size> project(const vec<T, Size>& v, const vec<T, Size>& normal);

template < typename T, size_t Size >
vec<T, Size> perpendicular(const vec<T, Size>& v, const vec<T, Size>& normal);
```

### Quaternion Transform

```cpp
template < typename T >
qua<T> qrotate(const mat<T, 3>& m);

template < typename T >
qua<T> qrotate(const qua<T>& q, const mat<T, 3>& m);

template < typename T >
qua<T> qrotate(const vec<T, 3>& from, const vec<T, 3>& to);

template < typename T >
qua<T> qrotate(const qua<T>& q, const vec<T, 3>& from, const vec<T, 3>& to);

template < typename T >
qua<T> qrotate(T angle, const vec<T, 3>& axis);

template < typename T >
qua<T> qrotate(const qua<T>& q, T angle, const vec<T, 3>& axis);

template < typename T >
qua<T> qrotate_x(T angle);

template < typename T >
qua<T> qrotate_x(const qua<T>& q, T angle);

template < typename T >
qua<T> qrotate_y(T angle);

template < typename T >
qua<T> qrotate_y(const qua<T>& q, T angle);

template < typename T >
qua<T> qrotate_z(T angle);

template < typename T >
qua<T> qrotate_z(const qua<T>& q, T angle);

template < typename T >
qua<T> qlook_at_lh(const vec<T, 3>& dir, const vec<T, 3>& up);

template < typename T >
qua<T> qlook_at_rh(const vec<T, 3>& dir, const vec<T, 3>& up);
```

## [License (MIT)](./LICENSE.md)
