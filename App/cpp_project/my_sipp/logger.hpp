#ifndef __SIPP_LOGGER_H__
#define __SIPP_LOGGER_H__

/************************** Trace Files ***********************/

#include <time.h>

#define MAX_PATH                   250

#ifdef GLOBALS_FULL_DEFINITION
#define extern
#define _DEFVAL(value) = value
#else
#define _DEFVAL(value)
#endif

extern bool   useMessagef                         _DEFVAL(0);

struct logfile_info {
    const char *name;
    bool check;
    FILE *fptr;
    int nfiles;
    struct logfile_id *ftimes;
    char file_name[MAX_PATH];
    bool overwrite;
    bool fixedname;
    time_t starttime;
    unsigned int count;
};

void rotate_messagef();

#endif /* __SIPP_LOGGER_H__ */

