#include "sipp.hpp"
#include "screen.hpp"

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#ifdef __SUNOS
#include<stdarg.h>
#endif

#include <unistd.h>

/* Clock must be a pointer to struct timeval */
#define GET_TIME(clock)       \
{                             \
  struct timezone tzp;        \
  gettimeofday (clock, &tzp); \
}

static void _screen_error(int fatal, bool use_errno, int error, const char *fmt, va_list ap)
{

}

#if 0
static void _screen_error(int fatal, bool use_errno, int error, const char *fmt, va_list ap)
{
    static unsigned long long count = 0;
    char * c = screen_last_error;
    struct timeval currentTime;

    //CStat::globalStat(fatal ? CStat::E_FATAL_ERRORS : CStat::E_WARNING);

    GET_TIME (&currentTime);

    //c+= sprintf(c, "%s: ", CStat::formatTime(&currentTime));
    c+= vsprintf(c, fmt, ap);
    if (use_errno) {
        c += sprintf(c, ", errno = %d (%s)", error, strerror(error));
    }
    c+= sprintf(c, ".\n");
    screen_errors++;

    if(screen_inited && !error_lfi.fptr && print_all_responses) {
        rotate_errorf();
        if(!error_lfi.fptr) {
            c += sprintf(c, "%s: Unable to create '%s': %s.\n",
                         screen_exename, screen_logfile, strerror(errno));
            screen_exit(EXIT_FATAL_ERROR);
        } else {
            fprintf(error_lfi.fptr, "%s: The following events occured:\n",
                    screen_exename);
            fflush(error_lfi.fptr);
        }
    }

    if(error_lfi.fptr) {
        count += fprintf(error_lfi.fptr, "%s", screen_last_error);
        fflush(error_lfi.fptr);
        if (ringbuffer_size && count > ringbuffer_size) {
            rotate_errorf();
            count = 0;
        }
        if (max_log_size && count > max_log_size) {
            print_all_responses = 0;
            if (error_lfi.fptr) {
                fflush(error_lfi.fptr);
                fclose(error_lfi.fptr);
                error_lfi.fptr = NULL;
                error_lfi.overwrite = false;
            }
        }
    } else if (fatal) {
        fprintf(stderr, "%s", screen_last_error);
        fflush(stderr);
    }

    if(fatal) {
        if(!screen_inited) {
            if(error == EADDRINUSE) {
                exit(EXIT_BIND_ERROR);
            } else {
                exit(EXIT_FATAL_ERROR);
            }
        } else {
            if(error == EADDRINUSE) {
                screen_exit(EXIT_BIND_ERROR);
            } else {
                screen_exit(EXIT_FATAL_ERROR);
            }
        }
    }
}
#endif

extern "C" {
    void ERROR(const char *fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);
        _screen_error(true, false, 0, fmt, ap);
        va_end(ap);
		/* 添加回产生crash，先注释掉 */
        //assert(0);
    }

    void ERROR_NO(const char *fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);
        _screen_error(true, true, errno, fmt, ap);
        va_end(ap);
    }

    void WARNING(const char *fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);
        _screen_error(false, false, 0, fmt, ap);
        va_end(ap);
    }

    void WARNING_NO(const char *fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);
        _screen_error(false, true, errno, fmt, ap);
        va_end(ap);
    }
}


