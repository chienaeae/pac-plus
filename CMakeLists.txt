cmake_minimum_required(VERSION 3.22)

project(main LANGUAGES CXX)

# Here to find package
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

include_directories(include)

add_executable(main src/main.cpp src/FPS.cpp src/LTexture.cpp src/LTimer.cpp src/Square.cpp
        src/SceneStateMachine.cpp
        src/SceneTest.cpp
        src/Game.cpp)

target_compile_features(main PRIVATE cxx_std_20)

# Here to link libraries
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(
  main
  PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)
