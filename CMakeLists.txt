cmake_minimum_required(VERSION 3.16)
project(NaryTreeLab LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core INTERFACE)
target_include_directories(core INTERFACE ${CMAKE_SOURCE_DIR}/core)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
    tests/test_dynamic_array.cpp
)

target_link_libraries(tests PRIVATE core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)