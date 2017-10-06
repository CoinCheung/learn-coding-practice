#ifndef _BIGNUMBER_H_
#define _BIGNUMBER_H_

/* ======================================================
 *  includes
 * ====================================================== */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<malloc.h>

/* ======================================================
 *  types and macros
 * ====================================================== */
#define PLUS 43
#define MINUS 45
#define LARGER 1
#define SMALLER -1
#define EQUAL 0 

typedef unsigned char uchar_t;

// struct of the big number, numbers stored in a char array where high digitals are stored in grids with high indices
// the highest digit is the operator digit where + is plus and - minus
typedef struct big_number
{
    // data
    int length;
    char *nums;
    char sign;

    // functions
    // int (*is_larger_sign)(const struct big_number *, const struct big_number *);
    // int (*is_larger_no_sign)(const struct big_number *, const struct big_number *);
    // void (*sign_reverse)(struct big_number * const);

}big_number;

/* ======================================================
 *  function definitions
 * ====================================================== */

// functions relevant to big number
void big_number_free(big_number);
big_number big_number_set(const char*);
// 增加一个直接传地址和加数进去就能实现在原来的数上加和乘的函数
big_number big_number_add(const big_number, const big_number); 
big_number big_number_mult(const big_number, const big_number);
big_number big_number_fact(const big_number);
int big_number_cmp_sign(const big_number, const big_number);
int big_number_cmp_nosign(const big_number, const big_number);
void big_number_add_by(big_number * const, const big_number); 
void big_number_mult_by(big_number * const, const big_number);

// associated functions
int max(int ,int);
int min(int ,int);
char char_to_num(const char ch, const char op);
char char_to_unnum(const char ch);
char num_to_char(const char num);

// inner functions
void sign_reverse(big_number * const);
void big_number_print(const big_number);


#endif
