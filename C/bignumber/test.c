#include<stdio.h>
#include<malloc.h>
#include"bignumber.h"

int main(void)
{
    big_number a, b;
    big_number res;
    big_number *r;

    a = big_number_set("14");
    b = big_number_set("2");
    big_number_print(a);
    big_number_print(b);


    fputs("sum\n", stdout);
    res = big_number_add(a,b);
    big_number_print(res);
    fputs("sum\n", stdout);
    for(int i = 0; i < 1; i++)
    {
        /* big_number_add_by(&res,a); */
        /* big_number_print(res); */
    }
    big_number_free(res);

    fputs("product\n", stdout);
    res = big_number_mult(a,b);
    big_number_print(res);
    for(int i = 0; i < 1; i++)
    {
        big_number_mult_by(&res,b);
        big_number_print(res);
    }
    big_number_free(res);

    fputs("factorize\n", stdout);
    res = big_number_fact(b);
    big_number_print(res);
    big_number_free(res);

    fputs("sign reverse\n", stdout);
    res = sign_reverse(b);
    big_number_print(res);
    big_number_free(res);


    fputs("division\n", stdout);
    r = big_number_divide(a,b);
    big_number_print(*r);
    big_number_print(*(r+1));
    big_number_free(*r);
    big_number_free(*(r+1));

    big_number_free(a);
    big_number_free(b);


    fputs("my try\n", stdout);
    fprintf(stdout, "%d\n", 2%-42);

    return 0;
}

