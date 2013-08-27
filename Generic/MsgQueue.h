#ifndef _MsgQueue_h
#define _MsgQueue_h

class MsgQueue
{
public:
  MsgQueue(HAB& qHab) : hab(qHab)
  {
    hmq = WinCreateMsgQueue(qHab, 0);
  }

  ~MsgQueue()
  {
    WinDestroyMsgQueue(hmq);
  }

  void Run(void);

private:
  HAB&  hab;
  HMQ   hmq;
};

#endif
