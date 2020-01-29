#include <iostream>
#include <fstream>
#include <iomanip>
#include <assert.h>

#include "sipp.hpp"
#include "scenario.hpp"
#include "screen.hpp"

char* CStat::formatTime (struct timeval* P_tv, bool with_epoch)
{
    static char L_time [TIME_LENGTH];
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (L_time, 0, TIME_LENGTH);
    } else {
        if (with_epoch) {
            sprintf(L_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%06ld",
                    L_currentDate->tm_year + 1900,
                    L_currentDate->tm_mon + 1,
                    L_currentDate->tm_mday,
                    L_currentDate->tm_hour,
                    L_currentDate->tm_min,
                    L_currentDate->tm_sec,
                    (long)P_tv->tv_usec);
        } else {
            sprintf(L_time, "%4.4d-%2.2d-%2.2d\t%2.2d:%2.2d:%2.2d.%06ld\t%10.10ld.%06ld",
                    L_currentDate->tm_year + 1900,
                    L_currentDate->tm_mon + 1,
                    L_currentDate->tm_mday,
                    L_currentDate->tm_hour,
                    L_currentDate->tm_min,
                    L_currentDate->tm_sec,
                    (long)P_tv->tv_usec,
                    P_tv->tv_sec,
                    (long)P_tv->tv_usec);
        }
    }
    return (L_time);
} /* end of formatTime */


