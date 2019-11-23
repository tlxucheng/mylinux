#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "xp_parser.h"

#define XP_MAX_NAME_LEN   256
#define XP_MAX_FILE_LEN   65536
#define XP_MAX_STACK_LEN  256

char   xp_file     [XP_MAX_FILE_LEN + 1];
char * xp_position [XP_MAX_STACK_LEN];
int    xp_stack    = 0;

int xp_set_xml_buffer_from_file(const char * filename)
{
    return 1;
}

int xp_set_xml_buffer_from_string(const char * str)
{
    size_t len = strlen(str);

    if(len > XP_MAX_FILE_LEN) {
        return 0;
    }
    
    strcpy(xp_file, str);
    xp_stack = 0;
    xp_position[xp_stack] = xp_file;

    if(strstr(xp_position[xp_stack], "<?xml") != xp_position[xp_stack]) return 0;
    if(!strstr(xp_position[xp_stack], "?>")) return 0;
    xp_position[xp_stack] = xp_position[xp_stack] + 2;

    return 1;
}


