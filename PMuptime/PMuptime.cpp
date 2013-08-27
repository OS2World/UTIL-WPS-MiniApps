#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include "MyRenderWin.h"
#include "UptimeApp.h"

// -------- main ---------

int
main(void)
{
  UptimeApp program;
  program.Run();
  return 0;
}