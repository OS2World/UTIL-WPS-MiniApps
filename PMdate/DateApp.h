#ifndef _DateApp_h
#define _DateApp_h

#include "MiniWin.h"
#include "MsgQueue.h"
#include "MyRenderWin.h"


// An object which handles the creation and running of the entire
// application.

class DateApp
{
public:
  DateApp();
  ~DateApp();
  void Run(void);

private:
  HAB         hab;
  MsgQueue*   queue;
  MiniWin*    appWin;
  MyRenderWin render;
};

#endif
