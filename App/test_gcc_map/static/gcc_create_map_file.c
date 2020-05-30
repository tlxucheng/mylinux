#include <stdio.h>

static int test_function()
{
    printf("This is a function called: %s\n", __func__);

    return 0;
}

int main()
{
    test_function(0);

    return 0;
}

