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

  const int START = 0;
  glDrawArrays(GL_TRIANGLES, START, SIZE);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {
  GLuint vertexShader = util::load("openGL/shaders/StatusApp/vertex.glsl", GL_VERTEX_SHADER);
  GLint vparams[4];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vparams[0]);
  glGetShaderiv(vertexShader, GL_SHADER_TYPE, &vparams[1]);
  glGetShaderiv(vertexShader, GL_SHADER_SOURCE_LENGTH, &vparams[2]);
  glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &vparams[3]);

  // ===== print =====
  printf("shader %s vertexShader\n", vparams[1]==GL_VERTEX_SHADER? "is":"is not");
  printf("shader compiled with %s\n", vparams[0]? "success":"failure");
  printf("shader source length is %d \n", vparams[2]);
  printf("shader log length is %d\n", vparams[3]);

  int logLength = vparams[3];
  if(logLength != 0) {
    char logInfo[logLength];
    // max length and length
    glGetShaderInfoLog(vertexShader, logLength*2, nullptr, logInfo);
    printf("log trace: %s", logInfo);
  }

  glCheckError();
  GLuint fragShader = util::load("openGL/shaders/StatusApp/frag.glsl", GL_FRAGMENT_SHADER);
  GLuint fragHelperShader = util::load("openGL/shaders/StatusApp/fragHelper.glsl", GL_FRAGMENT_SHADER);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);
  glAttachShader(mProgram, fragHelperShader);

  glCheckError();

  glLinkProgram(mProgram);

  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  glGenVertexArrays(SIZE, &mVAO);
  glBindVertexArray(mVAO);
  glCheckError();
}
