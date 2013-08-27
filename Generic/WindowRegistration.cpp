#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include "WindowRegistration.h"

WindowRegistration::WindowRegistration(HAB hab, PFNWP proc)
{
  if (registered == FALSE)
    {
      WinRegisterClass(hab,
                       windowClassName,
                       proc,
                       CS_SIZEREDRAW,
                       4);
      registered = TRUE;
    }
}

const PSZ WindowRegistration::windowClassName = (PSZ)"WinClass";
ULONG WindowRegistration::registered = 0;

