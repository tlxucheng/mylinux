#ifndef __STAT_H__
#define __STAT_H__

#define TIME_LENGTH 64

using namespace std;

class CStat
{
public:
    
    static char* formatTime (struct timeval* P_tv, bool with_epoch = false);
};

#endif

