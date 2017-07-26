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
  // ===== render commands =====
  // set color
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glCheckError();
  // we only care about color values now
  glClear(GL_COLOR_BUFFER_BIT);
  
  glCheckError();
  glUseProgram(mProgram);
  glCheckError();

  const int START = 0;
  glDrawArrays(GL_PATCHES, START, SIZE);
  glCheckError();  
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
    "void main(void)                                   \n"
    "{                                                 \n"
    "    const vec4 vertices[3] = vec4[3](             \n"
    "        vec4(0.2f, 0.2f, 0.0f, 1.0f),             \n"
    "        vec4(-0.2f, -0.2f, 0.0f, 1.0f),           \n"
    "        vec4(0.2f, -0.2f, 0.0f, 1.0f)             \n"
    "    );                                            \n"
    "    const vec4 colors[3] = vec4[3](               \n"
    "        vec4(1.0f, 0.0f, 0.0f, 1.0f),             \n"
    "        vec4(0.0f, 1.0f, 0.0f, 1.0f),             \n"
    "        vec4(0.0f, 0.0f, 1.0f, 1.0f)              \n"
    "    );                                            \n"
    "    gl_Position = vertices[gl_VertexID];          \n"
    "}              \n"
  };
  static const char * teStr[] =
  {
    "#version 420 core                                 \n"
    "                                                  \n"
    "layout(vertices = 3) out;                          \n"
    "                                                  \n"
    "void main(void) {                                 \n"
    "    if(gl_InvocationID == 0) {                    \n"
    "        // tessellation factors                   \n"
    "        gl_TessLevelInner[0] = 5.0;               \n"
    "        gl_TessLevelOuter[0] = 5.0;               \n"
    "        gl_TessLevelOuter[1] = 5.0;               \n"
    "        gl_TessLevelOuter[2] = 5.0;               \n"
    "    }                                             \n"
    "    // control points                             \n"
    "    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"
    "}                                                 \n"
  };
  static const char * teeStr[] =
  {
    "#version 420 core                                 \n"
    "                                                  \n"
    "layout(triangles, equal_spacing, cw) in;          \n"
    "                                                  \n"
    "void main(void) {                                 \n"
    "    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) + (gl_TessCoord.y * gl_in[1].gl_Position) + (gl_TessCoord.z * gl_in[2].gl_Position);\n"
    "}                                                 \n"
  };
  static const char * geometryStr[] =
  {
    "#version 420 core                                 \n"
    "                                                  \n"
    "layout(triangles) in;                             \n"
    "layout(points, max_vertices = 3) out;             \n"
    "                                                  \n"
    "void main(void) {                                 \n"
    "    int i;                                        \n"
    "    for(i = 0; i < gl_in.length(); i++) {         \n"
    "        gl_Position = gl_in[i].gl_Position;       \n"
    "        EmitVertex();                             \n"
    "    }                                             \n"
    "}                                                 \n"
  };
  
  static const char * fragStr[] = 
  {
      "#version 420 core                             \n"
      "                                              \n"
      "out vec4 color;                               \n"
      "                                              \n"
      "void main(void)                               \n"
      "{                                             \n"
      "    color = vec4(0.2, 0.2, 0.2, 1.0);    \n"
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

  GLuint teShader = glCreateShader(GL_TESS_CONTROL_SHADER);
  glShaderSource(teShader, ELEMENT_NUMBER, teStr, nullptr);
  glCompileShader(teShader);

  GLuint teeShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
  glShaderSource(teeShader, ELEMENT_NUMBER, teeStr, nullptr);
  glCompileShader(teeShader);

  GLuint geoShader = glCreateShader(GL_GEOMETRY_SHADER);
  glShaderSource(geoShader, ELEMENT_NUMBER, geometryStr, nullptr);
  glCompileShader(geoShader);

  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragShader);
  glAttachShader(mProgram, teShader);
  glAttachShader(mProgram, teeShader);
  glAttachShader(mProgram, geoShader);  
  glCheckError();

  glLinkProgram(mProgram);
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  glGenVertexArrays(SIZE, &mVAO);
  glBindVertexArray(mVAO);
  glCheckError();

  glPatchParameteri(GL_PATCH_VERTICES, 3);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glCheckError();
}

  // vertex
  // #version 330 core

  // void main(void) {
  //   gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
  // }

  // frag
  // #version 330 core 
  // out vec4 color;

  // void main(void) {
  //   color = vec4(0.0, 0.5, 0.5, 1.0);
  // }
