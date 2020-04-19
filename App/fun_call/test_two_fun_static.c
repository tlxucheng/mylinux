static int bar(int c, int d)
{
    int e = c + d;
    return e;
}

int foo(int a, int b)
{
    int d = 1;

    switch(d)
    {
        case 1:
            return bar(a, b);
        defualt:
            return -1;
    }

    return 0;
}
int main(void)
{
    foo(2, 5);
 
    return 0;
}
