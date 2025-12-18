#pragma once

#ifdef SHADER_PARSER
	#define SPARS_API __declspec(dllexport)
#else
	#define SPARS_API __declspec(dllimport)
#endif

