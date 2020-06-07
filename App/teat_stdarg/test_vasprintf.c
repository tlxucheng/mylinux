#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int test_func(char *fmt, ...)
{
    va_list ap;
    char *buf = NULL;

    va_start(ap, fmt);
    vasprintf(&buf, fmt, ap);
	printf("%s\n", buf);

    va_end(ap);
    free(buf);

    return 0;
}

int main()
{
    test_func("%s %d", "linuxcode", 10);

	return 0;
}
