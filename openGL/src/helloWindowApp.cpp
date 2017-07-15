#include "mesa/GL/gl.h"
#include "include/Application.h"

class helloWindowApp : public Application {
public:
  helloWindowApp();
  void run(double timeMills) override;
};

helloWindowApp::helloWindowApp() {

}

void helloWindowApp::run(double timeMills) {
  // set color
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  // we only care about color values now
  glClear(GL_COLOR_BUFFER_BIT);
}
// DECLARE_MAIN(helloWindowApp_cpp)