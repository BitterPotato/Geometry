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
  GLint width = 256;
  GLint height = 256;

  GLuint texture;
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glCheckError();
  glBindTexture(GL_TEXTURE_2D, texture);
  glCheckError();
  glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGB8, width, height);

  // glCheckError();
  // // 1. use clear
  // // float * data = new float[3]{1.0f, 1.0f, 0.0f};
  // // glClearTexSubImage(texture, 0, 0, 0, 1, width, height, 1, GL_RGB, GL_FLOAT, data);

  // 2. use subImage
  float * data = new float[width * height * 3];
  
  int x, y;
  for (y = 0; y < height; y++)
  {
      for (x = 0; x < width; x++)
      {
          data[(y * width + x) * 3 + 0] = (float)((x ^ y) & 0xFF) / 255.0f;
          data[(y * width + x) * 3 + 1] = (float)((x | y) & 0xFF) / 255.0f;
          data[(y * width + x) * 3 + 2] = (float)((x & y) & 0xFF) / 255.0f;
      }
  }
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_FLOAT, data);
  
  glCheckError();
  delete []data;
  
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
