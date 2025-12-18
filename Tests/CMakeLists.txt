cmake_minimum_required(VERSION 3.20)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(ShaderParserTests
    "src/test_main.cpp"
    "src/test_tokens.cpp" 
    "src/test_comments.cpp" 
    "src/test_groups.cpp"
)

 # Set C++ standard
set_target_properties(ShaderParserTests PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO

    # Force DLL and import library into a predictable folder
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
)

# Link test to library and GTest
target_link_libraries(ShaderParserTests
    PRIVATE
        ShaderParser   # CMake will resolve .lib automatically
        gtest
        gtest_main
)

# Optional: ensure C++23 standard
target_compile_features(ShaderParserTests PUBLIC cxx_std_23)

# Enable CTest integration
include(GoogleTest)
gtest_discover_tests(ShaderParserTests)
