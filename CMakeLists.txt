cmake_minimum_required (VERSION 2.6)
project (Graphics)
# The version number.
set (Graphics_VERSION_MAJOR 1)
set (Graphics_VERSION_MINOR 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(RUN_DIR ${PROJECT_SOURCE_DIR}/build)

# check c++11
include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "-std=c++11"   COMPILER_SUPPORTS_CXX11 )
if( COMPILER_SUPPORTS_CXX11 )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

# add binary dir to the search path
include_directories("${CMAKE_SOURCE_DIR}/include")

# 添加需要链接的库文件目录LINK_DIRECTORIES
link_directories("${CMAKE_SOURCE_DIR}/build")

add_subdirectory( openGL )