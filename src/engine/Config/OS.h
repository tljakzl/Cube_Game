#ifndef CORE_OS_H
#define CORE_OS_H

#include <boost/predef/os.h>
#include <boost/predef/platform.h>

// Operating System
#define CORE_OS_WINDOWS           BOOST_OS_WINDOWS
#define CORE_OS_LINUX             BOOST_OS_LINUX
#define CORE_OS_MACOS             BOOST_OS_MACOS
#define CORE_OS_IOS               BOOST_OS_IOS
#define CORE_OS_ANDROID           BOOST_PLAT_ANDROID
#define CORE_OS_WINDOWS_DESKTOP   BOOST_PLAT_WINDOWS_DESKTOP

#if CORE_OS_ANDROID && CORE_OS_LINUX
    #undef CORE_OS_LINUX
	#define CORE_OS_LINUX 0
#endif

// Platform
#define CORE_PLAT_DESKTOP 0

#if CORE_OS_WINDOWS_DESKTOP || CORE_OS_MACOS || CORE_OS_LINUX
    #undef CORE_PLAT_DESKTOP
	#define CORE_PLAT_DESKTOP 1
#endif

#endif //CORE_OS_H
