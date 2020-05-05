#include <stdio.h>
#include <string.h>
 
typedef void (*funcP)();
void func1()
{
    printf("this is func1!\n");
}
void func2()
{
    printf("this is func2!\n");
}
void main()
{
    char c[20] = "\0";
    funcP funcp = NULL;
    printf("please input func name:");
    scanf("%s",c);  //input func1 or func2
    if(strcmp(c,"func1")==0)
    {
         func1();
    }else if(strcmp(c,"func2")==0){
         func2();
    }
}