#ifndef POINT_APP_H
#define POINT_APP_H

#include "Application.h"

class PointApp : public Application {
public:
  // PointApp();

  void startup() override;

  void run(double timeMills) override;

  void shutdown() override;

private:
  GLuint mProgram;
  GLuint mVAO;

  // GLuint      square_buffer;
  // GLuint      square_vao;

  // GLuint      square_program;
  GLuint program_fans;
  GLuint mvp_loc_fans;
  GLuint vid_offset_loc_fans;

  void initShader();
};

#endif