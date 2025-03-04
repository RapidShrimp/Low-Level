cmake_minimum_required(VERSION 3.8)

project(Low-Level)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Low-Level src/main.cpp "src/main.h" "src/Engine/Core/GameInstance.h" "src/Engine/Core/GameScene.h")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
target_sources(Low-Level PRIVATE ${MY_SOURCES})
target_include_directories(Low-Level PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(Low-Level PRIVATE SFML::Graphics)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Low-Level PROPERTY CXX_STANDARD 20)
endif()
