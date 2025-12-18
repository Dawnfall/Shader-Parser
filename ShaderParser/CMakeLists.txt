cmake_minimum_required(VERSION 3.20)
project(ShaderParser 
VERSION 0.1
LANGUAGES CXX)

# Create library
option(SHADERPARSER_BUILD_SHARED "Build ShaderParser as a shared library" OFF)

if(SHADERPARSER_BUILD_SHARED)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()

add_library(ShaderParser ${LIB_TYPE}
    src/ShaderParser.cpp
)

# Include headers
target_include_directories(ShaderParser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add this after creating your target
target_compile_options(ShaderParser
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>          # MSVC: warning level 4 + warnings as errors
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Werror>    # GCC
        $<$<CXX_COMPILER_ID:Clang>:-Wall -Werror>  # Clang
)

target_compile_features(ShaderParser PUBLIC cxx_std_20)
