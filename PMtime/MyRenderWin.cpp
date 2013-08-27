#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "MyRenderWin.h"
#include "Misc.h"


// CTOR, find out country specific information

MyRenderWin::MyRenderWin()
{
#define CURRENT_COUNTRY 0
#define NLS_CODEPAGE 0

  COUNTRYCODE Country;
  COUNTRYINFO CtryBuffer;
  ULONG       Length;
  APIRET      rc;

  Country.country = CURRENT_COUNTRY;
  Country.codepage = NLS_CODEPAGE;

  rc = DosQueryCtryInfo(sizeof(CtryBuffer), /* Length of data area provided */
                        &Country,           /* Input data structure */
                        &CtryBuffer,  /* Data area to be filled by function */
                        &Length);     /* Length of data returned */

  if (rc != 0)
    {
      timeFmt = '/';
    }
  else
    {
      timeFmt = CtryBuffer.fsTimeFmt;
    }
}


// DTOR

MyRenderWin::~MyRenderWin()
{
}


// This method takes care of repainting the application's
// window with the current time.

void MyRenderWin::paint(HWND& hwnd, HPS& hps, RECTL& rcl, MiniWin* win)
{
	hwnd;				// suppress warning

  time_t    timer;
  struct tm tblock;

  timer = time(0);
  tblock = *localtime(&timer);

  char string[2+1+2+1];

  switch (timeFmt)
    {
    case 0:   // 12 hour
      {
        int hour = tblock.tm_hour;
        if ((hour %= 12) == 0)
          hour = 12;

        sprintf(string, "%01d:%02d%c",
                hour,
                tblock.tm_min,
                tblock.tm_hour <= 12 ? 'a' : 'p');
        break;
      }
    case 1:   // 24 hour
      sprintf(string, "%02d:%02d", tblock.tm_hour, tblock.tm_min);
      break;
    default:
      strcpy(string, "?time?");
      break;
    }

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
}


// This method calculates the initial size of the application's
// window, and resizes it to this size.

void MyRenderWin::calcWinSize(MiniWin* win)
{
	char sampleString[64];

  switch (timeFmt)
    {
    case 0:   // 12 hour
      strcpy(sampleString, "77:77aI");
      break;
    case 1:   // 24 hour
      strcpy(sampleString, "77:77I");
      break;
    default:
      strcpy(sampleString, "?time?");
      break;
    }

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
