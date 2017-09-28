#!/usr/local/bin/python
# -*- coding: utf-8 -*-
# filename: cffi_build.py


from cffi import FFI

ffibuild = FFI() #all work are down by an FFI object

# the 'r' is necessary, or '\n' will be treated as python syntax(enter pressed)
ffibuild.set_source("liboutput", r'''

        #include<stdio.h>


#define true 1
     typedef struct
     {
         int mm;
         int cc;
     } mystruct;


        int mmm = 2;
        //.source.c

// class mycls
// {
//     public:
//     int a = 1;
//     int b = 3;
//
//     void fun();
// }


void print(char str[])
{
    fputs("hello from cffi\n",stdout);
    fprintf(stdout, "the string input is: %s", str);
}


void longarray(long *a, int len)
{
    for(int i = 0; i < len; i++)
        a[i] = i;

}


long* returnarray()
{
    long *p = NULL;

    p = malloc(sizeof(long)*10);
    for(int i = 0; i < 10; i++)
        *(p+i) = i;

    return p;
}

void freearray(long *p)
{
    free(p);
}

void voidprint()
{
    fputs("string from C\n",stdout);
}

        ''') # cdef() and set_source()have no order

ffibuild.cdef(r'''


#define true 1

typedef char ch32;

     typedef struct
     {
         int mm;
         int cc;
     } mystruct;


        int mmm = 2;

    void print(char []);
    void longarray(long *a, int len);

    long* returnarray();
    void freearray(long *p);
    void voidprint();

        ''')
# cdef can contain global variables, type definitions, function declarisions, but no includes
# headers included should be put in the set_source() domain


if __name__ == '__main__':
    ffibuild.compile(verbose=True, debug=True)
