cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE SHADER_PARSER_SOURCES CONFIGURE_DEPENDS
    "*.cpp"
    "*.h"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SHADER_PARSER_SOURCES})

add_library(ShaderParser SHARED ${SHADER_PARSER_SOURCES})

set_target_properties(ShaderParser PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO

    OUTPUT_NAME "ShaderParser$<$<CONFIG:Debug>:_d>"
)

target_include_directories(ShaderParser PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(ShaderParser PRIVATE
    TWISTED_ENGINE
    $<$<CONFIG:Debug>:TWISTED_DEBUG>
    $<$<CONFIG:Release>:TWISTED_RELEASE>
    $<$<CONFIG:Deploy>:TWISTED_DEPLOY>
)

target_compile_options(ShaderParser PRIVATE
if (MSVC)
    $<$<CONFIG:Debug>:/Od /Zi>
    $<$<CONFIG:Release>:/Ox>
 endif()
)