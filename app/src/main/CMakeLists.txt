project(Hard3D)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-Wall -std=c++14 -c -O3)
set(CMAKE_CXX_FLAGS_DEBUG        "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage --coverage")

file(GLOB CPPS "jni/*.cpp" "jni/tools/*.cpp")

set (source "${CMAKE_SOURCE_DIR}/assets")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
)

add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-system m pthread dl drm Xdamage Xfixes X11 xcb xcb-glx xcb-dri2 Xxf86vm Xext X11 Xau Xdmcp)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
