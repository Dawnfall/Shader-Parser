#pragma once

#if defined(_WIN32)
	#if defined(SHADERPARSER_BUILD_DLL)
		#define SPARS_API __declspec(dllexport)
	#elif defined(SHADERPARSER_USE_DLL)
		#define SPARS_API __declspec(dllimport)
	#else
		#define SPARS_API
	#endif
#else
	#define SHADERPARSER_API
#endif