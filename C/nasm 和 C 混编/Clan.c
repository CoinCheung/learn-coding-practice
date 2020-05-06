#include<stdio.h>
#include<string.h>


extern void myprint(char * str, int len);


int compare(int a, int b)
{
    char *str1 = "a is larger than b\r\n";
    char *str2 = "a is smaller than b\r\n";

    if(a > b)
//        myprint(str1,strlen(str1));
        myprint(str1,29);
    else
 //       myprint(str2,strlen(str2));
        myprint(str2,20);

    return a - b ;
}


void main()
{
    /* printf("%d\n",compare(3,4)); */
}



