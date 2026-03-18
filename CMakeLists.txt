cmake_minimum_required(VERSION 3.16)
project(VastMiningSimulation VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")
add_executable(VastMiningSimulation ${SOURCES})
target_include_directories(VastMiningSimulation PRIVATE include)
