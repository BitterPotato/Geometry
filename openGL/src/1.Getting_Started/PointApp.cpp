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
  glDrawArrays(GL_POINTS, START, SIZE);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {
  // static const char * vertexStr[] = 
  // {
  //     "#version 420 core                             \n"
  //     "                                              \n"
  //     "void main(void)                               \n"
  //     "{                                             \n"
  //     "    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);   \n"
  //     "}                                             \n"
  // };
  static const char * vertexStr[] = 
  {
      "#version 420 core                             \n"
      "                                              \n"
      "layout(location=0) in vec4 in_color;                             \n"
      "out vec4 out_color;                           \n"
      "                                              \n"
      "void main(void)                               \n"
      "{                                             \n"
      "    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);   \n"
      "    out_color = in_color;                       \n"
      "}                                             \n"
  };
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

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, ELEMENT_NUMBER, vertexStr, nullptr);
  glCompileShader(vertexShader);
  
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

  glPointSize(10.0f);
}

  // vertex
  // #version 330 core

  // void main(void) {
  //   gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
  // }

  // frag
  // #version 330 core 
  // out vec4 color;

  // void main(void) {
  //   color = vec4(0.0, 0.5, 0.5, 1.0);
  // }
