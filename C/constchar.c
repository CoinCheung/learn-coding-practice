#include<stdio.h>
#include<malloc.h>
#include<string.h>


const int* fun1()
{
    int *p = (int *)malloc(sizeof(int)*10);

    return p;
}

void fun2()
{
    
}

int main()
{
    char *cp = "ddddd";
    const char *cp2 = "fffffff";
    char *cpp;
    int a[4];
    int *pp = NULL;

    a[0] = 1;

    pp = fun1();
    pp[0] = 1;
    fprintf(stdout, "pp[0] is: %s\n",pp[0]);

    fprintf(stdout, "before changed, cp is: %s\n",cp);
    cp = "fffff";

    fprintf(stdout, "cp[2] is: %c\n",cp[2]);

    fprintf(stdout, "after changed, cp is: %s\n",cp);
}

