project(vmath.hpp.untests)

file(GLOB_RECURSE UNTESTS_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.hpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UNTESTS_SOURCES})

add_executable(${PROJECT_NAME} ${UNTESTS_SOURCES})
add_executable(${PROJECT_NAME}.singles ${UNTESTS_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    vmath.hpp::vmath.hpp
    vmath.hpp::setup_targets)

target_link_libraries(${PROJECT_NAME}.singles PRIVATE
    vmath.hpp::singles
    vmath.hpp::setup_targets)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
add_test(${PROJECT_NAME} ${PROJECT_NAME}.singles)
