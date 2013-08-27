#ifndef _MiniWin_h
#define _MiniWin_h

#include "Window.h"
#include "RenderWin.h"

extern const ULONG timerID;

class MiniWin : public Window
{
public:
  MiniWin(HAB hab, RenderWin* render);
	~MiniWin();

	void PresParamChanged(HWND hwnd, LONG lPP);

  void size(ULONG cx, ULONG cy)
  {
    Window::size(frame(), cx, cy);
    Window::size(client(), cx, cy);
  }

  void move(LONG x, LONG y)
  {
    Window::move(frame(), x, y);
  }

  void setTimer()
  {
    WinStartTimer(myHab,
									client(),
									timerID,
									timerInt);
	}

	void stopTimer()
	{
		WinStopTimer(myHab,
								 client(),
								 timerID);
	}

	void setInt(ULONG newInt)
	{
		timerInt = newInt;
		setTimer();
  }

  virtual MRESULT EXPENTRY ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

private:
	void        loadConfig();
	void        PopupMenu(int x, int y);
	void        ProcessCommand(MPARAM mp1, MPARAM mp2);

	RenderWin*  appObj;
  HAB         myHab;
	ULONG       timerInt;
	HSWITCH     switchEntry;
	int         iFloatWindow;
};

#endif
