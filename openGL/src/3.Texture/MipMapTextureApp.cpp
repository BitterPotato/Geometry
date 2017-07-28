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
  util::loadTexture("openGL/textures/brick.ktx", texture);

  glGenerateTextureMipmap(texture);
  int w, h;
  int miplevel = 2;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
  printf("texturesize in level2 width:%d height:%d\n", w, h);

  glCheckError();
  GLint mipSize;
  GLint compressed;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &mipSize);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_COMPRESSED, &compressed);
  printf("texture in level 2 %s compressed.\nits size is %d\n", compressed?"is":"not",
  mipSize);

  // TODO: the last line shows the texture is not compressed...
  float *compressedData = new float[mipSize];
  glGetCompressedTexImage(GL_TEXTURE_2D, miplevel, compressedData);
  glCheckError();

  GLint vertexShader = util::load("openGL/shaders/SimpleTextureApp/vertex.glsl", GL_VERTEX_SHADER);
  GLint fragShader = util::load("openGL/shaders/SimpleTextureApp/frag.glsl", GL_FRAGMENT_SHADER);
  
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
