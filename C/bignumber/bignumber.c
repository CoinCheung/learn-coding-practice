#include"bignumber.h"

/* ======================================================
 *  function implementations
 * ====================================================== */

/* function: void big_number_free(const big_number bnum);
 * function designed to free the memory the big number occupies
 * input: a big number struct
 * return: none
 * */
inline void big_number_free(big_number bnum)
{
    free(bnum.nums);
    bnum.nums = NULL;
}


/* function: 
 * 
 * input: a string (char array end with 0)
 * return: */
big_number big_number_set(const char* nums)
{
    big_number bn;
    int len;

    len = 0;
    while(nums[len] != 0) // count the length
    {
        len ++;
    }
    // when the number is negative
    if(nums[0] == '-')
    {
        bn.sign = MINUS;
        len --;
        bn.nums = (char*)malloc(len*sizeof(char));
        for(int i = 0; i < len; i ++)
            bn.nums[i] = nums[len - i];
    }
    else
    {
        bn.sign = PLUS;
        bn.nums = (char*)malloc(len*sizeof(char));
        for(int i = 0; i < len; i ++)
            bn.nums[i] = nums[len - i -1];
    }

    bn.length = len;

    return bn;
}

/* function designed to add two big numbers
 * input: two big numbers a and b
 * return: the sum of the two big numbers */
big_number big_number_add(const big_number a, const big_number b)
{
    // local variables
    big_number res;
    const big_number *bp_large = NULL;
    const big_number *bp_small = NULL;
    int len_max, len_min;

    // initialize local variables
    if(big_number_cmp_nosign(a, b) == LARGER)
    {
        bp_large = &a;
        bp_small = &b;
    }
    else
    {
        bp_large = &b;
        bp_small = &a;
    }
    len_max = max(a.length, b.length);
    len_min = min(a.length, b.length);
    res.length = len_max + 1;

    res.nums = (char*)malloc(res.length * sizeof(char));
    memset(res.nums, 0, res.length);

    // calculation
    // computation of common parts
    for(int i = 0; i < len_min; i ++)
    {
        // scenario where two number have same sign
        if(a.sign == b.sign )
        {
            res.nums[i] += char_to_unnum(bp_large->nums[i]) + char_to_unnum(bp_small->nums[i]);
            if(res.nums[i] > 9)
            {
                res.nums[i] -= 10;
                res.nums[i+1] ++;
            }
        }
        // scenario where two numbers have distinct signs
        else
        {
            res.nums[i] += char_to_unnum(bp_large->nums[i]) - char_to_unnum(bp_small->nums[i]);
            if(res.nums[i] < 0)
            {
                res.nums[i] += 10;
                res.nums[i+1] --;
            }
        }
        res.nums[i] = num_to_char(res.nums[i]);
    }

    // computation of extra parts larger number has to smaller one
    for(int i = len_min; i < len_max; i++) 
    {
        res.nums[i] += char_to_unnum(bp_large->nums[i]);
        if(res.nums[i] > 9)
        {
            res.nums[i] -= 10;
            res.nums[i+1] ++;
        }
        if(res.nums[i] < 0)
        {
            res.nums[i] += 10;
            res.nums[i+1] --;
        }
        res.nums[i] = num_to_char(res.nums[i]);
    }

    res.nums[res.length-1] = num_to_char(res.nums[res.length-1]);
        
    // remove the first digits if they are zeros
    while(res.length > 1 && res.nums[res.length-1] == '0')
        res.length --;
    res.sign = bp_large->sign;
    return res;
}


/* function: inline void big_number_add_by(big_number * const a, const big_number b);
 * add a big number to the current one *a directly, without return a new one 
 * input:
 * return: */
inline void big_number_add_by(big_number * const a, const big_number b) 
{
    big_number temp;

    temp = big_number_add(*a,b);
    big_number_free(*a);
    *a = temp;
}


/* function: int max(int a, int b);
 * the inline function to compare two integers to find the larger
 * input:
 * return: */
inline int max(int a,int b)
{
    return a > b ? a : b;
}


/* function: int min(int a, int b);
 * the inline function to compare two integers to find the smaller
 * input:
 * return: */
inline int min(int a,int b)
{
    return a > b ? b : a;
}


/* function: 
 * 
 * input:
 * return: */
inline char char_to_num(const char ch, const char op)
{
    if(op == PLUS)
        return ch - 48;
    else
        return 48 - ch;
}


