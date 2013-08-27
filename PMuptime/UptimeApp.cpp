#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include "UptimeApp.h"


// The name of the application

const char* appName = "PMuptime";


// CTOR, creates application objects

UptimeApp::UptimeApp()
{
  hab = WinInitialize(0);
  queue = new MsgQueue(hab);
  appWin = new MiniWin(hab, &render);
}


// DTOR, winds the application down

UptimeApp::~UptimeApp()
{
  delete appWin;
  delete queue;
  WinTerminate(hab);
}


// This method runs the application until a WM_QUIT
// arrives in the thread's message queue.

void UptimeApp::Run(void)
{
  queue->Run();
}
