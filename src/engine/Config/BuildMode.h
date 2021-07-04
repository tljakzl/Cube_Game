#ifndef CORE_BUILD_MODE_H
#define CORE_BUILD_MODE_H

#define CORE_BUILD_PRODUCTION 0
#define CORE_BUILD_DEBUG 1
#define CORE_ASSERT_ENABLED !CORE_BUILD_PROD

#if CORE_BUILD_PRODUCTION && CORE_BUILD_DEBUG
    #error Debug mode not allowed in production build
#endif

#endif //CORE_BUILD_MODE_H
