#include "glad/glad.h"
#include "PointApp.h"
#include "Utils.h"

#include <cstdint>
#include <cmath>

#define glCheckError() util::glCheckError_(__FILE__, __LINE__) 
#define SIZE 1
#define ELEMENT_NUMBER 1
#define DRAW_NUMS 2;

void PointApp::startup() {
  Application::startup();

  // do nothing
  initShader();
}

typedef unsigned int uint;

typedef  struct {
    uint  count;
    uint  primCount;
    uint  first;
    uint  baseInstance;
} DrawArraysIndirectCommand;

void PointApp::run(double timeMills) {
  // ===== render commands =====

  // set color
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // we only care about color values now
  glClear(GL_COLOR_BUFFER_BIT);
  
  glUseProgram(mProgram);

  GLfloat fv_color[] = {
    (float)(sin(timeMills)*0.5f + 0.5f),
    (float)(cos(timeMills)*0.5f + 0.5f),
    1.0f,
    1.0f
  };
  // the first parameter corresponds to the loaction in the shader
  glVertexAttrib4fv(0, fv_color);

  const int START = 0;
  uint instanceCnt =  20;
  uint count = 1;
  uint first = 0;
  uint baseInstance = 0;

  // const DrawArraysIndirectCommand cmd = {count, instanceCnt, first, baseInstance};
  // // the following command will cause invalid_operation
  // glDrawArraysIndirect(GL_POINTS, &cmd);

  glCheckError();
  // glDrawArraysIndirect(GL_POINTS, nullptr);
  glMultiDrawArraysIndirect(GL_POINTS, nullptr, 2, 0);
  glCheckError();
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {
  static const char * fragStr[] = 
  {
      "#version 420 core                             \n"
      "                                              \n"
      "out vec4 color;                               \n"
      "in vec4 out_color;                            \n"
      "                                              \n"
      "void main(void)                               \n"
      "{                                             \n"
      "    color = out_color;    \n"
      "}                                             \n"
  };

  GLuint vertexShader = util::load("openGL/shaders/PointInstPriApp/vertex.glsl", GL_VERTEX_SHADER);
  
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, ELEMENT_NUMBER, fragStr, nullptr);
  glCompileShader(fragShader);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);
  glLinkProgram(mProgram);
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  glGenVertexArrays(SIZE, &mVAO);
  glBindVertexArray(mVAO);

  // glPointSize(10.0f);
  glEnable(GL_PROGRAM_POINT_SIZE);

  // generate indirect buffer
  GLuint indirectBuffer;
  glGenBuffers(1, &indirectBuffer);
  glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBuffer);
  // allocate
  glBufferData(GL_DRAW_INDIRECT_BUFFER, DRAW_NUMS*sizeof(DrawArraysIndirectCommand), nullptr, GL_STATIC_DRAW);
  DrawArraysIndirectCommand * cmd = (DrawArraysIndirectCommand *)glMapBufferRange(GL_DRAW_INDIRECT_BUFFER, 0, DRAW_NUMS*sizeof(DrawArraysIndirectCommand), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
  for(int i=0; i<DRAW_NUMS; i++) {
    cmd[i].count = 1;
    cmd[i].primCount = 20;
    cmd[i].first = 0;
    cmd[i].baseInstance = 0;
  }
  glUnmapBuffer(GL_DRAW_INDIRECT_BUFFER);

}
