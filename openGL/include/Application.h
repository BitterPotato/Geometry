#ifndef APP_H
#define APP_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cstdio>

class Application {
public:
  Application() {}
  virtual ~Application() {}

  virtual void startup(){
    // init glad
    // this should be called after glfwMakeContextCurrent, else the GLAD will 
    // not be initialized
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      printf("Failed to initialize GLAD\n");
    }
  }
  virtual void run(double  timeMills){}
  virtual void shutdown(){}
};

#endif
