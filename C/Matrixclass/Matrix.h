#ifndef _MATRIX_H_
#define _MATRIX_H_

/* 
 * only basic data types supported
 *  */

/* ********************************************************* 
 * header files
 ********************************************************* */
#include<iostream>

extern "C"
{
#include<cblas.h>
#include"testlibs.h"
}


/* ********************************************************* 
 * usings
 ********************************************************* */
using std::cout;
using std::endl;
using std::exit;




/* ********************************************************* 
 * macros and types
 ********************************************************* */


/* ********************************************************* 
 * definitions
 ********************************************************* */
template <class T>
class Matrix2
{
    public:
        // data
        int N;
        int D;
        long ele_num;
        T *data; 

        // functions
        Matrix2(int n, int d);
        Matrix2(int n);
        ~Matrix2();

        static Matrix2 ones(int N, int D);
        static Matrix2 ones(int N);

        static Matrix2 zeros(int N, int D);
        static Matrix2 zeros(int N);
        void print();

        static Matrix2 dot(Matrix2 a, Matrix2 b);
        void dot(const Matrix2 m);
        
};



/* ********************************************************* 
 * implementations
 ********************************************************* */

/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(int n, int d)
{
    N = n;
    D = d;
    ele_num = n * d;
    data = (T*)malloc(sizeof(T)*ele_num);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(int n)
{
    N = n;
    D = 1;
    ele_num = n;
    data = (T*)malloc(sizeof(T)*ele_num);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::~Matrix2()
{
    free(data);
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::ones(int N, int D)
{
    Matrix2 ret(N,D);
    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 1;

    return ret;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::ones(int N)
{
    Matrix2 ret(N);
    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 1;

    return ret;
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::zeros(int N, int D)
{
    Matrix2 ret(N,D);
    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 0;

    return ret;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::zeros(int N)
{
    Matrix2 ret(N);
    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 0;

    return ret;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::print()
{
    long pos;
    pos = 0;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < D; j++, pos++)
            cout<< data[pos] << " ,";
        cout<<endl;
    }

}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::dot(const Matrix2<T> m)
{
    const int N = this->N;
    const int D = this->D;
    const int C = m.N;
    const int M = m.D;

    double res;

    // check if two matrices match in shape
    if(D != C)
    {
        cout<< __FILE__<<":"<<__LINE__<<"ERROR: shape of two matrices should match to each other"<<endl;
        exit(1);
    }

    // scenario where this and m are vectors
    if(D == 1)
    {
        cblas_dger(CblasRowMajor, N, M, 1, this->data, 1, m.data, 1, this->data, M);
    }
    else if(N == 1 && M == 1)
    {
        res = cblas_ddot(D, this->data, 1, m.data, 1);
    }

    else if(N == 1 && M != 1)
        cblas_dgemv(CblasRowMajor, CblasTrans, C, M, 1, m.data, M, this->data, 1, 0, this->data, 1);

    // scenario where a is matrix and b is vector
    else if(M == 1 && N != 1)
        cblas_dgemv(CblasRowMajor, CblasNoTrans, N, D, 1, this->data, D, m.data, 1, 0, this->data, 1);

    // scenario where a and b are matrices
    else
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, M, D, 1, this->data, D, m.data, M, 0, this->data, M);


}



//////////////////////////

class A
{
    public:
        double *data;
        int N;
        int D;

        A();
        ~A();
        void print();
};


A::A()
{
    data = (double*)malloc(sizeof(double)*N*D);
}

A::~A()
{
    free(data);
}

void A::print()
{
    const int DD = 5;
    // double *dd;
    //
    // dd = data;

    // double *a = new double[D];
    
    // d = dynamic_cast<double(*)[D]>(a);

    double (*d)[DD];
    // d = new double[2][5];(double(*)[D])
    // d = static_cast<double (*)[5]>(malloc(sizeof(double)*10));
    d = reinterpret_cast<double (*)[DD]>(data);
    // d = (double(*)[DD])data;
    // int aa[D];
    

    // d = (double(*)[DD])this->data;
    for(int i = 0; i < N; i++)
        cout << d[i] <<endl;
}


#endif
