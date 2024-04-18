cmake_minimum_required(VERSION 3.1.0)

project(main LANGUAGES CXX)

add_executable(main main.cpp)

# Here to find package

target_compile_features(main PRIVATE cxx_std_11)

# Here to link libraries
