cmake_minimum_required(VERSION 3.20)

# Bring in GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(ShaderParserTests
    test_main.cpp
    test_shaderparser.cpp
)

target_link_libraries(ShaderParserTests
    PRIVATE
        ShaderParser
        gtest
        gtest_main
)

# Enable ctest
include(GoogleTest)
gtest_discover_tests(ShaderParserTests)