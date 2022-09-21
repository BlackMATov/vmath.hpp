project(vmath.hpp.singles)

#
# generate
#

find_package(PythonInterp REQUIRED)

set(VMATH_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(VMATH_SINGLES_INPUT "${VMATH_ROOT_DIR}/headers/vmath.hpp/vmath_all.hpp")
set(VMATH_SINGLES_OUTPUT "${VMATH_ROOT_DIR}/singles/headers/vmath.hpp/vmath_all.hpp")
file(GLOB_RECURSE VMATH_SINGLES_DEPENDS "${VMATH_ROOT_DIR}/headers/*.hpp")

add_custom_command(OUTPUT "${VMATH_SINGLES_OUTPUT}"
    COMMAND "${PYTHON_EXECUTABLE}" ".ci/build_singles.py" "${VMATH_SINGLES_INPUT}" "${VMATH_SINGLES_OUTPUT}"
    DEPENDS ${VMATH_SINGLES_DEPENDS}
    WORKING_DIRECTORY "${VMATH_ROOT_DIR}")

add_custom_target(${PROJECT_NAME}.generate
    DEPENDS "${VMATH_SINGLES_OUTPUT}")

#
# library
#

add_library(${PROJECT_NAME} INTERFACE)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}.generate)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_include_directories(${PROJECT_NAME} INTERFACE headers)
