#include <string.h>
#include <stdio.h>

int main()
{
    char s[128] = "ccp_gloabl:ccp1_global_spec";
    char *p;
    char qq[128] = "123456";
    char ss[128] = {0};
    char ww[128] = {0};
    char aa[5] = {0};
    char bb[6] = {"12345"};

    p = index(s, ':');
    *p++ = '\0';
    printf("p %s, s %s\n", p, s);

    qq[4] = '\0';
    printf("qq: %s\n", qq);
    strncpy(ss, qq, 6);
    printf("ss %s\n", ss);
    printf("ss[5]: %c\n", ss[5]);

    memcpy(ww, qq, sizeof(ww));
    printf("ww: %s\n", ww);
    printf("ww[5]: %c\n", ww[5]);  

    printf("bb: %s\n", bb);
    strncpy(aa, bb, sizeof(aa) - 1);
    aa[sizeof(aa)] = '\0';
    printf("aa: %s\n", aa);
    
    return 0;
}
