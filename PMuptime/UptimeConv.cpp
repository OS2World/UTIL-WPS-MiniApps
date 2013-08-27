#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include <stdio.h>

#include "UptimeConv.h"

char* UptimeConv::makeTitle()
{
  char* title = new char[256];

  ULONG uMins  = mins();
  ULONG uHours = hours();
  ULONG uDays  = days();

  sprintf(title,
          "Up %01u+%01u:%02u",
          uDays,
          uHours % 24,
          uMins % 60);

  return title;
}

