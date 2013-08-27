#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include "DateApp.h"

// The name of the application

const char* appName = "PMdate";


// CTOR, creates application objects

DateApp::DateApp()
{
  hab = WinInitialize(0);
  queue = new MsgQueue(hab);
  appWin = new MiniWin(hab, &render);
}


// DTOR, winds the application down

DateApp::~DateApp()
{
  delete appWin;
  delete queue;
  WinTerminate(hab);
}


// This method runs the application until a WM_QUIT
// arrives in the thread's message queue.

void DateApp::Run(void)
{
  queue->Run();
}
