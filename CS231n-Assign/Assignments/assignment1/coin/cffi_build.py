#!/usr/local/bin/python
# -*- coding: utf-8 -*-
#filename: cffi_build.py


from cffi import FFI

ffibuild = FFI()

ffibuild.set_source("mylib",r'''
    // contents of assig1.h
    #include<math.h>
    #include<stdio.h>

    double cal_vector_dis(double *v1, double *v2, int len);
    double cal_vector_dis_direct(double *v1, double *v2, int len);
    double* cal_dists(double (**v1), double (**v2), int row1, int col1, int row2, int col2);
    void printhello(void);
    void freeheap(void *hp);

    // contents of assig1.c
    double cal_vector_dis_direct(double *v1, double *v2, int len)
    {
        double sum = 0;
        for(int i = 0; i < len ; i++)
            sum += (*(v1+i) - *(v2+i)) * (*(v1+i) - *(v2+i));

        return sqrt(sum);
    }


    double cal_vector_dis(double *v1, double *v2, int len)
    {
        double sum = 0;
        for(int i = 0; i < len ; i++)
            sum += (*(v1+i) - *(v2+i)) * (*(v1+i) - *(v2+i));

        return sqrt(sum);
    }


    double* cal_dists(double (**v1), double (**v2), int row1, int col1, int row2, int col2)
    {
        double (*res)[row2] = NULL;

        res =  (double (*)[row2])malloc(sizeof(double)*row1*row2);

        for(int i = 0; i < row1; i++)
        {
            for(int j = 0; j < row2; j++)
            {
                res[i][j] = cal_vector_dis(*(v1+i), *(v2+j), col1);
            }
      //      fprintf(stdout,"loop with i = %d and res[i][0] = %lf\n",i,res[i][0]);
        }

        return (double *)res;
    }


    void printhello()
    {
        fputs("hello by c\n",stdout);
    }

    void freeheap(void *hp)
    {
        free(hp);
    }

        ''')

ffibuild.cdef(r'''
    double cal_vector_dis(double *v1, double *v2, int len);
    double cal_vector_dis_direct(double *v1, double *v2, int len);
    double* cal_dists(double (**v1), double (**v2), int row1, int col1, int row2, int col2);
    void printhello();
    void freeheap(void *hp);

''')

if __name__ == '__main__':
    ffibuild.compile(verbose = True, debug = True)
