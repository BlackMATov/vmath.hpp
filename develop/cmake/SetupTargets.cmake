add_library(${PROJECT_NAME}.setup_targets INTERFACE)
add_library(${PROJECT_NAME}::setup_targets ALIAS ${PROJECT_NAME}.setup_targets)

target_compile_options(${PROJECT_NAME}.setup_targets INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:
        /WX /W4>
    $<$<CXX_COMPILER_ID:GNU>:
        -Werror -Wall -Wextra -Wpedantic>
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Werror -Weverything -Wconversion
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        -Wno-ctad-maybe-unsupported
        -Wno-double-promotion
        -Wno-float-equal
        -Wno-shadow-field-in-constructor
        -Wno-unknown-warning-option
        >)

target_link_libraries(${PROJECT_NAME}.setup_targets INTERFACE
    $<$<BOOL:${BUILD_WITH_COVERAGE}>:
        vmath.hpp::enable_gcov>
    $<$<BOOL:${BUILD_WITH_SANITIZERS}>:
        vmath.hpp::enable_asan
        vmath.hpp::enable_ubsan>
    $<$<BOOL:${BUILD_WITH_NO_EXCEPTIONS}>:
        vmath.hpp::disable_exceptions>
    $<$<BOOL:${BUILD_WITH_NO_RTTI}>:
        vmath.hpp::disable_rtti>)
