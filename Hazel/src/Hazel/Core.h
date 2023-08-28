#pragma once

// This is the first file created, it mainly contains some 
// macros for further usage.

// Because dllimport and dllexport only exist in Windows
// so here set a if statement to check the platform
#ifdef HZ_PLATFORM_WINDOWS
	// Also check if want to build a dll or a .lib library
	#ifdef HZ_BUILD_DLL
		// If we are trying to build the dll, then export it.
		#define HAZEL_API __declspec(dllexport)
	#else
		// If we are not trying to build the dll, then it should be imported from another DLL.
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	// If no platforms are defined, report errors.
	#error Hazel only supprt Windows!
#endif

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { \
		if (!(x)) { \
			HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			__debugbreak(); \
		} \
	}
	#define HZ_CORE_ASSERT(x, ...) { \
		if (!(x)) { \
			HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			__debugbreak(); \
		} \
	}
#else 
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
