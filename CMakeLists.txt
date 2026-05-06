cmake_minimum_required(VERSION 3.16)

project(robot_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(robot_sim ${SOURCES})

target_include_directories(robot_sim PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# ---- SFML ----
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(robot_sim PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

set(SFML_BIN_DIR "${SFML_ROOT}/bin")

add_custom_command(TARGET robot_sim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_BIN_DIR}/sfml-graphics-d-3.dll"
        $<TARGET_FILE_DIR:robot_sim>

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_BIN_DIR}/sfml-window-d-3.dll"
        $<TARGET_FILE_DIR:robot_sim>

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_BIN_DIR}/sfml-system-d-3.dll"
        $<TARGET_FILE_DIR:robot_sim>
)