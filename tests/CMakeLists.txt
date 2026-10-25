include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# Keep gtest from installing itself alongside the project
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(gbm_test gbm_test.cpp)
target_link_libraries(gbm_test PRIVATE mc_core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(gbm_test)
