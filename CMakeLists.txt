cmake_minimum_required(VERSION 3.22)

project(template LANGUAGES CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(include)

add_executable(main src/main.cpp src/FPS.cpp src/LTexture.cpp src/LTimer.cpp src/Square.cpp
        src/SceneStateMachine.cpp
        src/SceneTest.cpp
        src/Game.cpp
        src/Font.cpp
        src/Sprite.cpp
        src/Object.cpp
        src/ComponentTransform.cpp
        src/ComponentSprite.cpp
        src/ComponentKeyboardMovement.cpp)
target_compile_features(main PRIVATE cxx_std_20)

add_library(lib STATIC src/lib.cpp)

add_executable(mainTests test/hello_test.cpp)

# Here to find package
find_package(GTest CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

# Here to link libraries
target_link_libraries(main PRIVATE lib)
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(
  main
  PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)

target_link_libraries(mainTests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
lib)

include(GoogleTest)
gtest_discover_tests(mainTests)
