cmake_minimum_required(VERSION 3.16)

project(robot_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/external)

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

# ---- nlohmann/json ----
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(robot_sim PRIVATE
    nlohmann_json::nlohmann_json
)

set(SFML_BIN_DIR "${SFML_ROOT}/bin")

add_custom_command(TARGET robot_sim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_BIN_DIR}"
        $<TARGET_FILE_DIR:robot_sim>
)