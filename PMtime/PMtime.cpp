#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include "MyRenderWin.h"
#include "TimeApp.h"

// -------- main ---------

int
main(void)
{
  TimeApp program;
  program.Run();
  return 0;
}