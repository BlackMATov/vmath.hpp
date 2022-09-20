project(vmath.hpp.singles)

find_package(PythonInterp REQUIRED)

set(VMATH_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(VMATH_SINGLES_BUILD_SCRIPT "${VMATH_ROOT_DIR}/.ci/build_singles.py")
set(VMATH_SINGLES_INPUT_HEADER "${VMATH_ROOT_DIR}/headers/vmath.hpp/vmath.hpp")
set(VMATH_SINGLES_OUTPUT_HEADER "${VMATH_ROOT_DIR}/singles/vmath.hpp/vmath.hpp")

add_custom_command(OUTPUT ${VMATH_SINGLES_OUTPUT_HEADER}
    COMMAND "${PYTHON_EXECUTABLE}"
            "${VMATH_SINGLES_BUILD_SCRIPT}"
            "${VMATH_SINGLES_INPUT_HEADER}"
            "${VMATH_SINGLES_OUTPUT_HEADER}")

add_custom_target(vmath.hpp.singles.generate
    DEPENDS "${VMATH_SINGLES_OUTPUT_HEADER}")
