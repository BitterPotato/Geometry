#include "mesa/GL/gl.h"
#include "include/Application.h"

Application::Application() {

}

void Application::startup() {
  // do nothing
}

void Application::run(double timeMills) {
  // ===== render commands =====

    // set color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // we only care about color values now
    glClear(GL_COLOR_BUFFER_BIT);
}

void Application::shutdown() {

}