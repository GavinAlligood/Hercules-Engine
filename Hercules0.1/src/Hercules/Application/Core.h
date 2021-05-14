#pragma once

#ifdef HC_DEBUG
	#define HC_ENABLE_ASSERTS
#endif

#ifdef HC_ENABLE_ASSERTS
	#define HC_ASSERT(x, ...) { if (!(x)) { HC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HC_CORE_ASSERT(x, ...) { if (!(x)) { HC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HC_ASSERT(x, ...)
	#define HC_CORE_ASSERT(x, ...)
#endif