#include<stdio.h>
#include<malloc.h>
#include"bignumber.h"

int main(void)
{
    big_number a, b;
    big_number res;
    big_number *r;


    a = big_number_set("345");
    b = big_number_set("-123");
    big_number_print(a);
    big_number_print(b);


    fputs("sum\n", stdout);
    res = big_number_add(a,b);
    big_number_print(res);
    fputs("sum\n", stdout);
    for(int i = 0; i < 1; i++)
    {
        big_number_add_by(&res,b);
        big_number_print(res);
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
    // 4/5 3%-5 10/3 10/-3 -10/3 132/14 1232/34 32/2434
    int dividend = -32;
    int divider = -44;

    char *dend;
    char *dder;
    dend = (char *)malloc(sizeof(char)*5);
    dder = (char *)malloc(sizeof(char)*5);

    sprintf(dend, "%d", dividend);
    sprintf(dder, "%d", divider);

    a = big_number_set(dend);
    b = big_number_set(dder);
    r = big_number_divide(a,b);
    big_number_print(*r);
    big_number_print(*(r+1));
    big_number_free(*r);
    big_number_free(*(r+1));

    free(dend);
    free(dder);
    big_number_free(a);
    big_number_free(b);


    fputs("my try\n", stdout);
    fprintf(stdout, "%d\n", dividend/divider);
    fprintf(stdout, "%d\n", dividend%divider);

    return 0;
}

