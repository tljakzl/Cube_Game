cmake_minimum_required(VERSION 3.14)
project(foo)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(LIBSDIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# init exe
file(GLOB foo_SRC
        "${SRCDIR}/*.h"
        "${SRCDIR}/*.cpp"
        )
add_executable(foo ${foo_SRC})


# add OpenGl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(foo GL)

# add glfw
target_include_directories(foo PRIVATE ${LIBSDIR}/glfw/include)
add_subdirectory(${LIBSDIR}/glfw)
target_link_libraries(foo glfw)

# add GLEW
target_include_directories(foo PRIVATE ${LIBSDIR}/glew-cmake/include)
add_subdirectory(${LIBSDIR}/glew-cmake)
target_link_libraries(foo GLEW)

# add freetype
target_include_directories(foo PRIVATE ${LIBSDIR}/freetype2/include)
add_subdirectory(${LIBSDIR}/freetype2)
target_link_libraries(foo freetype)

# add stb
target_include_directories(foo PRIVATE ${LIBSDIR}/stb)

# add glm
target_include_directories(foo PRIVATE ${LIBSDIR}/glm)
add_subdirectory(${LIBSDIR}/glm)

# set output directory exe
set_target_properties(foo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINDIR})
