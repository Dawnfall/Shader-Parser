#pragma once

#include <string>

namespace Constants
{
	inline const std::string SHADER_USE_KEYWORD = "#USE";

	inline const std::string SHADER_VERTEX_LAYOUT_KEYWORD = "_vertexLayout";
	inline const std::string SHADER_VERTEX_LAYOUT =
		R"(
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec3 aNormal; 
	layout(location = 2) in vec2 aUV;     
    )";

	inline const std::string SHADER_MVP_UNIFORM_BUFFER_KEYWORD = "_mvpBuffer";
	inline const std::string SHADER_MVP_UNIFORM_BUFFER =
		R"(
    layout(std140) uniform MVP_uniforms
	{
		mat4 uModel;
		mat4 uView;
		mat4 uProj;
	};
)";





}