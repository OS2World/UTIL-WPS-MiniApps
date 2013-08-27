#define INCL_DOS
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#pragma hdrstop

#include <string.h>

#include "Window.h"


Window::Window(HAB hab) : winReg(hab, &WindowProc)
{
  FRAMECDATA fcdata;
  fcdata.cb            = sizeof(fcdata);
  fcdata.flCreateFlags = 0;
  fcdata.hmodResources = 0;
  fcdata.idResources   = 0;

  hwndFrame = WinCreateWindow(HWND_DESKTOP,
                              WC_FRAME,
                              0,
                              WS_VISIBLE,
                              0, 0, 0, 0,
                              HWND_DESKTOP,
                              HWND_TOP,
                              0,
                              &fcdata,
                              0);

  hwndClient  = WinCreateWindow(hwndFrame,
                                WindowRegistration::windowClassName,
                                0,
                                WS_VISIBLE,
                                0, 0, 0, 0,
                                hwndFrame,
                                HWND_TOP,
                                0,
                                (PVOID)this,
                                0);

}

Window::~Window()
{
  WinDestroyWindow(hwndClient);
  WinDestroyWindow(hwndFrame);
}

MRESULT EXPENTRY Window::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
		case WM_BUTTON1DOWN:
			{
        trackWindow();
        return 0;
      }
    }
  return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

void Window::trackWindow(void)
{
  SWP wpos;
  WinQueryWindowPos(frame(), &wpos);

  RECTL rcl;
  WinQueryWindowRect(HWND_DESKTOP, &rcl);

  TRACKINFO  ti;

  ti.cxBorder            = 2;
  ti.cyBorder            = 2;
  ti.cxGrid              = 0;
  ti.cyGrid              = 0;
  ti.cxKeyboard          = 4;
  ti.cyKeyboard          = 4;
  ti.rclBoundary.xLeft   = 0;
  ti.rclBoundary.xRight  = rcl.xRight;
  ti.rclBoundary.yBottom = 0;
  ti.rclBoundary.yTop    = rcl.yTop;
  ti.ptlMinTrackSize.x   = 1;
  ti.ptlMinTrackSize.y   = 1;
  ti.ptlMaxTrackSize.x   = rcl.xRight;
  ti.ptlMaxTrackSize.y   = rcl.yTop;
  ti.rclTrack.xLeft      = wpos.x;
  ti.rclTrack.yBottom    = wpos.y;
  ti.rclTrack.xRight     = wpos.x + wpos.cx;
  ti.rclTrack.yTop       = wpos.y + wpos.cy;
  ti.fs                  = TF_MOVE;

  if (WinTrackRect(HWND_DESKTOP, 0, &ti) == TRUE)
    {
      WinSetWindowPos(frame(), HWND_TOP,
                      ti.rclTrack.xLeft,
                      ti.rclTrack.yBottom,
                      0, 0,
                      SWP_MOVE | SWP_ZORDER);
    }
}

MRESULT EXPENTRY Window::WindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
    case WM_CREATE:
      {
        WinSetWindowULong(hwnd, QWL_USER, (ULONG)mp1);
      }
    }
  Window* win = (Window*)WinQueryWindowULong(hwnd, QWL_USER);
  return win->ProcessMsg(hwnd, msg, mp1, mp2);
}
