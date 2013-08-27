// A Window class.

#ifndef _Window_h
#define _Window_h

#include "WindowRegistration.h"

class Window
{
public:
	Window(HAB hab);

	~Window();

	virtual MRESULT EXPENTRY ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

	LONG fgnd()
	{
		return textCol;
	}

	LONG bgnd()
	{
		return backCol;
	}

	void setFgnd(LONG l)
	{
		textCol = l;
	}

	void setBgnd(LONG l)
	{
		backCol = l;
	}

	HWND client()
  {
    return hwndClient;
  }

  HWND frame()
  {
		return hwndFrame;
  }

  void size(HWND hwnd, ULONG cx, ULONG cy)
  {
    WinSetWindowPos(hwnd, 0, 0, 0, cx, cy, SWP_SIZE);
  }

  void move(HWND hwnd, ULONG x, ULONG y)
  {
    WinSetWindowPos(hwnd, 0, x, y, 0, 0, SWP_MOVE);
	}

private:
	static MRESULT EXPENTRY WindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
	void                    trackWindow();

private:
	WindowRegistration  winReg;
	HWND                hwndFrame;
	HWND                hwndClient;

protected:
	LONG       					textCol;
	LONG   					    backCol;
};

#endif

