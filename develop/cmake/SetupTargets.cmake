add_library(${PROJECT_NAME}.setup_targets INTERFACE)
add_library(${PROJECT_NAME}::setup_targets ALIAS ${PROJECT_NAME}.setup_targets)

target_link_libraries(${PROJECT_NAME}.setup_targets INTERFACE
    vmath.hpp.vendors::doctest)

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

if(BUILD_WITH_COVERAGE)
    target_link_libraries(${PROJECT_NAME}.setup_targets INTERFACE
        vmath.hpp::enable_gcov)
endif()

if(BUILD_WITH_SANITIZERS)
    target_link_libraries(${PROJECT_NAME}.setup_targets INTERFACE
        vmath.hpp::enable_asan
        vmath.hpp::enable_ubsan)
endif()

if(BUILD_WITH_NO_EXCEPTIONS)
    target_link_libraries(${PROJECT_NAME}.setup_targets INTERFACE
        vmath.hpp::disable_exceptions)

    target_compile_definitions(${PROJECT_NAME}.setup_targets INTERFACE
        DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS)
endif()

if(BUILD_WITH_NO_RTTI)
    target_link_libraries(${PROJECT_NAME}.setup_targets INTERFACE
        vmath.hpp::disable_rtti)
endif()
