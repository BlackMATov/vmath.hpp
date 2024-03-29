option(BUILD_WITH_COVERAGE "Build with coverage" OFF)
option(BUILD_WITH_SANITIZERS "Build with sanitizers" OFF)
option(BUILD_WITH_NO_EXCEPTIONS "Build with no exceptions" ${VMATH_HPP_NO_EXCEPTIONS})
option(BUILD_WITH_NO_RTTI "Build with no RTTI" ${VMATH_HPP_NO_RTTI})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(DisableExceptions)
include(DisableRTTI)
include(EnableASan)
include(EnableGCov)
include(EnableUBSan)
include(SetupTargets)

add_subdirectory(singles)
add_subdirectory(untests)
add_subdirectory(vendors)

#
# install
#

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(VMATH_HPP_INSTALL_CONFIG_DIR
    "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

set(VMATH_HPP_INSTALL_CONFIG_INPUT
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in")

set(VMATH_HPP_INSTALL_GENERATED_CONFIG_CMAKE
    "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}-config.cmake")

set(VMATH_HPP_INSTALL_GENERATED_CONFIG_VERSION_CMAKE
    "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}-config-version.cmake")

configure_package_config_file(
    "${VMATH_HPP_INSTALL_CONFIG_INPUT}"
    "${VMATH_HPP_INSTALL_GENERATED_CONFIG_CMAKE}"
    INSTALL_DESTINATION "${VMATH_HPP_INSTALL_CONFIG_DIR}"
    NO_SET_AND_CHECK_MACRO)

write_basic_package_version_file(
    "${VMATH_HPP_INSTALL_GENERATED_CONFIG_VERSION_CMAKE}"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    ARCH_INDEPENDENT)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets)

install(
    DIRECTORY singles/headers/${PROJECT_NAME}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(
    EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION "${VMATH_HPP_INSTALL_CONFIG_DIR}")

install(
    FILES "${VMATH_HPP_INSTALL_GENERATED_CONFIG_CMAKE}"
          "${VMATH_HPP_INSTALL_GENERATED_CONFIG_VERSION_CMAKE}"
    DESTINATION "${VMATH_HPP_INSTALL_CONFIG_DIR}")
