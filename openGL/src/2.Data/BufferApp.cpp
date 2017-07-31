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

  static const char * vertexStr[] = 
  {
    "#version 420 core                                 \n"
    "                                                  \n"
    "layout(location=0) in vec4 color;             \n"
    "out vec4 out_color;                               \n"
    "                                                  \n"
    "void main(void)                                   \n"
    "{                                                 \n"
    "    const vec4 vertices[3] = vec4[3](             \n"
    "        vec4(0.2f, 0.2f, 0.0f, 1.0f),             \n"
    "        vec4(-0.2f, -0.2f, 0.0f, 1.0f),           \n"
    "        vec4(0.2f, -0.2f, 0.0f, 1.0f)             \n"
    "    );                                            \n"
    "    gl_Position = vertices[gl_VertexID];          \n"
    "    out_color = color;                            \n"
    "}              \n"
  };
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
  static const char * computeStr[] = 
  {
      "#version 420 core                             \n"
      "                                              \n"
      "layout(local_size_x=32,local_size_y=32) in;  \n"
      "                                              \n"
      "void main(void)                               \n"
      "{                                             \n"
      "}                                             \n"
  };

  glCheckError();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, ELEMENT_NUMBER, vertexStr, nullptr);
  glCompileShader(vertexShader);
  glCheckError();
  
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, ELEMENT_NUMBER, fragStr, nullptr);
  glCompileShader(fragShader);

  GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
  glShaderSource(computeShader, ELEMENT_NUMBER, computeStr, nullptr);
  glCompileShader(computeShader);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);
  // Problem: if use compute shader, then display nothing...
  // glAttachShader(mProgram, computeShader);

  glCheckError();

  glLinkProgram(mProgram);
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  GLuint buffer;
  // how many buffer objects and buffer address
  glCreateBuffers(1, &buffer);
  // to store vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, buffer);

  static const float data[] =
  {
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f,  0.0f, 1.0f, 1.0f
  };
  // static const float data[] =
  // {
  //     1.0f, 0.0f, 0.0f, 1.0f,
  //     0.0f, 1.0f, 0.0f, 1.0f,
  //     0.0f,  0.0f, 1.0f, 1.0f
  // };
  
  // way 1. immutable
  // glBufferStorage(GL_ARRAY_BUFFER, sizeof(data), data, GL_MAP_WRITE_BIT);
  // nullptr only init data in the data
  // glBufferStorage(GL_ARRAY_BUFFER, sizeof(data), nullptr, GL_MAP_WRITE_BIT);
  // glNamedBufferStorage(buffer, sizeof(data), data, GL_MAP_WRITE_BIT); 
  

  // allocate(necessary for way2 and way3)
  glBufferData(GL_ARRAY_BUFFER, sizeof(data), nullptr, GL_STATIC_DRAW);
  // way 2. allocate data store and init
  // // offset and size
  // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data), data);
  // glNamedBufferSubData(buffer, 0, sizeof(data), data);
  
  // way 3.
  // void * ptr = glMapBuffer(GL_ARRAY_BUFFER, 0, sizeof(data), GL_WRITE_ONLY);
  // void * aptr = glNamedBuffer(buffer, GL_WRITE_ONLY);
  void * ptr = glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(data), GL_MAP_WRITE_BIT);
  memcpy(ptr, data, sizeof(data));
  glUnmapBuffer(GL_ARRAY_BUFFER);

  // ======== another test ========
  // create and bind vao to context, then we can use it
  glCreateVertexArrays(1, &mVAO);
  // not necessary be called here, but must be called
  glBindVertexArray(mVAO);

  // // layout index and buffer index
  // glVertexArrayAttribBinding(mVAO, 0, 0);
  // // bind index, buffer, offset, stride
  // glVertexArrayVertexBuffer(mVAO, 0, buffer, 0, 4);
  // // attri index, value's size, normalized, data offset in every vertex
  // glVertexArrayAttribFormat(mVAO, 0, 4, GL_FLOAT, GL_FALSE, 0);

  // alternative: affect the current bind vao
  glVertexAttribBinding(0, 0);
  // bind index, buffer, offset, stride
  glBindVertexBuffer(0, buffer, 0, 4);
  // attri index, value's size, normalized, data offset in every vertex
  glVertexAttribFormat( 0, 4, GL_FLOAT, GL_FALSE, 0);

  // layout index
  glEnableVertexArrayAttrib(mVAO, 0);
  


}
