#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void get_host_and_port(const char * addr, char * host, int * port)
{
}

static unsigned char tolower_table[256];

void init_tolower_table()
{
    for (int i = 0; i < 256; i++) {
        tolower_table[i] = tolower(i);
    }
}

/* This is simpler than doing a regular tolower, because there are no branches.
 * We also inline it, so that we don't have function call overheads.
 *
 * An alternative to a table would be to do (c | 0x20), but that only works if
 * we are sure that we are searching for characters (or don't care if they are
 * not characters. */
unsigned char inline mytolower(unsigned char c)
{
    return tolower_table[c];
}

char * strncasestr(char *s, const char *find, size_t n)
{
    char *end = s + n;
    char c, sc;
    size_t len;

    if ((c = *find++) != 0) {
        c = mytolower((unsigned char)c);
        len = strlen(find);
        end -= (len - 1);
        do {
            do {
                if ((sc = *s++) == 0)
                    return (NULL);
                if (s >= end)
                    return (NULL);
            } while ((char)mytolower((unsigned char)sc) != c);
        } while (strncasecmp(s, find, len) != 0);
        s--;
    }
    return ((char *)s);
}

int get_decimal_from_hex(char hex)
{
    if (isdigit(hex))
        return hex - '0';
    else
        return tolower(hex) - 'a' + 10;
}

