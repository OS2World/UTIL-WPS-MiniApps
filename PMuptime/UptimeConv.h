#ifndef _UptimeConv_h
#define _UptimeConv_h


class UptimeConv
{
public:
  UptimeConv();
  ULONG days();
  ULONG hours();
  ULONG mins();
  ULONG secs();
  char* makeTitle();

private:
  ULONG timeUp;
};

inline UptimeConv::UptimeConv()
{
  DosQuerySysInfo(QSV_MS_COUNT,
                  QSV_MS_COUNT,
                  &timeUp,
                  sizeof(timeUp));
}

inline ULONG UptimeConv::secs()
{
  return timeUp / 1000;
}

inline ULONG UptimeConv::mins()
{
  return secs() / 60;
}

inline ULONG UptimeConv::hours()
{
  return mins() / 60;
}

inline ULONG UptimeConv::days()
{
  return hours() / 24;
}

#endif
