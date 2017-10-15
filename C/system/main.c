#include<stdio.h>
#include<stdlib.h>


int main(void)
{
    int res;

    res = system("./shell");
    fprintf(stdout, "main: system return is %d\n", res>>8);

    return 0;
}
