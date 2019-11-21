#ifndef __SCREEN_H
#define __SCREEN_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    void ERROR(const char *fmt, ...) __attribute__ ((noreturn));
    void WARNING(const char *fmt, ...);
    void ERROR_NO(const char *fmt, ...);
    void WARNING_NO(const char *fmt, ...);
#ifdef __cplusplus
}
#endif

#define EXIT_TEST_OK               0
#define EXIT_TEST_FAILED           1
#define EXIT_TEST_RES_INTERNAL     97
#define EXIT_TEST_RES_UNKNOWN      98
#define EXIT_OTHER                 99
#define EXIT_FATAL_ERROR           -1
#define EXIT_BIND_ERROR            -2

#endif


