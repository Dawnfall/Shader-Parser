cmake_minimum_required(VERSION 3.20)
project(ShaderParserProject)

# Let each subdirectory define its own targets.
add_subdirectory(ShaderParser)
add_subdirectory(Tests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ShaderParserTests)