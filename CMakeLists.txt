cmake_minimum_required(VERSION 3.20)
project(gauss_solver LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 3.4 REQUIRED)
find_package(GTest   REQUIRED)       # <-- используем системный GTest

# ---------- библиотека -------------------------------------------------------
add_library(gauss src/gaussian.cpp)
target_include_directories(gauss PUBLIC include)
target_link_libraries(gauss PUBLIC Eigen3::Eigen)

# ---------- утилита решения ---------------------------------------------------
add_executable(solve src/main.cpp)
target_link_libraries(solve PRIVATE gauss)

# ---------- тесты ------------------------------------------------------------
enable_testing()
add_executable(tests tests/tests.cpp)
target_link_libraries(tests PRIVATE gauss GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)
