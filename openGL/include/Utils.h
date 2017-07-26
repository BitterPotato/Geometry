#ifndef UTILS_H
#define UTILS_H

#include "glad/glad.h"

#include <cstdio>
#include <string>

namespace util {
  GLenum glCheckError_(const char *file, int line)
  {
      GLenum errorCode;
      while ((errorCode = glGetError()) != GL_NO_ERROR)
      {
          std::string error;
          switch (errorCode)
          {
              case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
              case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
              case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
              case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
              case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
              case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
              case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
          }
          printf("%s | %s (%d)\n", error.c_str(), file, line);
      }
      return errorCode;
  }

  GLuint load(const char * filename, GLenum shader_type) {
    #define SHADER_FAILED 0
    #define CHECK_ERRORS false

    FILE * fp;
    size_t fileSize;
    char * data;

    fp = fopen(filename, "rb");
    if(!fp) {
        printf("cannot find file");
        return SHADER_FAILED;
    }

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    data = new char[fileSize + 1];
    if(!data)
        return SHADER_FAILED;

    fread(data, 1, fileSize, fp);
    data[fileSize] = 0;
    fclose(fp);

    GLuint shader = glCreateShader(shader_type);
    if(!shader)
        return SHADER_FAILED;
    
    glShaderSource(shader, 1, &data, nullptr);
    delete [] data;
    glCompileShader(shader);

    if(CHECK_ERRORS) {
        
    }

    return shader;
  }
}

#endif