#include "glad/glad.h"
#include "PointApp.h"
#include "GLFW/glfw3.h"

#include <cstdio>
#include <iostream>

// called each time  the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// void APIENTRY glDebugOutput(GLenum source, 
//                             GLenum type, 
//                             GLuint id, 
//                             GLenum severity, 
//                             GLsizei length, 
//                             const GLchar *message, 
//                             void *userParam)
// {
void APIENTRY glDebugOutput(unsigned int source, 
                            unsigned int type, 
                            unsigned int id, 
                            unsigned int severity, 
                            int length, 
                            const char *message, 
                            const void *userParam)
{
    // 忽略一些不重要的错误/警告代码
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

void processInput(GLFWwindow* window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  // TODO:always needs to modify there
  PointApp* app = new PointApp();
  // ExampleApplicaton* app;

  glfwInit();

  // [glfwWindowHint](http://www.glfw.org/docs/latest/window.html#window_hints)
  // user OpenGL version 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  // only use core openGL features
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // ========= 已停止工作 =========
  // set for debug(is slow)
  // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  // glDebugMessageControl(GL_DEBUG_SOURCE_API, 
  //                     GL_DEBUG_TYPE_ERROR, 
  //                     GL_DEBUG_SEVERITY_HIGH,
  //                     0, nullptr, GL_TRUE); 
  // GLint flags;
  // glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  // if(flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
  //   printf("the debug has been detected");
  //   glEnable(GL_DEBUG_OUTPUT);
  //   glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
  //   glDebugMessageCallback(glDebugOutput, nullptr);
  //   glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
  // }


  GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
  if(window == nullptr) {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // register callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  app->startup();

  while(!glfwWindowShouldClose(window)) {
    processInput(window);
    
    app->run(glfwGetTime());

    // Double buffer:
    // 1. the front buffer, contains the final output image that is shown at the screen;
    // 2. the back buffer, all the rendering commands draw to the back buffer.(output image is not drawn in an instant, but drawn pixel by pixel and usually from left to right and top to bottom.)
    // After all the rendering commands are finished, we swap the back buffer to the front buffer, so the image is instantly displayed to the user.
    glfwSwapBuffers(window);
    // checks if any events are triggered
    glfwPollEvents();
  }
  
  // app->shutdown();
  // clean/ delte all resources
  glfwTerminate();
  return 0;
}
