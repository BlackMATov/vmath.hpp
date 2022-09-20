project(vmath.hpp.untests)

file(GLOB_RECURSE UNTESTS_SOURCES "*.cpp" "*.hpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UNTESTS_SOURCES})

add_executable(${PROJECT_NAME} ${UNTESTS_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE vmath.hpp)

add_executable(${PROJECT_NAME}.singles ${UNTESTS_SOURCES})
add_dependencies(${PROJECT_NAME}.singles vmath.hpp.singles.generate)
target_link_libraries(${PROJECT_NAME}.singles PRIVATE vmath.hpp.singles)

#
# setup libraries
#

function(setup_libraries_for_target TARGET)
    target_link_libraries(${TARGET} PRIVATE doctest_with_main)

    if(${BUILD_WITH_COVERAGE})
        target_link_libraries(${TARGET} PRIVATE enable_gcov)
    endif()

    if(${BUILD_WITH_SANITIZERS})
        target_link_libraries(${TARGET} PRIVATE enable_asan enable_ubsan)
    endif()
endfunction()

setup_libraries_for_target(${PROJECT_NAME})
setup_libraries_for_target(${PROJECT_NAME}.singles)

#
# setup warnings
#

function(setup_warnings_for_target TARGET)
    target_compile_options(${TARGET}
        PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /WX /W4>
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:
            -Werror -Wall -Wextra -Wpedantic>
        PRIVATE
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
endfunction()

setup_warnings_for_target(${PROJECT_NAME})
setup_warnings_for_target(${PROJECT_NAME}.singles)

#
# add tests
#

add_test(${PROJECT_NAME} ${PROJECT_NAME})
add_test(${PROJECT_NAME} ${PROJECT_NAME}.singles)
