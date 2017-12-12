#ifndef _MATRIX_H_
#define _MATRIX_H_

/* 
 * This is a C Matrix calculus libray written by Coin:
 *
 * 1. This libary is heavily dependant on Openblas, with some functions merely a wrapper is Openblas functions. Thus, to use this library, openblas should first be compiled and installed. When gcc is utilized to compile, the '-lopenblas' link option should be added.
 *
 * 2. this lib depends on openblas(assigned by -lopenblas), numberic.h
 *
 *
 * the functions that is rewritable with openblas is:
 * Matrix_add_by(); // cblas_axpy
 * Matrix_scale(); // cblas_scale
 *
 *  */




/* ======================================================
 * includes
 * ====================================================== */
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
#include<cblas.h>
#include"numeric.h"


/* ======================================================
 * types and macros
 * ====================================================== */

/* definition of a 2 dimension matrix */
typedef struct
{
    int N;
    int D;
    long ele_num;
    double *data;
}Matrix;

/* definition of a 3 dimension matrix */
typedef struct
{
    int N;
    int D;
    int H;
    long ele_num;
    double *data;
}Matrix3;


/* ======================================================
 * function definitions
 * ====================================================== */






//deep copy a Matrix
Matrix Matrix_copy(const Matrix); 

// create a Matrix whose elements are gaussian random numbers 
Matrix Matrix_gaussian(const int, const int);



#endif
