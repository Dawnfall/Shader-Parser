cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE SHADER_PARSER_SOURCES CONFIGURE_DEPENDS
    "*.cpp"
    "*.h"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SHADER_PARSER_SOURCES})

# Create shared library
add_library(ShaderParser SHARED ${SHADER_PARSER_SOURCES})

# Set C++ standard
set_target_properties(ShaderParser PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO

    # Force DLL and import library into a predictable folder
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
)

# Include directories
target_include_directories(ShaderParser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Compile definitions
target_compile_definitions(ShaderParser PRIVATE
    SHADER_PARSER
    $<$<CONFIG:Debug>:SPARS_DEBUG>
    $<$<CONFIG:Release>:SPARS_RELEASE>
)

# MSVC-specific compile options
    target_compile_options(ShaderParser PRIVATE
        $<$<CONFIG:Debug>:/Od /Zi>
        $<$<CONFIG:Release>:/Ox>
    )
