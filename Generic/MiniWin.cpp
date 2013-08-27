#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include <string.h>

#include "MiniWin.h"
#include "Resource.h"


extern const char* appName;
const char* WinXposKey  = "Window X pos";
const char* WinYposKey  = "Window Y pos";
const char* textFontKey = "Text Font";
const char* timerIntKey = "Timer Interval";
const char* textColKey  = "Text Colour";
const char* backColKey  = "Background Colour";
const char* floatKey		= "Float Window";
const ULONG timerID = 0;


MiniWin::MiniWin(HAB hab, RenderWin* app) : appObj(app), Window(hab)
{
  myHab = hab;

	WinSetWindowULong(client(), QWL_USER, (ULONG)this);
  loadConfig();

	setTimer();
  appObj->calcWinSize(this);

	SWCNTRL sw;
	sw.hwnd           = frame();
	sw.hwndIcon       = 0;
  sw.hprog          = 0;
  sw.idProcess      = 0;
  sw.idSession      = 0;
	sw.uchVisibility  = SWL_VISIBLE;
  sw.fbJump         = SWL_JUMPABLE;
  sw.bProgType      = PROG_PM;
  strcpy(sw.szSwtitle, appName);
	switchEntry = WinAddSwitchEntry(&sw);
}


MiniWin::~MiniWin()
{
	WinRemoveSwitchEntry(switchEntry);

	stopTimer();

  SWP pos;
	WinQueryWindowPos(frame(), &pos);

	PrfWriteProfileData(HINI_USERPROFILE,
                      (PSZ)appName,
                      (PSZ)WinXposKey,
                      &(pos.x),
                      sizeof(pos.x));

  PrfWriteProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)WinYposKey,
											&(pos.y),
											sizeof(pos.y));

	PrfWriteProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)textColKey,
											&textCol,
											sizeof(textCol));

	PrfWriteProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)backColKey,
											&backCol,
											sizeof(backCol));

	PrfWriteProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)timerIntKey,
											&timerInt,
											sizeof(timerInt));

	PrfWriteProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)floatKey,
											&iFloatWindow,
											sizeof(iFloatWindow));
}

void
DrawBox(HPS hps, RECTL rcl)
{
	POINTL  p;

  GpiSetColor(hps, SYSCLR_BUTTONLIGHT);
  p.x=rcl.xLeft;    p.y = rcl.yBottom; GpiMove(hps, &p);
  p.x=rcl.xLeft;    p.y = rcl.yTop-1;  GpiLine(hps, &p);
	p.x=rcl.xRight-1; p.y = rcl.yTop-1;  GpiLine(hps, &p);
  GpiSetColor(hps, SYSCLR_BUTTONDARK);
  p.x=rcl.xRight-1; p.y = rcl.yBottom; GpiLine(hps, &p);
	p.x=rcl.xLeft+1;  p.y = rcl.yBottom; GpiLine(hps, &p);

	rcl.xLeft++; rcl.xRight--;
  rcl.yBottom++; rcl.yTop--;

  GpiSetColor(hps, SYSCLR_BUTTONLIGHT);
  p.x=rcl.xLeft;    p.y = rcl.yBottom; GpiMove(hps, &p);
	p.x=rcl.xLeft;    p.y = rcl.yTop-1;  GpiLine(hps, &p);
	p.x=rcl.xRight-1; p.y = rcl.yTop-1;  GpiLine(hps, &p);
	GpiSetColor(hps, SYSCLR_BUTTONDARK);
	p.x=rcl.xRight-1; p.y = rcl.yBottom; GpiLine(hps, &p);
	p.x=rcl.xLeft+1;  p.y = rcl.yBottom; GpiLine(hps, &p);
}

void MiniWin::loadConfig()
{
	LONG x = 32;
	LONG y = 32;

	ULONG len = sizeof(x);
	PrfQueryProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)WinXposKey,
											&x,
											&len);

	len = sizeof(y);
	PrfQueryProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)WinYposKey,
											&y,
											&len);

	WinSetWindowPos(frame(), HWND_TOP, x, y, 0, 0, SWP_MOVE | SWP_ZORDER);

	timerInt = 30 * 1000;

	len = sizeof(timerInt);
	PrfQueryProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)timerIntKey,
											&timerInt,
											&len);

	const ULONG fontNameLen = 128;
	char fontName[fontNameLen];

	PrfQueryProfileString(HINI_USERPROFILE,
												(PSZ)appName,
												(PSZ)textFontKey,
												(PSZ)"8.Helv",
                        fontName,
												fontNameLen);

	WinSetPresParam(client(),
									PP_FONTNAMESIZE,
									strlen(fontName)+1,
									(PVOID)fontName);

	textCol = CLR_BLACK;
	backCol = SYSCLR_DIALOGBACKGROUND;

	len = sizeof(textCol);
	PrfQueryProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)textColKey,
											&textCol,
											&len);

	len = sizeof(backCol);
	PrfQueryProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)backColKey,
											&backCol,
											&len);

	iFloatWindow = 0;
	len = sizeof(iFloatWindow);
	PrfQueryProfileData(HINI_USERPROFILE,
											(PSZ)appName,
											(PSZ)floatKey,
											&iFloatWindow,
											&len);}

