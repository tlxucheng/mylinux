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

extern char * scenario_file;

extern unsigned long long max_log_size		      _DEFVAL(0);
extern unsigned long long ringbuffer_size	      _DEFVAL(0);
extern int    ringbuffer_files			          _DEFVAL(0);

struct logfile_id {
    time_t start;
    int n;
};

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

#ifdef GLOBALS_FULL_DEFINITION
#define LOGFILE(name, s, check) \
	struct logfile_info name = { s, check, NULL, 0, NULL, "", true, false, 0, 0};
#else
#define LOGFILE(name, s, check) \
	extern struct logfile_info name;
#endif
LOGFILE(calldebug_lfi, "calldebug", true);
LOGFILE(message_lfi, "messages", true);
LOGFILE(shortmessage_lfi, "shortmessages", true);
LOGFILE(log_lfi, "logs", true);
LOGFILE(error_lfi, "errors", false);

void rotate_messagef();

#endif /* __SIPP_LOGGER_H__ */

