#include<stdlib.h>
#include<stdio.h>

#define fun(type) \
/* type add(type a, type b) \ */
/* { \ */
/*     return a + b; \ */
/* } */

fun(int)

/* int main()
 * {
 *     int res;
 *
 *     res = add(1,2);
 *     fprintf(stdout, "number is %d\n",res);
 *     return 0;
 * } */


/* _QUEUE_DEF(int) */

#define str(s) #s

#define print(s) fprintf(stdout, "s is %s\n", str(s));

int max(int a, int b);
void swap(int *a, int *b);

inline int max(int a, int b)
{
    return a>b?a:b;
}

inline void swap(int *a, int *b)
{
    *a = (*a)^(*b);
    *b = (*a)^(*b);
    *a = (*a)^(*b);
}

#include"datastr.h"
// extern int a;

int main()
{
    /* _QUEUE(int) qu; */
    struct queue qu;
    init_queue(&qu);
    qu.add(4,&qu);
    qu.printrear(&qu);
    
    /* fprintf(stdout, "the string is: %s\n", str(this is a string)); */
    /* fputs(str(this is a string),stdout);  */
    /*  */
    /* print(s in the macro) */
    /* fprintf(stdout,"max of 1 and 2 is: %d\n", max(1,2)); */
    /*  */
    /* int a = 5; */
    /* int b = 6; */
    /* fprintf(stdout,"before swap, numbers are: %d and %d\n",a,b); */
    /* swap(&a, &b); */
    /* fprintf(stdout,"after swap, numbers are: %d and %d\n",a,b); */

    /* func(1); */
    /* fprintf(stdout,"var a is: %d\n",a); */

    return 0;
}
