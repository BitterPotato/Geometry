cmake_minimum_required (VERSION 2.6)
project (openGL_Graphics)
# The version number.
set (openGL_VERSION_MAJOR 1)
set (openGL_VERSION_MINOR 0)

set(SOURCE_DIR src)

set(COMMON_LIBS glfw3 opengl32)

include_directories("${CMAKE_SOURCE_DIR}/include")

# 添加需要链接的库文件路径LINK_LIBRARIES
link_libraries(${COMMON_LIBS})

add_executable(Application ${CMAKE_SOURCE_DIR}/openGL/src/Application.cpp ${CMAKE_SOURCE_DIR}/openGL/src/Main.cpp )

# add_subdirectory( ${SOURCE_DIR}/1.Getting_Started )
# add_executable(Application ${CMAKE_SOURCE_DIR}/openGL/src/Application.cpp ${CMAKE_SOURCE_DIR}/openGL/src/helloWindowApp.cpp ${CMAKE_SOURCE_DIR}/openGL/src/Main.cpp )