/* function: 
 * 
 * input:
 * return: */
inline char char_to_unnum(const char ch)
{
    return ch - 48;
}

/* function: 
 * 
 * input:
 * return: */
inline char num_to_char(const char num)
{
    if(num >= 0)
        return num + 48;
    else
        return 48 - num;
}

/* function: int big_number_cmp_sign(const big_number a, const big_number b)
 * see if the given number is larger than the current one with sign considered
 * input: big number a, its counterpart b in the comparison
 * return 1 if current number is larger, -1 if counterpart is larger, 0 is they are same */
int big_number_cmp_sign(const big_number a, const big_number b)
{
    int flag;

    // scenario where signs are different
    if(a.sign == PLUS && b.sign == MINUS)
        return LARGER;
    else if(a.sign == MINUS && b.sign == PLUS)
        return SMALLER;

    // scenario where signs are same
    flag = big_number_cmp_nosign(a, b);
    if((a.sign == PLUS && flag == LARGER) || (a.sign == MINUS && flag == SMALLER))
        return LARGER;
    else if((a.sign == PLUS && flag == SMALLER) || (a.sign == MINUS && flag == LARGER))
        return SMALLER;
    else
        return EQUAL;
}


/* function: int big_number_cmp_nosign(const big_number *a, const big_number *b)
 * see if the given number is larger than the current one with sign not considered
 * input: big number a, its counterpart b in the comparison
 * return 1 if current number is larger, -1 if counterpart is larger, 0 if they are same */
int big_number_cmp_nosign(const big_number a, const big_number b)
{
    // scenario where two numbers has different length
    if(a.length > b.length)
        return LARGER;
    if(a.length < b.length)
        return SMALLER;

    // scenario where two numbers are same in length
    for(int i = a.length -1; i >=0 ;i --) // compare from high digits
    {
        if(*(a.nums + i) > *(b.nums + i))
            return LARGER;
        if(*(a.nums + i) < *(b.nums + i))
            return SMALLER;
    }
    
    return EQUAL; // when they are same
}



/* function: 
 * 
 * input:
 * return: */
inline void sign_reverse(big_number * const bn)
{
    bn->sign = (bn->sign == PLUS) ? MINUS : PLUS;
}


/* function: 
 * 
 * input:
 * return: */
inline void big_number_print(const big_number bn)
{
    if(bn.sign == MINUS)
        fputs("-",stdout);
    for(int i = bn.length-1; i >=0 ; i--)
        fprintf(stdout, "%c",bn.nums[i]);
    fputs("\n",stdout);
}


/* function: 
 * 
 * input:
 * return: */
big_number big_number_mult(const big_number a, const big_number b)
{
    big_number res;
    int i;

    if(a.sign == b.sign)
        res.sign = PLUS;
    else
        res.sign = MINUS;

    res.length = a.length + b.length;

    res.nums = (char *)malloc(res.length*sizeof(char));
    memset(res.nums, 0, res.length);
    for(int i = 0; i < a.length; i++)
        for(int j = 0; j < b.length; j++)
            res.nums[i+j] += char_to_unnum(a.nums[i]) * char_to_unnum(b.nums[j]);

    for(int i = 0; i < res.length; i++)
    {
        if(res.nums[i] > 9)
        {
            res.nums[i+1] += res.nums[i]/10;
            res.nums[i] = res.nums[i]%10;
        }
        res.nums[i] = num_to_char(res.nums[i]%10);
    }

    i = res.length-1;
    while(i > 0 && res.nums[i] == '0')
    {
        res.length --;
        i --;
    }

    return res;
}

/* function: 
 * 
 * input:
 * return: */
void big_number_mult_by(big_number * const a, const big_number b)
{
    big_number temp;

    temp = big_number_mult(*a, b);
    big_number_free(*a);
    *a = temp;
}


/* function: 
 * 
 * input:
 * return: */
big_number big_number_fact(const big_number a)
{
    big_number multiplier;
    big_number step;
    big_number res;
    big_number temp;

    multiplier = big_number_set("3");
    res = big_number_set("2");
    step = big_number_set("1");

    while(big_number_cmp_sign(multiplier, a) != LARGER)
    {
        temp = res;
        res = big_number_mult(multiplier, res);
        big_number_free(temp);

        temp = multiplier;
        multiplier = big_number_add(multiplier, step);
        big_number_free(temp);
    }

    big_number_free(multiplier);
    big_number_free(step);

    return res;
}

