cmake_minimum_required(VERSION 3.16)
project(VastMiningSimulation VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Default to Debug build with symbols (use -DCMAKE_BUILD_TYPE=Release for optimized builds)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Main executable
file(GLOB SOURCES "src/*.cpp")
add_executable(VastMiningSimulation ${SOURCES})
target_include_directories(VastMiningSimulation PRIVATE include)

# Unit tests with Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(tests ${TEST_SOURCES}
  src/MiningTruck.cpp
  src/UnloadStation.cpp
  src/Simulation.cpp
)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests GTest::gtest_main)
add_test(NAME UnitTests COMMAND tests)
