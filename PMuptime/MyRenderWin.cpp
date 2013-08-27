#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "MyRenderWin.h"
#include "UptimeConv.h"
#include "Misc.h"


MyRenderWin::MyRenderWin()
{
}


// DTOR

MyRenderWin::~MyRenderWin()
{
}


// This method takes care of repainting the application's
// window with the current time.

void MyRenderWin::paint(HWND& hwnd, HPS& hps, RECTL& rcl, MiniWin* win)
{

	hwnd;			// supress warning
  UptimeConv uptime;
  char* string = uptime.makeTitle();

  rcl.xLeft--; rcl.yBottom++;
  WinDrawText(hps,
              strlen(string),
              (PSZ)string,
              &rcl,
              SYSCLR_BUTTONLIGHT,
              win->bgnd(),
              DT_CENTER | DT_VCENTER);
  rcl.xLeft++; rcl.yBottom--;
	WinDrawText(hps,
              strlen(string),
              (PSZ)string,
              &rcl,
              win->fgnd(),
              win->bgnd(),
							DT_CENTER | DT_VCENTER);

  delete [] string;
}


// This method calculates the initial size of the application's
// window, and resizes it to this size.

void MyRenderWin::calcWinSize(MiniWin* win)
{
	const char* sampleString = "Up 99+23:59W";
	const ULONG sampleLen = strlen(sampleString);

	HPS hps = WinGetPS(win->client());

	POINTL aptl[TXTBOX_COUNT];

	BOOL success = GpiQueryTextBox(hps,
																 sampleLen,
																 (PSZ)sampleString,
																 TXTBOX_COUNT,
																 aptl);

	ULONG x;
	ULONG y;

	if (success == TRUE)
		{
			ULONG hgt1 = Max(aptl[TXTBOX_TOPRIGHT].y, aptl[TXTBOX_TOPLEFT].y);
			ULONG hgt2 = Min(aptl[TXTBOX_BOTTOMRIGHT].y, aptl[TXTBOX_BOTTOMLEFT].y);
			ULONG wid1 = Max(aptl[TXTBOX_TOPRIGHT].x, aptl[TXTBOX_BOTTOMRIGHT].x);
			ULONG wid2 = Min(aptl[TXTBOX_TOPLEFT].x, aptl[TXTBOX_BOTTOMLEFT].x);

			x = wid1 - wid2;
      y = hgt1 - hgt2;
    }
  else
    {
      x = strlen(sampleString) * 12;
      y = 20;
    }

  WinReleasePS(hps);

  win->size(x + 6, y + 6);   // 2 border & 1 blank on each edge
}
