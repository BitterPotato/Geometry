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
  
  // glUseProgram(mProgram);
  glBindProgramPipeline(mPipeline);

  const int START = 0;
  glDrawArrays(GL_TRIANGLES, START, SIZE);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {
  GLuint vertexShader = util::load("openGL/shaders/ShaderModeApp/vertex.glsl", GL_VERTEX_SHADER);
  GLuint fragOneShader = util::load("openGL/shaders/ShaderModeApp/fragOne.glsl", GL_FRAGMENT_SHADER);
  GLuint fragTwoShader = util::load("openGL/shaders/ShaderModeApp/fragTwo.glsl", GL_FRAGMENT_SHADER);
  

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);

  mProgram1 = glCreateProgram();
  glAttachShader(mProgram, fragOneShader);

  mProgram2 = glCreateProgram();
  glAttachShader(mProgram, fragTwoShader);

  glCheckError();

  glProgramParameteri(mProgram, GL_PROGRAM_SEPARABLE, GL_TRUE);
  glProgramParameteri(mProgram1, GL_PROGRAM_SEPARABLE, GL_TRUE);
  glProgramParameteri(mProgram2, GL_PROGRAM_SEPARABLE, GL_TRUE);  
  glLinkProgram(mProgram);
  glLinkProgram(mProgram1);
  glLinkProgram(mProgram2);  
  glCheckError();

  glGenProgramPipelines(1, &mPipeline);
  glCheckError();

  bool useFirst = true;
  glUseProgramStages(mPipeline, GL_VERTEX_SHADER_BIT, mProgram);
  glCheckError();
  if(useFirst)
    glUseProgramStages(mPipeline, GL_FRAGMENT_SHADER_BIT, mProgram1);
  else
    glUseProgramStages(mPipeline, GL_FRAGMENT_SHADER_BIT, mProgram2);
  glCheckError();
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragOneShader);
  glDeleteShader(fragTwoShader);  

  glGenVertexArrays(SIZE, &mVAO);
  glBindVertexArray(mVAO);
  glCheckError();
}
