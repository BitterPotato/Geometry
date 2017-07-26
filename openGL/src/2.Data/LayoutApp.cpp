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
  GLuint vertexShader = util::load("openGL/shaders/UniformApp/vertex.glsl", GL_VERTEX_SHADER);
  glCheckError();

  glCheckError();
  GLuint fragShader = util::load("openGL/shaders/LayoutApp/frag.glsl", GL_FRAGMENT_SHADER);
  printf("shader enum: %d", fragShader);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);

  glCheckError();

  glLinkProgram(mProgram);
  glGetError();
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);
  
  // necessary
  glUseProgram(mProgram);

  // ============ work out the shared layout param =================
  static const GLchar * uniformNames[4] =
  {
    "ColorBlock.alpha",
    "ColorBlock.rgb_color",
    "ColorBlock.trans_matrix",
    "ColorBlock.dummy"
  };
  GLuint uniformIndices[4];

  glGetUniformIndices(mProgram, 4, uniformNames, uniformIndices);
  
  GLint uniformOffsets[4];
  GLint arrayStrides[4];
  GLint matrixStrides[4];
  
  glGetActiveUniformsiv(mProgram, 4, uniformIndices, GL_UNIFORM_OFFSET, uniformOffsets);
  glGetActiveUniformsiv(mProgram, 4, uniformIndices, GL_UNIFORM_ARRAY_STRIDE, arrayStrides);
  glGetActiveUniformsiv(mProgram, 4, uniformIndices, GL_UNIFORM_MATRIX_STRIDE, matrixStrides);
  
  printf("uniform offsets: %d %d %d %d\n", uniformOffsets[0], uniformOffsets[1], uniformOffsets[2], uniformOffsets[3]);
  printf("array stride: %d\n", arrayStrides[3]);
  printf("matrix stride: %d\n", matrixStrides[2]);
  // ==================================================================

  GLfloat s_color[] = 
  {
    0.0f, 1.0f, 1.0f, 1.0f
  };

  GLint location = glGetUniformLocation(mProgram, "in_color");
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
