#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void get_host_and_port(const char * addr, char * host, int * port)
{
}

int get_decimal_from_hex(char hex)
{
    if (isdigit(hex))
        return hex - '0';
    else
        return tolower(hex) - 'a' + 10;
}

