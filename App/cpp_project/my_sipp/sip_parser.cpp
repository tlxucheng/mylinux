#include <string.h>
#include <stdlib.h>
#include "screen.hpp"
#include "sip_parser.hpp"

/*************************** Mini SIP parser ***************************/
char * get_call_id(char *msg)
{
    static char call_id[MAX_HEADER_LEN];
    char * ptr1, * ptr2, * ptr3, backup;
    bool short_form;

    call_id[0] = '\0';

    short_form = false;

    ptr1 = strstr(msg, "Call-ID:");
    if(!ptr1) {
        ptr1 = strstr(msg, "Call-Id:");
    }
    if(!ptr1) {
        ptr1 = strstr(msg, "Call-id:");
    }
    if(!ptr1) {
        ptr1 = strstr(msg, "call-Id:");
    }
    if(!ptr1) {
        ptr1 = strstr(msg, "call-id:");
    }
    if(!ptr1) {
        ptr1 = strstr(msg, "CALL-ID:");
    }
    // For short form, we need to make sure we start from beginning of line
    // For others, no need to
    if(!ptr1) {
        ptr1 = strstr(msg, "\r\ni:");
        short_form = true;
    }
    if(!ptr1) {
        WARNING("(1) No valid Call-ID: header in reply '%s'", msg);
        return call_id;
    }

    if (short_form) {
        ptr1 += 4;
    } else {
        ptr1 += 8;
    }

    while((*ptr1 == ' ') || (*ptr1 == '\t')) {
        ptr1++;
    }

    if(!(*ptr1)) {
        WARNING("(2) No valid Call-ID: header in reply");
        return call_id;
    }

    ptr2 = ptr1;

    while((*ptr2) &&
            (*ptr2 != ' ') &&
            (*ptr2 != '\t') &&
            (*ptr2 != '\r') &&
            (*ptr2 != '\n')) {
        ptr2 ++;
    }

    if(!*ptr2) {
        WARNING("(3) No valid Call-ID: header in reply");
        return call_id;
    }

    backup = *ptr2;
    *ptr2 = 0;
    if ((ptr3 = strstr(ptr1, "///")) != 0) ptr1 = ptr3+3;
    strcpy(call_id, ptr1);
    *ptr2 = backup;
    return (char *) call_id;
}


