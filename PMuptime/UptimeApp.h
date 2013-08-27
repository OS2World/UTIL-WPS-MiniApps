#ifndef _UptimeApp_h
#define _UptimeApp_h

#include "MiniWin.h"
#include "MsgQueue.h"
#include "MyRenderWin.h"


// An object which handles the creation and running of the entire
// application.

class UptimeApp
{
public:
  UptimeApp();
  ~UptimeApp();
  void Run(void);

private:
  HAB         hab;
  MsgQueue*   queue;
  MiniWin*    appWin;
  MyRenderWin render;
};

#endif
