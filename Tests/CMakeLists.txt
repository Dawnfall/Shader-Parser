cmake_minimum_required(VERSION 3.20)
include(FetchContent)

# ---------------------------------
# GoogleTest
# ---------------------------------

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Prevent overriding parent compiler/linker settings (important!)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ---------------------------------
# Test executable
# ---------------------------------

add_executable(Tests)

target_sources(Tests PRIVATE
    src/test_main.cpp
    src/test_tokens.cpp
    src/test_comments.cpp
    src/test_groups.cpp
)

target_link_libraries(Tests PRIVATE
    ShaderParser
    GTest::gtest
    GTest::gtest_main
)

# ---------------------------------
# CTest integration
# ---------------------------------

include(GoogleTest)
gtest_discover_tests(Tests)
