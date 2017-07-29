#include "glad/glad.h"
#include "PointApp.h"
#include "Utils.h"

#include <cmath>
#include <cstring>

#define glCheckError() util::glCheckError_(__FILE__, __LINE__) 

// app not work TODO:
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
  
  glCheckError();
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

  GLint unit_number;
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &unit_number);
  printf("the number of texture units:%d", unit_number);

  GLuint texture;
  glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &texture);
  glTextureStorage3D(texture, 8, GL_RGB8, width, height , 2);

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
  glTextureSubImage3D(texture, 0, 0, 0, 0, width, height, 1, GL_RGB, GL_FLOAT, data);

  float * data2 = new float[width * height * 3];
  
  for (y = 0; y < height; y++)
  {
      for (x = 0; x < width; x++)
      {
          data2[(y * width + x) * 3 + 0] = (float)((x & y) & 0xFF) / 255.0f;
          data2[(y * width + x) * 3 + 1] = (float)((x & y) & 0xFF) / 255.0f;
          data2[(y * width + x) * 3 + 2] = (float)((x & y) & 0xFF) / 255.0f;
      }
  }
  glTextureSubImage3D(texture, 0, 0, 0, 1, width, height, 1, GL_RGB, GL_FLOAT, data2);

  delete []data;
  delete []data2;
  // load ktx texture
  // util::loadTexture("openGL/textures/aliens.ktx", texture);

  // GLuint sampler;
  // glCreateSamplers(1, &sampler);
  // glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  // glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  // printf("current texture index: %d", texture);
  // // default texture unit is 0
  // glBindSampler(0, sampler);

  // explicitly bind the texture to a specific unit
  // graphic cards not supported
  // glBindTextureUnit(1, texture);
  // glBindSampler(1, sampler);
  
  glCheckError();

  GLint vertexShader = util::load("openGL/shaders/TexturePlayApp/vertex.glsl", GL_VERTEX_SHADER);
  GLint fragShader = util::load("openGL/shaders/TexturePlayApp/frag.glsl", GL_FRAGMENT_SHADER);
  
  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);
  glCheckError();

  glLinkProgram(mProgram);
  glCheckError();
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);

}
