cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(vmath.hpp
    VERSION "0.0.1"
    DESCRIPTION "C++17 tiny vector math library"
    HOMEPAGE_URL "https://github.com/blackmatov/vmath.hpp"
    LANGUAGES CXX)

option(VMATH_HPP_NO_EXCEPTIONS "Don't use exceptions" OFF)
option(VMATH_HPP_NO_RTTI "Don't use RTTI" OFF)

#
# library
#

file(GLOB_RECURSE VMATH_HPP_HEADERS CONFIGURE_DEPENDS "headers/*.hpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${VMATH_HPP_HEADERS})

add_library(${PROJECT_NAME} INTERFACE ${VMATH_HPP_HEADERS})
add_library(vmath.hpp::vmath.hpp ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} INTERFACE
    cxx_std_17)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_definitions(${PROJECT_NAME} INTERFACE
    $<$<BOOL:${VMATH_HPP_NO_EXCEPTIONS}>:VMATH_HPP_NO_EXCEPTIONS>
    $<$<BOOL:${VMATH_HPP_NO_RTTI}>:VMATH_HPP_NO_RTTI>)

#
# develop
#

if(PROJECT_IS_TOP_LEVEL)
    enable_testing()
    add_subdirectory(develop)
endif()
