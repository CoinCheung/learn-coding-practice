#include<stdio.h>
#include<malloc.h>


int main(void)
{
    int (*a)[10] = (int(*)[10])malloc(sizeof(int)*20);
    return 0;
}
