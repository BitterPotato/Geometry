cmake_minimum_required (VERSION 2.6)
project (openGL_Graphics)
# The version number.
set (openGL_VERSION_MAJOR 1)
set (openGL_VERSION_MINOR 0)

set(SOURCE_DIR src)

set(COMMON_LIBS glfw3)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")

# print include_directories property
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

# message( WARNING "$INCLUDE_DIRECTORIES" )
# 添加需要链接的库文件路径LINK_LIBRARIES
link_libraries(${COMMON_LIBS})

set(COMMON_CPPS ${PROJECT_SOURCE_DIR}/src/glad.c ${PROJECT_SOURCE_DIR}/src/Main.cpp)
# add_executable(Application ${COMMON_CPPS} ${PROJECT_SOURCE_DIR}/src/PointApp.cpp  )

add_subdirectory( ${SOURCE_DIR}/1.Getting_Started )