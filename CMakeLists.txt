cmake_minimum_required(VERSION 3.16)

project(sample_project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Helps VS Code IntelliSense understand the project
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(mc_core STATIC src/core/gbm.cpp)
target_include_directories(mc_core PUBLIC src/core)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE mc_core)

enable_testing()
add_subdirectory(tests)
add_subdirectory(benchmarks)
