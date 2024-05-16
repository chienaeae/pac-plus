cmake_minimum_required(VERSION 3.22)

project(pac-plus LANGUAGES CXX)

# Generate compile_commands.json for analysis tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Include directories
include_directories(include)

# Add game library
add_library(game STATIC
        src/fps.cpp
        src/texture.cpp
        src/timer.cpp
        src/square.cpp
        src/scene-state-machine.cpp
        src/scene-test.cpp
        src/game.cpp
        src/font.cpp
        src/sprite.cpp
        src/object.cpp
        src/component-transform.cpp
        src/component-sprite.cpp
        src/component-keyboard-movement.cpp
        src/object-collection.cpp)
target_compile_features(game PRIVATE cxx_std_20)

# Add main executable
add_executable(pac-plus src/main.cpp)
target_compile_features(pac-plus PRIVATE cxx_std_20)

# Add test executable
file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(mainTests ${TEST_SOURCES})

# Find required packages
find_package(GTest CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

# Link libraries to game
target_link_libraries(game PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(game PRIVATE
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

# Link libraries to main
target_link_libraries(pac-plus PRIVATE game SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(pac-plus PRIVATE
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

# Link libraries to mainTests
target_link_libraries(mainTests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(mainTests PRIVATE game SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(mainTests PRIVATE
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

# Discover tests
include(GoogleTest)
gtest_discover_tests(mainTests)
