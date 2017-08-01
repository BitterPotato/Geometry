#include "glad/glad.h"
#include "PointApp.h"
#include "Utils.h"

#include <cmath>

#define glCheckError() util::glCheckError_(__FILE__, __LINE__) 
#define SIZE 3
#define ELEMENT_NUMBER 1

// TODO: should be fixed based on PointInstPriApp
void PointApp::startup() {
  Application::startup();

  glDebugMessageCallback(&util::simple_print_callback, nullptr);

  // do nothing
  initShader();
}

void PointApp::run(double timeMills) {
  // ===== render commands =====
  // set color
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  // glCheckError();
  // we only care about color values now
  glClear(GL_COLOR_BUFFER_BIT);
  
  // glCheckError();
  glUseProgram(mProgram);
  // glCheckError();

  glBindVertexArray(mVAO);

  glEnable(GL_PROGRAM_POINT_SIZE);
  glPointSize(20.0f);
  glDrawArraysInstanced(GL_POINTS, 0, 1, 20);
  // glDrawArrays(GL_POINTS, 0, 1);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {

  glCheckError();
  GLuint vertexShader = util::load("openGL/shaders/PointInstApp/vertex.glsl", GL_VERTEX_SHADER);
  util::compileInfo(vertexShader);
  glCheckError();

  GLuint fragShader = util::load("openGL/shaders/VertexInputApp/frag.glsl", GL_FRAGMENT_SHADER);
  glCheckError();

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);


  glCheckError();

  glLinkProgram(mProgram);
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  GLfloat basecolor[] = {
    0.2f, 0.2f, 0.2f, 0.2f,
    0.2f, 0.2f, 0.4f, 0.4f,
    0.2f, 0.2f, 0.6f, 0.6f,
    0.2f, 0.2f, 0.8f, 0.8f,
    0.2f, 0.2f, 1.0f, 1.0f
  };
  glCheckError();
  GLuint basecolor_buffer;
  glGenBuffers(1, &basecolor_buffer);
  glCheckError();
  glBindBuffer(GL_TEXTURE_BUFFER, basecolor_buffer);
  glCheckError();
  glBufferData(GL_TEXTURE_BUFFER, sizeof(basecolor), nullptr, GL_STATIC_READ);
  glCheckError();
  glBufferSubData(GL_TEXTURE_BUFFER, 0, sizeof(basecolor), basecolor);
  glCheckError();

  GLuint basecolor_texture;
  glCreateTextures(GL_TEXTURE_BUFFER, 1, &basecolor_texture);
  glBindTexture(GL_TEXTURE_BUFFER, basecolor_texture);
  glCheckError();
  glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, basecolor_buffer);
  glCheckError();
  glBindImageTexture(0, basecolor_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
  glCheckError();

  GLuint alphacolor_texture;
  int width = 5;
  glCreateTextures(GL_TEXTURE_1D, 1, &alphacolor_texture);
  glBindTexture(GL_TEXTURE_1D, alphacolor_texture);
  glTexStorage1D(GL_TEXTURE_1D, 1, GL_RGBA32F, width);
  glTexSubImage1D(GL_TEXTURE_1D, 0, 0, width, GL_RGBA, GL_FLOAT, basecolor);
  glBindTextureUnit(1, alphacolor_texture);

  glCreateVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);


  glCheckError();
}