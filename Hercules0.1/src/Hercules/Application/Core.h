#pragma once

#ifdef  HC_PLATFORM_WINDOWS
	#ifdef HC_BUILD_DLL
		#define HERCULES_API __declspec(dllexport)
	#else
		#define HERCULES_API __declspec(dllimport)
	#endif // /HC_BUILD_DLL
#else
	#error Hercules currently only supports Windows
#endif //  HC_PLATFORM_WINDOWS

#ifdef HC_ENABLE_ASSERTS
	#define HC_ASSERT(x, ...) { if (!(x)) { HC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HC_CORE_ASSERT(x, ...) { if (!(x)) { HC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HC_ASSERT(x, ...)
	#define HC_CORE_ASSERT(x, ...)
#endif