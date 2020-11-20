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

## [License (MIT)](./LICENSE.md)
