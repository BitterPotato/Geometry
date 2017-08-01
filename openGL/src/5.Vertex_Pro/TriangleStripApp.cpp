#include "glad/glad.h"
#include "PointApp.h"
#include "Utils.h"

#include <cmath>

#define glCheckError() util::glCheckError_(__FILE__, __LINE__) 
#define SIZE 3
#define ELEMENT_NUMBER 1

typedef struct Vertex_t {
  GLfloat position[4];
  GLubyte color[3];
} Vertex;

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
  // glCheckError();

  const int START = 0;
  glDrawElements(GL_TRIANGLE_STRIP, 9, GL_UNSIGNED_SHORT, 0);
  // Mode: PRIMITIVE_RESTART
  // glDrawElements(GL_TRIANGLE, 9, GL_UNSIGNED_SHORT, 0);
  
}

void PointApp::shutdown() {
  glDeleteProgram(mProgram);
  glDeleteVertexArrays(SIZE, &mVAO);
}

void PointApp::initShader() {

  glCheckError();
  GLuint vertexShader = util::load("openGL/shaders/VertexInputApp/vertex.glsl", GL_VERTEX_SHADER);
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

  // generate data
  Vertex_t vertexes[6];
  vertexes[0] = {-0.8f, 0.2f, 0.0f, 1.0f, 255, 0, 0};
  vertexes[1] = {-0.5f, -0.2f, 0.0f, 1.0f, 0, 255, 0};
  vertexes[2] = {-0.2f, 0.2f, 0.0f, 1.0f, 0, 0, 255};
  vertexes[3] = {0.1f, -0.2f, 0.0f, 1.0f, 255, 0, 0};
  vertexes[4] = {0.4f, 0.2f, 0.0f, 1.0f, 0, 255, 0};
  vertexes[5] = {0.7f, -0.2f, 0.0f, 1.0f, 0, 0,255};
  // printf("test Data: %.1f %d\n", vertexes[0].position[0], vertexes[0].color[0]);

  GLuint buffer;
  glCreateBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), nullptr, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexes), vertexes);

  glGenVertexArrays(SIZE, &mVAO);
  glBindVertexArray(mVAO);

  glVertexAttribFormat(0, 4, GL_FLOAT, GL_FALSE, 0);
  glVertexAttribFormat(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0);
  
  glVertexAttribBinding(0, 0);
  glVertexAttribBinding(1, 1);
  glBindVertexBuffer(0, buffer, 0, sizeof(Vertex_t));
  glBindVertexBuffer(1, buffer, sizeof(GLfloat)*4, sizeof(Vertex_t));
  
  // enable Vao for attributes
  glEnableVertexArrayAttrib(mVAO, 0);
  glEnableVertexArrayAttrib(mVAO, 1);  

  GLushort vertex_indice[] {
    0, 1, 2,
    2, 3, 4,
    3, 4, 5
  };
  //bind vertex indices
  GLuint index_buffer;
  glCreateBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indice), vertex_indice, GL_STATIC_DRAW);

  // Mode: PRIMITIVE_RESTART
  // const GLushort INDICE_MAX = 0xFFF;
  // GLushort vertex_indice_alt[] {
  //   0, 1, 2, INDICE_MAX, 2, 3, 4, 5, INDICE_MAX
  // };
  // // bind vertex indices
  // GLuint index_buffer;
  // glCreateBuffers(1, &index_buffer);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indice_alt), vertex_indice_alt, GL_STATIC_DRAW);
  // glEnable(GL_PRIMITIVE_RESTART);
  // glCheckError();
  // glPrimitiveRestartIndex(INDICE_MAX);

  glCheckError();
}