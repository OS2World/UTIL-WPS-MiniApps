#ifndef _Application_h
#define _Application_h

class MiniWin;

class RenderWin
{
public:
  virtual ~RenderWin() {}

  virtual void calcWinSize(MiniWin* win)
  {
  }
  virtual void paint(HWND& hwnd, HPS& hps, RECTL& rcl, MiniWin* win)
  {
  }

private:

};

#endif