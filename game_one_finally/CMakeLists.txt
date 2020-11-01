cmake_minimum_required(VERSION 3.14)
project(foo)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

file(GLOB foo_SRC
        "*.h"
        "*.cpp"
        )
add_executable(foo ${foo_SRC})
target_include_directories(foo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/freetype2/include)

target_link_libraries(foo GLEW)
target_link_libraries(foo glfw)
target_link_libraries(foo GL)
target_link_libraries(foo freetype)
set_target_properties( foo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
