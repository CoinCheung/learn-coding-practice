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
            bn.nums[i] = nums[len - i] - 48;
    }
    else
    {
        bn.sign = PLUS;
        bn.nums = (char*)malloc(len*sizeof(char));
        for(int i = 0; i < len; i ++)
            bn.nums[i] = nums[len - i -1] - 48;
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
            res.nums[i] += bp_large->nums[i] + bp_small->nums[i];
            if(res.nums[i] > 9)
            {
                res.nums[i] -= 10;
                res.nums[i+1] ++;
            }
        }
        // scenario where two numbers have distinct signs
        else
        {
            res.nums[i] += bp_large->nums[i] - bp_small->nums[i];
            if(res.nums[i] < 0)
            {
                res.nums[i] += 10;
                res.nums[i+1] --;
            }
        }
    }

    // computation of extra parts larger number has to smaller one
    for(int i = len_min; i < len_max; i++) 
    {
        res.nums[i] += bp_large->nums[i];
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
    }

    // remove the first digits if they are zeros
    while(res.length > 1 && res.nums[res.length-1] == 0)
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
inline void sign_reverse_by(big_number * const bn)
{
    bn->sign = (bn->sign == PLUS) ? MINUS : PLUS;
}


/* function: 
 * 
 * input:
 * return: */
inline big_number sign_reverse(const big_number bn)
{
    big_number res;
    
    res.length = bn.length;
    res.sign = (bn.sign == PLUS) ? MINUS : PLUS;
    res.nums = (char*)malloc(sizeof(char)*bn.length);
    memcpy(res.nums,bn.nums,bn.length);

    return res;
}



/* function: 
 * 
 * input:
 * return: */
inline void big_number_print(const big_number bn)
{
    if(bn.sign == MINUS)
        if(!(bn.length == 1 && bn.nums[0] == 0))
            fputs("-",stdout);

    for(int i = bn.length-1; i >=0 ; i--)
        fprintf(stdout, "%hhd",bn.nums[i]);
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
        {
            res.nums[i+j] += a.nums[i] * b.nums[j];
            if(res.nums[i+j] > 10)
            {
                res.nums[i+j+1] += res.nums[i+j]/10;
                res.nums[i+j] = res.nums[i+j]%10;
            }
        }

    i = res.length-1;
    while(i > 0 && res.nums[i] == 0)
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
    big_number cease;

    // positive number
    if(a.sign == PLUS)
    {
        step = big_number_set("-1");
        res = big_number_copy(a);
        multiplier = big_number_add(res, step);
        cease = big_number_set("0");

        while(big_number_cmp_sign(multiplier, cease) == LARGER)
        {
            big_number_mult_by(&res, multiplier);
            big_number_add_by(&multiplier, step);
        }
    }
    /* else if(a.sign == MINUS) */
    else
    {
        step = big_number_set("1");
        res = big_number_copy(a);
        multiplier = big_number_add(res, step);
        cease = big_number_set("0");

        while(big_number_cmp_sign(multiplier, cease) == SMALLER)
        {
            big_number_mult_by(&res, multiplier);
            big_number_add_by(&multiplier, step);
        }
    }

    big_number_free(multiplier);
    big_number_free(cease);
    big_number_free(step);

    return res;
}



/* function: 
 * 
 * input:
 * return: */
big_number* big_number_divide(const big_number a, const big_number b)
{
    big_number mid;
    big_number temp;
    big_number dividor;
    big_number *ret, *quo, *remain;
    int pos_dividend;
    int pos_quo;
    int i;


    ret = (big_number*)malloc(sizeof(big_number)*2);
    quo = ret; // quotient
    remain = ret + 1; // remain

    // scenario where divider b is 0
    if(b.length == 1 && b.nums[0] == 0)
    {
        fputs("division error: divisor should not be 0!!\n", stdout);
        exit(0);
    }

    // scenario where dividend a is 0
    else if(a.length == 1 && a.nums[0] == 0)
    {
        *quo = big_number_set("0");
        *remain = big_number_set("0");
    }

    // scenario where quotient is 0
    else if(big_number_cmp_nosign(a,b) == SMALLER)
    {
        *quo = big_number_set("0");
        *remain = big_number_copy(a);
    }
    
    // scenario where short division is implemented
    else
    {
        // initialize relevant variables
        dividor = big_number_copy(b);
        dividor.sign = MINUS;

        mid.length = b.length;
        mid.sign = PLUS;
        mid.nums = (char*)malloc(sizeof(char)*(a.length));
        mid.nums += a.length - b.length;

        quo->length = a.length - b.length + 1;
        quo->nums = (char*)malloc(sizeof(char)*quo->length);
        memset(quo->nums, 0, quo->length);

        pos_quo = quo->length -1;

        // get higher digits for the first division
        for(pos_dividend = 0; pos_dividend < b.length; pos_dividend++)
            mid.nums[mid.length-1-pos_dividend] = a.nums[a.length-1-pos_dividend];

        // short division
        while(pos_dividend <= a.length)
        {
            // try the short division quotient
            while(big_number_cmp_nosign(mid, b) != SMALLER)
            {
                // minus divider till remainder smaller than divider
                temp = big_number_add(mid, dividor);
                while(temp.length < mid.length)
                {
                    mid.nums[mid.length-1] = 0;
                    mid.length--;
                }
                for(i = 0; i < temp.length; i++)
                    mid.nums[i] = temp.nums[i];

                big_number_free(temp);
                quo->nums[pos_quo]++;
            }

            // update the remainder
            if(pos_dividend < a.length)
            {
                mid.nums--;
                mid.length++;
                mid.nums[0] = a.nums[a.length - 1 - pos_dividend];
            }
            pos_quo--;
            pos_dividend++;
        }

        *remain = big_number_copy(mid);
        big_number_free(mid);
        big_number_free(dividor);

        // get rid of the zeros in the quotient high digits
        i = quo->length - 1;
        while(quo->length>1 && quo->nums[i] == 0)
        {
            quo->length--;
            i = quo->length - 1;
        }

        // calculate operators
        if(a.sign != b.sign)
        {
            quo->sign = MINUS;
            if(a.sign == MINUS)
                remain->sign = MINUS;
        }
        else if(a.sign == MINUS)
            remain->sign = MINUS;
    }

    return ret;
}


/* function: 
 * 
 * input:
 * return: */
inline big_number big_number_copy(const big_number a)
{
    big_number res;

    res = a;
    res.nums = (char *)malloc(sizeof(char)*res.length);
    memcpy(res.nums, a.nums, res.length);

    return res;
}


// debug
void print(const big_number a)
{
    big_number_print(a);
}