void MiniWin::PresParamChanged(HWND hwnd, LONG lPP)
{
	// update configuration info to reflect a font
	// or colour change (done by a drag and drop operation)

	switch (lPP)
	{
		case PP_FONTNAMESIZE:
		{
			const ULONG nameLen = 128;
			char fontName[nameLen];
			ULONG found;

			WinQueryPresParam(hwnd,
												PP_FONTNAMESIZE,
												0,
												&found,
												nameLen,
												(PVOID)fontName,
												QPF_NOINHERIT);

			PrfWriteProfileString(HINI_USERPROFILE,
														(PSZ)appName,
														(PSZ)textFontKey,
														(PSZ)fontName);

			appObj->calcWinSize(this);
			break;
		}

		case PP_FOREGROUNDCOLOR:
		{
			LONG lrgb;
			ULONG AttrFound;

			WinQueryPresParam(hwnd,
												PP_FOREGROUNDCOLOR,
												0,
												&AttrFound,
												sizeof(lrgb),
												&lrgb,
												0);

			setFgnd(lrgb);

			WinInvalidateRect(hwnd, 0, TRUE);
			break;
		}

		case PP_BACKGROUNDCOLOR:
		{
			LONG lrgb;
			ULONG AttrFound;

			WinQueryPresParam(hwnd,
												PP_BACKGROUNDCOLOR,
												0,
												&AttrFound,
												sizeof(lrgb),
												&lrgb,
												0);

			setBgnd(lrgb);

			WinInvalidateRect(hwnd, 0, TRUE);
			break;
		}
	}
}

void MiniWin::PopupMenu(int x, int y)
{
	HWND hwndPopup = WinLoadMenu(client(), 0L, IDW_POPUP);

	WinSetPresParam(hwndPopup,
									PP_FONTNAMESIZE,
									strlen("8.Helv")+1,
									(PVOID)"8.Helv");

	USHORT  usOpts = PU_KEYBOARD | PU_VCONSTRAIN |
									 PU_HCONSTRAIN | PU_MOUSEBUTTON2 | PU_MOUSEBUTTON1;

	WinSendMsg(hwndPopup, MM_SETITEMATTR,
						 MPFROM2SHORT(IDM_POPUP_FLOAT, TRUE),
						 MPFROM2SHORT(MIA_CHECKED, iFloatWindow ? MIA_CHECKED : 0));
	WinPopupMenu(client(), client(), hwndPopup, x, y, IDM_POPUP_FLOAT, usOpts);
}

void MiniWin::ProcessCommand(MPARAM mp1, MPARAM)
{
	// process a menu command
	switch(USHORT(mp1))
	{
		case IDM_POPUP_FLOAT:
		{
			iFloatWindow = !iFloatWindow;
			break;
		}

		case IDM_POPUP_ABOUT:
		{
			WinDlgBox(HWND_DESKTOP, client(), WinDefDlgProc, 0, IDD_ABOUT, 0);
			break;
		}

		case IDM_POPUP_EXIT:
		{
			WinSendMsg(client(), WM_CLOSE, 0L, 0L);
			break;
		}
	}
}

MRESULT EXPENTRY MiniWin::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
	switch (msg)
		{
		case WM_COMMAND:
			{
				ProcessCommand(mp1, mp2);
				return 0;
			}

		case WM_BUTTON2CLICK:
		case WM_BUTTON2DBLCLK:
			{
				PopupMenu(MOUSEMSG(&msg)->x, MOUSEMSG(&msg)->y);
				return 0;
			}

		case WM_TIMER:
			{
				if (((USHORT)SHORT1FROMMP(mp1)) == timerID)
					{
            // Problem area...  Using Float causes Lockup to work
            // incorrecty.  Solutions welcome!

						if (iFloatWindow)
              WinSetWindowPos(frame(), HWND_TOP, 0, 0, 0, 0, SWP_ZORDER);

            RECTL rcl;
            WinQueryWindowRect(hwnd, &rcl);
            rcl.xLeft   += 2;
            rcl.xRight  -= 2;
            rcl.yBottom += 2;
            rcl.yTop    -= 2;

						WinInvalidateRect(hwnd, &rcl, FALSE);
            setTimer();
            return 0;
					}
        break;
			}

		case WM_PRESPARAMCHANGED:
			{
				PresParamChanged(hwnd, (ULONG)mp1);
				return 0;
			}

		case WM_PAINT:
			{
				HPS hps = WinBeginPaint(hwnd, 0, 0);

				// use RGB colours
				GpiCreateLogColorTable (hps, LCOL_RESET, LCOLF_RGB, 0L, 0L, NULL) ;

				RECTL rcl;
				WinQueryWindowRect(hwnd, &rcl);
				WinFillRect(hps, &rcl, backCol);

				DrawBox(hps, rcl);

				appObj->paint(hwnd, hps, rcl, this);

				WinEndPaint(hps);
				return 0;
			}
		}

  return Window::ProcessMsg(hwnd, msg, mp1, mp2);
}

