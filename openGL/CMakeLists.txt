cmake_minimum_required (VERSION 2.6)
project (openGL_Graphics)
# The version number.
set (openGL_VERSION_MAJOR 1)
set (openGL_VERSION_MINOR 0)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")

add_library(utils ${PROJECT_SOURCE_DIR}/src/glad.c ${PROJECT_SOURCE_DIR}/src/Main.cpp)
set(COMMON_LIBS utils)

# print include_directories property
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

# message( WARNING "$INCLUDE_DIRECTORIES" )
# 添加需要链接的库文件路径LINK_LIBRARIES
link_libraries(${COMMON_LIBS})


# add_executable(Application ${COMMON_CPPS} ${PROJECT_SOURCE_DIR}/src/PointApp.cpp  )

set(SOURCE_DIR src)
# add_subdirectory( ${SOURCE_DIR}/1.Getting_Started )
# add_subdirectory( ${SOURCE_DIR}/2.Data)
# add_subdirectory(${SOURCE_DIR}/3.Texture)
# add_subdirectory(${SOURCE_DIR}/4.Shader_Programs)
add_subdirectory(${SOURCE_DIR}/5.Vertex_Pro)