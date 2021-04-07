cmake_minimum_required(VERSION 3.8.0)
project(foo)

set(LLVM_ENABLE_RTTI ON)
set(LLVM_ENABLE_EH ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

set(LIBSDIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# init exe
file(GLOB foo_SRC
        "${SRCDIR}/*.h"
        "${SRCDIR}/*.cpp"
		"${SRCDIR}/engine/Window/*.h"
		"${SRCDIR}/engine/Window/*.cpp"
        )
add_executable(foo ${foo_SRC})

# set output directory exe
if ( MSVC )
	set_target_properties(foo PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINDIR})
	set_target_properties(foo PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINDIR})
	set_target_properties(foo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINDIR})
else()
	set_target_properties(foo PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINDIR})
endif ( MSVC )

if(MSVC)
	set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "foo")
	set_target_properties(foo PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${BINDIR}")
endif(MSVC)

# add OpenGl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
if(WIN32)
	target_compile_options(foo PRIVATE /EHsc)
	target_link_libraries(foo ${OPENGL_LIBRARY})
else()
	target_link_libraries(foo GL)
endif()

# add source
target_include_directories(foo PUBLIC ${SRCDIR})

# add glfw
target_include_directories(foo PRIVATE ${LIBSDIR}/glfw/include)
add_subdirectory(${LIBSDIR}/glfw)
target_link_libraries(foo glfw)

# add GLEW
target_include_directories(foo PRIVATE ${LIBSDIR}/glew-cmake/include)
add_subdirectory(${LIBSDIR}/glew-cmake)
target_link_libraries(foo libglew_static)

# add freetype
target_include_directories(foo PRIVATE ${LIBSDIR}/freetype2/include)
add_subdirectory(${LIBSDIR}/freetype2)
target_link_libraries(foo freetype)

# add stb
target_include_directories(foo PRIVATE ${LIBSDIR}/stb)

# add glm
target_include_directories(foo PRIVATE ${LIBSDIR}/glm)
add_subdirectory(${LIBSDIR}/glm)

