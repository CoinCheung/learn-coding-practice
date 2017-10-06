#include<stdio.h>
#include<malloc.h>
#include"bignumber.h"

int main()
{
    big_number a, b;
    big_number res;

    a = big_number_set("-100");
    b = big_number_set("5857");
    big_number_print(a);
    big_number_print(b);


    fputs("sum\n", stdout);
    res = big_number_add(a,b);
    for(int i = 0; i < 100; i++)
    {
        big_number_add_by(&res,a);
        big_number_print(res);
    }
    big_number_free(res);

    fputs("product\n", stdout);
    res = big_number_mult(a,b);
    for(int i = 0; i < 100; i++)
    {
        big_number_mult_by(&res,b);
        big_number_print(res);
    }
    big_number_free(res);

    fputs("factorize\n", stdout);
    res = big_number_fact(b);
    big_number_print(res);
    big_number_free(res);

    big_number_free(a);
    big_number_free(b);

    return 0;
}

