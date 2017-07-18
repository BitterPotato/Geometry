#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <cstdio>

// called each time  the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height-100);
  
}

void processInput(GLFWwindow* window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
int main() {
  glfwInit();

  // [glfwWindowHint](http://www.glfw.org/docs/latest/window.html#window_hints)
  // user OpenGL version 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // only use core openGL features
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
  if(window == nullptr) {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // register callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while(!glfwWindowShouldClose(window)) {
    processInput(window);
    
    // ===== render commands =====

    // set color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // we only care about color values now
    glClear(GL_COLOR_BUFFER_BIT);

    // Double buffer:
    // 1. the front buffer, contains the final output image that is shown at the screen;
    // 2. the back buffer, all the rendering commands draw to the back buffer.(output image is not drawn in an instant, but drawn pixel by pixel and usually from left to right and top to bottom.)
    // After all the rendering commands are finished, we swap the back buffer to the front buffer, so the image is instantly displayed to the user.
    glfwSwapBuffers(window);
    // checks if any events are triggered
    glfwPollEvents();
  }
  
  // clean/ delte all resources
  glfwTerminate();
  return 0;
}