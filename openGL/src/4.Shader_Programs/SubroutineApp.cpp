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

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);
  
  glUseProgram(mProgram);
  GLuint choice = 2;
  // TODO: seems not support
  glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &choice);

  const int START = 0;
  glDrawArrays(GL_TRIANGLES, START, SIZE);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {
  GLuint vertexShader = util::load("openGL/shaders/ShaderModeApp/vertex.glsl", GL_VERTEX_SHADER);
  GLuint fragRoutShader = util::load("openGL/shaders/ShaderModeApp/fragRout.glsl", GL_FRAGMENT_SHADER);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragRoutShader);
  glCheckError();

  glLinkProgram(mProgram); 
  glCheckError();

  // GLuint index;
  // index = glGetProgramResourceIndex(mProgram, GL_FRAGMENT_SUBROUTINE_UNIFORM, "getColor2");
  // printf("routine index %d\n", index);
  // int bufSize = 20;
  // GLsizei lengths[2];
  // char names[bufSize][2];
  // glGetProgramResourceName(mProgram, GL_UNIFORM, 1, bufSize, &lengths[0], names[0]);
  // glGetProgramResourceName(mProgram, GL_UNIFORM, 2, bufSize, &lengths[1], names[1]);

  
  glDeleteShader(vertexShader);
  glDeleteShader(fragRoutShader);

  glGenVertexArrays(SIZE, &mVAO);
  glBindVertexArray(mVAO);
  glCheckError();
}
