#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "logger.hpp"
#include "screen.hpp"
#include "sipp.hpp"

#define SIPP_ENDL "\r\n"

void rotatef(struct logfile_info *lfi)
{
    char L_rotate_file_name [MAX_PATH];

    if (!lfi->fixedname) {
        sprintf (lfi->file_name, "%s_%d_%s.log", scenario_file, getpid(), lfi->name);
    }

    if (ringbuffer_files > 0) {
        if (!lfi->ftimes) {
            lfi->ftimes = (struct logfile_id *)calloc(ringbuffer_files, sizeof(struct logfile_id));
        }
        /* We need to rotate away an existing file. */
        if (lfi->nfiles == ringbuffer_files) {
            if ((lfi->ftimes)[0].n) {
                sprintf(L_rotate_file_name, "%s_%d_%s_%lu.%d.log", scenario_file, getpid(), lfi->name, (lfi->ftimes)[0].start, (lfi->ftimes)[0].n);
            } else {
                sprintf(L_rotate_file_name, "%s_%d_%s_%lu.log", scenario_file, getpid(), lfi->name, (lfi->ftimes)[0].start);
            }
            unlink(L_rotate_file_name);
            lfi->nfiles--;
            memmove(lfi->ftimes, &((lfi->ftimes)[1]), sizeof(struct logfile_id) * (lfi->nfiles));
        }
        if (lfi->starttime) {
            (lfi->ftimes)[lfi->nfiles].start = lfi->starttime;
            (lfi->ftimes)[lfi->nfiles].n = 0;
            /* If we have the same time, then we need to append an identifier. */
            if (lfi->nfiles && ((lfi->ftimes)[lfi->nfiles].start == (lfi->ftimes)[lfi->nfiles - 1].start)) {
                (lfi->ftimes)[lfi->nfiles].n = (lfi->ftimes)[lfi->nfiles - 1].n + 1;
            }
            if ((lfi->ftimes)[lfi->nfiles].n) {
                sprintf(L_rotate_file_name, "%s_%d_%s_%lu.%d.log", scenario_file, getpid(), lfi->name, (lfi->ftimes)[lfi->nfiles].start, (lfi->ftimes)[lfi->nfiles].n);
            } else {
                sprintf(L_rotate_file_name, "%s_%d_%s_%lu.log", scenario_file, getpid(), lfi->name, (lfi->ftimes)[lfi->nfiles].start);
            }
            lfi->nfiles++;
            fflush(lfi->fptr);
            fclose(lfi->fptr);
            lfi->fptr = NULL;
            rename(lfi->file_name, L_rotate_file_name);
        }
    }

    time(&lfi->starttime);
    if (lfi->overwrite) {
        lfi->fptr = fopen(lfi->file_name, "w");
    } else {
        lfi->fptr = fopen(lfi->file_name, "a");
        lfi->overwrite = true;
    }
    if(lfi->check && !lfi->fptr) {
        /* We can not use the error functions from this function, as we may be rotating the error log itself! */
        ERROR("Unable to create '%s'", lfi->file_name);
    }
}

void rotate_messagef()
{
    rotatef(&message_lfi);
}

int _trace (struct logfile_info *lfi, const char *fmt, va_list ap)
{
	int ret = 0;
	if(lfi->fptr) {
		ret = vfprintf(lfi->fptr, fmt, ap);
		fflush(lfi->fptr);

		lfi->count += ret;

		if (max_log_size && lfi->count > max_log_size) {
			fclose(lfi->fptr);
			lfi->fptr = NULL;
		}

		if (ringbuffer_size && lfi->count > ringbuffer_size) {
			rotatef(lfi);
			lfi->count = 0;
		}
	}
	return ret;
}

int TRACE_MSG(const char *fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = _trace(&message_lfi, fmt, ap);
	va_end(ap);

	return ret;
}


