#ifndef _Point_h
#define _Point_h

class Point
{
public:
  Point()
  {
  }
  Point(LONG _x, LONG _y)
  {
    set(_x, _y);
  }
  void set(LONG _x, LONG _y)
  {
    p.x = _x;
    p.y = _y;
  }
  operator POINTL()
  {
    return p;
  }
  operator PPOINTL()
  {
    return &p;
  }
private:
  POINTL p;
};

#endif
