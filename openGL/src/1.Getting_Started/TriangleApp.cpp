#include "glad/glad.h"
#include "PointApp.h"
#include "Utils.h"

#include <cmath>

#define glCheckError() util::glCheckError_(__FILE__, __LINE__) 
#define SIZE 3
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
  // glCheckError();
  // we only care about color values now
  glClear(GL_COLOR_BUFFER_BIT);
  
  // glCheckError();
  glUseProgram(mProgram);
  // glCheckError();

  const int START = 0;
  glDrawArrays(GL_TRIANGLES, START, SIZE);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {
  static const char * vertexStr[] = 
  {
    "#version 420 core                                 \n"
    "                                                  \n"
    "out vec4 out_color;                               \n"
    "                                                  \n"
    "void main(void)                                   \n"
    "{                                                 \n"
    "    const vec4 vertices[3] = vec4[3](             \n"
    "        vec4(0.2f, 0.2f, 0.0f, 1.0f),             \n"
    "        vec4(-0.2f, -0.2f, 0.0f, 1.0f),           \n"
    "        vec4(0.2f, -0.2f, 0.0f, 1.0f)             \n"
    "    );                                            \n"
    "    const vec4 colors[3] = vec4[3](               \n"
    "        vec4(1.0f, 0.0f, 0.0f, 1.0f),             \n"
    "        vec4(0.0f, 1.0f, 0.0f, 1.0f),             \n"
    "        vec4(0.0f, 0.0f, 1.0f, 1.0f)              \n"
    "    );                                            \n"
    "    gl_Position = vertices[gl_VertexID];          \n"
    "    out_color = colors[gl_VertexID];              \n"
    "}              \n"
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
  glCheckError();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, ELEMENT_NUMBER, vertexStr, nullptr);
  glCompileShader(vertexShader);
  glCheckError();
  
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, ELEMENT_NUMBER, fragStr, nullptr);
  glCompileShader(fragShader);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);
  glCheckError();

  glLinkProgram(mProgram);
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  glGenVertexArrays(SIZE, &mVAO);
  glBindVertexArray(mVAO);
  glCheckError();
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
