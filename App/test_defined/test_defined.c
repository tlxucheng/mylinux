#include <stdio.h>

int main()
{
#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
    printf("STDC\n");
#elif defined __GNUC__
    printf("__GNUC__\n");
#endif

#if defined (__linux__) && defined(__GLIBC__)
    printf("linux glibc\n");
#else
    printf("not linux glibc\n");
#endif

    return 0;
}