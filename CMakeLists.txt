cmake_minimum_required(VERSION 3.16)
project(VastMiningSimulation VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Default to Debug build with symbols (use -DCMAKE_BUILD_TYPE=Release for optimized builds)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

file(GLOB SOURCES "src/*.cpp")
add_executable(VastMiningSimulation ${SOURCES})
target_include_directories(VastMiningSimulation PRIVATE include)
