#ifndef _MyRenderWin_h
#define _MyRenderWin_h

#include "RenderWin.h"
#include "MiniWin.h"

// Override the window size calculation and window painting
// methods from the Application class.

class MyRenderWin : public RenderWin
{
public:
  MyRenderWin();
  ~MyRenderWin();
  virtual void calcWinSize(MiniWin* win);
  virtual void paint(HWND& hwnd, HPS& hps, RECTL& rcl, MiniWin* win);

private:
  ULONG timeFmt;
};

#endif
