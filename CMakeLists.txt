cmake_minimum_required(VERSION 3.22)

project(pac-plus LANGUAGES CXX)

# Generate compile_commands.json for analysis tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The CMAKE_CXX_FLAGS_DEBUG is a string that holds the flags for the c++ compiler when the system is in debug mode.
# The -fsanitize=address flag enables AddressSanitizer, it is a memory error detector for C++
# The -fno-omit-frame-pointer flag disables omission of the frame pointer (sometimes needed for debugging)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")

# CMAKE_LINKER_FLAGS_DEBUG is a string to hold the flags for the linker when the system is in debug mode.
# The -fsanitize=address flag for the linker again, enables the AddressSanitizer
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")

# Enable testing
enable_testing()

# Include headers directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external/rapidxml)

# Add game library
add_library(game STATIC
        src/game/window.cpp
        src/game/fps.cpp
        src/game/texture.cpp
        src/game/animation.cpp
        src/game/timer.cpp
        src/game/scene-state-machine.cpp
        src/game/game.cpp
        src/game/font.cpp
        src/game/sprite.cpp
        src/game/object.cpp
        src/game/component-transform.cpp
        src/game/component-sprite.cpp
        src/game/component-animation.cpp
        src/game/component-keyboard-movement.cpp
        src/game/object-collection.cpp)
target_compile_features(game PRIVATE cxx_std_20)

# Add main executable
add_executable(pac-plus src/main.cpp src/pac-plus.cpp src/scene-test.cpp src/square.cpp)
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
