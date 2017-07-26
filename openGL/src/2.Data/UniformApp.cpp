#include "glad/glad.h"
#include "PointApp.h"
#include "Utils.h"

#include <cmath>
#include <cstring>

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
  glCheckError();

  const int START = 0;
  glDrawArrays(GL_TRIANGLES, START, SIZE);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {

  // static const char * vertexStr[] = 
  // {
  //   "#version 420 core                                 \n"
  //   "                                                  \n"
  //   "void main(void)                                   \n"
  //   "{                                                 \n"
  //   "    const vec4 vertices[3] = vec4[3](             \n"
  //   "        vec4(0.2f, 0.2f, 0.0f, 1.0f),             \n"
  //   "        vec4(-0.2f, -0.2f, 0.0f, 1.0f),           \n"
  //   "        vec4(0.2f, -0.2f, 0.0f, 1.0f)             \n"
  //   "    );                                            \n"
  //   "    gl_Position = vertices[gl_VertexID];          \n"
  //   "}              \n"
  // };
  // static const char * fragStr[] = 
  // {
  //   "#version 420 core                                 \n"
  //   "                                                  \n"
  //   "uniform vec4 in_color;        \n"
  //   "                                                  \n"
  //   "out vec4 color;                                   \n"
  //   "                                                  \n"
  //   "void main(void) {                                 \n"
  //   "    color = in_color;                             \n"
  //   "}                                                 \n"
  // };

  glCheckError();
  // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // glShaderSource(vertexShader, ELEMENT_NUMBER, vertexStr, nullptr);
  // glCompileShader(vertexShader);
  GLuint vertexShader = util::load("openGL/shaders/UniformApp/vertex.glsl", GL_VERTEX_SHADER);
  glCheckError();
  
  GLuint fragShader = util::load("openGL/shaders/UniformApp/frag.glsl", GL_FRAGMENT_SHADER);
  printf("shader enum: %d", fragShader);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);

  glCheckError();

  glLinkProgram(mProgram);
  glGetError();
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  GLint location = glGetUniformLocation(mProgram, "in_color");
  printf("location:%d", location);
  
  // necessary
  glUseProgram(mProgram);

  GLfloat s_color[] = 
  {
    0.0f, 1.0f, 1.0f, 1.0f
  };

  // GLuint location = 0;
  glUniform4fv(location, 1, s_color);
  
  glCheckError();

  glCreateVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);

#ifdef WIN32
  printf("this is win platform");
#else
  printf("unix platform");
#endif
}
