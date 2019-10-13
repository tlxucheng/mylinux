#include <stdio.h>

#define ARRAY_SZIE(x) (sizeof(x) / sizeof((x)[0]))

const char *country_name[] = {
"china",
"japan",
"american"
};

int main()
{
    int arr_size = ARRAY_SZIE(country_name);

    printf("arr_size: %d\n", arr_size);
 
    return 0;
}


