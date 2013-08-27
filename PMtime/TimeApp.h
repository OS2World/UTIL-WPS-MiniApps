#ifndef _TimeApp_h
#define _TimeApp_h

#include "MiniWin.h"
#include "MsgQueue.h"
#include "MyRenderWin.h"


// An object which handles the creation and running of the entire
// application.

class TimeApp
{
public:
  TimeApp();
  ~TimeApp();
  void Run(void);

private:
  HAB         hab;
  MsgQueue*   queue;
  MiniWin*    appWin;
  MyRenderWin render;
};

#endif
