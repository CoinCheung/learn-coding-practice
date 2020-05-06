#include<assert.h>
#include<stdio.h>

int main(void)
{
    assert(1 == 0);

    fprintf(stdout, "after the assert line");

    return 0;
}
