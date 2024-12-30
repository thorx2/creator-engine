cmake_minimum_required(VERSION 3.15)
project(MyGameProject)

set(USE_DIRECTX OFF)
set(USE_VULCAN OFF)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(engine)
add_subdirectory(game)
