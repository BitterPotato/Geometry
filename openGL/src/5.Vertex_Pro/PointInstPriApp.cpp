#include "glad/glad.h"
#include "PointApp.h"
#include "Utils.h"

#include <cmath>

#define glCheckError() util::glCheckError_(__FILE__, __LINE__) 
#define SIZE 1
#define ELEMENT_NUMBER 1

void PointApp::startup() {
  Application::startup();

  // do nothing
  initShader();
}

void PointApp::run(double timeMills) {
  // ===== render commands =====

  // set color
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // we only care about color values now
  glClear(GL_COLOR_BUFFER_BIT);
  
  glUseProgram(mProgram);

  GLfloat fv_color[] = {
    (float)(sin(timeMills)*0.5f + 0.5f),
    (float)(cos(timeMills)*0.5f + 0.5f),
    1.0f,
    1.0f
  };
  // the first parameter corresponds to the loaction in the shader
  glVertexAttrib4fv(0, fv_color);

  const int START = 0;
  int instanceCnt =  20;
  // glDrawArraysInstanced(GL_POINTS, 0, 1, instanceCnt);
  glDrawArraysInstancedBaseInstance(GL_POINTS, 0, 1, instanceCnt, 0);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {
  static const char * fragStr[] = 
  {
      "#version 420 core                             \n"
      "                                              \n"
      "out vec4 color;                               \n"
      "in vec4 out_color;                            \n"
      "                                              \n"
      "void main(void)                               \n"
      "{                                             \n"
      "    color = out_color;    \n"
      "}                                             \n"
  };

  GLuint vertexShader = util::load("openGL/shaders/PointInstPriApp/vertex.glsl", GL_VERTEX_SHADER);
  
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, ELEMENT_NUMBER, fragStr, nullptr);
  glCompileShader(fragShader);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);
  glLinkProgram(mProgram);
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  glGenVertexArrays(SIZE, &mVAO);
  glBindVertexArray(mVAO);

  // glPointSize(10.0f);
  glEnable(GL_PROGRAM_POINT_SIZE);
}