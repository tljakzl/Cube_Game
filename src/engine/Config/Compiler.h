#ifndef CORE_COMPILER_H
#define CORE_COMPILER_H

#include <boost/predef/compiler.h>

// Compiler
#define CORE_COMP_CLANG   BOOST_COMP_CLANG
#define CORE_COMP_MSVC    BOOST_COMP_MSVC
#define CORE_COMP_GCC     BOOST_COMP_GCC

#if defined(_MSC_VER)

    #undef CORE_COMP_MSVC
    #define CORE_COMP_MSVC 1

    #if defined(__clang__)
        #define CORE_COMP_MSVC_CLANG 1
        #define CORE_COMP_MSVC_CL 0
    #else
        #define CORE_COMP_MSVC_CLANG 0
        #define CORE_COMP_MSVC_CL 1
    #endif

#else

    #ifndef CORE_COMP_MSVC_CLANG
        #define CORE_COMP_MSVC_CLANG 0
    #endif

    #ifndef CORE_COMP_MSVC_CL
        #define CORE_COMP_MSVC_CL 0
    #endif

#endif


#if defined(PRODUCTION)
    #undef CORE_BUILD_PRODUCTION
	#define CORE_BUILD_PRODUCTION 1
#endif


#if CORE_COMP_MSVC

	#if defined(_DEBUG) && defined(NDEBUG)
		#error NDEBUG defined in debug configuration
	#endif

	#if !defined(_DEBUG) && !defined(NDEBUG)
		#error NDEBUG not defined in release configuration
	#endif

	#if !defined(_DEBUG)
		#undef CORE_BUILD_DEBUG
		#define CORE_BUILD_DEBUG 0
	#endif

#else

    #if defined(NDEBUG)
        #undef CORE_BUILD_DEBUG
        #define CORE_BUILD_DEBUG 0
    #endif

#endif

#endif //CORE_COMPILER_H
