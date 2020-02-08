#ifndef __SIPP_STRINGS_H__
#define __SIPP_STRINGS_H__

char *strcasestr2 ( char *__haystack, const char *__needle);
void init_tolower_table();
char *strncasestr (char *s, const char *find, size_t n);
void get_host_and_port(const char * addr, char * host, int * port);
int get_decimal_from_hex(char hex);

#endif /* __SIPP_STRINGS_H__ */


