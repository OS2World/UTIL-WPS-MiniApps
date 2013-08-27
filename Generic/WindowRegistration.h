#ifndef _WindowRegistration_h
#define _WindowRegistration_h

class WindowRegistration
{
public:
  static const PSZ windowClassName;

  WindowRegistration(HAB hab, PFNWP proc);

private:
  static ULONG registered;
};

#endif

