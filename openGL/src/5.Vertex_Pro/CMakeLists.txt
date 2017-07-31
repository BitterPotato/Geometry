project( start )

# TODO:modify the render script there
add_executable(Application ${PROJECT_SOURCE_DIR}/VertexInputApp.cpp)
target_link_libraries(Application libglfw3.a)
# target_link_libraries(${COMMON_LIBS})