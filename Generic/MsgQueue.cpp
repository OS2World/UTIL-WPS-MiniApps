#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include "MsgQueue.h"

void MsgQueue::Run(void)
{
  QMSG qMsg;

  while (WinGetMsg(hab, &qMsg, 0, 0, 0))
    WinDispatchMsg(hab, &qMsg);
}
