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

  // only used by SeparateModeApp
  GLuint mProgram1;
  GLuint mProgram2;
  GLuint mPipeline;

  void initShader();
};

#endif