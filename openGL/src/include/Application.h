#ifndef APP_H
#define APP_H

class Application {
public:
  Application();
  ~Application();

  virtual void startup();
  virtual void run(double  timeMills);
  virtual void shutdown();

};

#endif
