#include "glad/glad.h"
#include "PointApp.h"
#include "Utils.h"

#include <cmath>
#include <cstring>

#define glCheckError() util::glCheckError_(__FILE__, __LINE__) 

void PointApp::startup() {
  Application::startup();

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

  glDrawArrays(GL_TRIANGLES, 0, 3);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(1, &mVAO);
}

void PointApp::initShader() {

  GLuint texture;
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);

  GLuint sampler;
  glCreateSamplers(1, &sampler);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  printf("current texture index: %d", texture);
  // default texture unit is 0
  glBindSampler(0, sampler);
  
  // load ktx texture
  util::loadTexture("openGL/textures/brick.ktx", texture);

  glCheckError();

  GLint vertexShader = util::load("openGL/shaders/ComplexTextureApp/vertex.glsl", GL_VERTEX_SHADER);
  GLint fragShader = util::load("openGL/shaders/ComplexTextureApp/frag.glsl", GL_FRAGMENT_SHADER);
  
  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);
  glCheckError();

  glLinkProgram(mProgram);
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);

}
