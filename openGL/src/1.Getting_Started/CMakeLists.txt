project( start )

add_executable(helloWindow helloWindow.cpp )

# 为target添加需要链接的(共享)库 (unuseful)
# target_link_libraries(glWindow ${COMMON_LIBS})