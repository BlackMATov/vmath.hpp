project(vmath.hpp.singles)

#
# generate
#

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(VMATH_HPP_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(VMATH_HPP_SINGLES_INPUT "${VMATH_HPP_ROOT_DIR}/headers/vmath.hpp/vmath_all.hpp")
set(VMATH_HPP_SINGLES_OUTPUT "${VMATH_HPP_ROOT_DIR}/develop/singles/headers/vmath.hpp/vmath_all.hpp")
set(VMATH_HPP_SINGLES_SCRIPT "${VMATH_HPP_ROOT_DIR}/develop/singles/scripts/build_singles.py")
file(GLOB_RECURSE VMATH_SINGLES_DEPENDS CONFIGURE_DEPENDS "${VMATH_HPP_ROOT_DIR}/headers/*.hpp")

add_custom_command(OUTPUT "${VMATH_HPP_SINGLES_OUTPUT}"
    COMMAND
        "${Python3_EXECUTABLE}" "${VMATH_HPP_SINGLES_SCRIPT}"
        "${VMATH_HPP_SINGLES_INPUT}" "${VMATH_HPP_SINGLES_OUTPUT}"
    DEPENDS
        "${VMATH_HPP_SINGLES_SCRIPT}" ${VMATH_SINGLES_DEPENDS}
    WORKING_DIRECTORY
        "${VMATH_HPP_ROOT_DIR}")

add_custom_target(${PROJECT_NAME}.generate
    DEPENDS "${VMATH_HPP_SINGLES_OUTPUT}")

#
# library
#

add_library(${PROJECT_NAME} INTERFACE)
add_library(vmath.hpp::singles ALIAS ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME}
    ${PROJECT_NAME}.generate)

target_compile_features(${PROJECT_NAME} INTERFACE
    cxx_std_17)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
