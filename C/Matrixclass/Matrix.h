#ifndef _MATRIX_H_
#define _MATRIX_H_

/* 
 * only basic data types supported
 *  */

/* ********************************************************* 
 * header files
 ********************************************************* */
#include<iostream>
#include<cstring> // memcpy

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
using std::memcpy;
using std::memset;




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
        Matrix2();
        Matrix2(int n, int d);
        Matrix2(int n);
        Matrix2(Matrix2& m); // copy construction
        Matrix2(Matrix2&& m); // moving construction
        ~Matrix2();

        Matrix2& operator=(Matrix2& m); // copy assignment
        Matrix2& operator=(Matrix2&& m); // moving assignment

        static Matrix2 ones(const int N, const int D);
        static Matrix2 ones(const int N);

        static Matrix2 zeros(const int N, const int D);
        static Matrix2 zeros(int N);

        void print();
        void free();

        static Matrix2 dot(const Matrix2& a, const Matrix2& b);
        Matrix2 dot(const Matrix2& m);

        Matrix2& operator*(const Matrix2& m);
        Matrix2& operator*(const T m);
        
};



/* ********************************************************* 
 * implementations
 ********************************************************* */

/* function:
 * instruction: copy construction
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(Matrix2<T>& m): N(m.N), D(m.D), ele_num(m.ele_num), data(new T[ele_num])
{
    cout << "copying"<<endl;
    memcpy(data, m.data, ele_num*sizeof(T));
}



/* function:
 * instruction: moving construction
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(Matrix2<T>&& m): N(m.N), D(m.D), ele_num(m.ele_num), data(m.data) 
{
    cout << "moving construct" <<endl;
    m.data = NULL;
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(): N(0), D(0), data(NULL)
{
}



/* function:
 * instruction: construct with two dimensions
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(int n, int d): N(n), D(d), ele_num(n*d), data(new T[ele_num])
{
}



/* function:
 * instruction: construct with one dimension(a vector)
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::Matrix2(int n): N(n), D(1), ele_num(n), data(new T[ele_num])
{
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>::~Matrix2()
{
    cout << "deconstructing..." <<endl;
    delete[] data;
}



/* function:
 * instruction: copy assignment
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>& Matrix2<T>::operator=(Matrix2<T>& m) 
{
    cout << "direct assign" <<endl;
    this->N = m.N;
    this->D = m.D;
    this->ele_num = m.ele_num;
    delete(this->data);
    this->data = m.data;

    return *this;
}



/* function:
 * instruction: moving assignment 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>& Matrix2<T>::operator=(Matrix2<T>&& m)
{
    cout << "moving assign"<<endl;
    this->N = m.N;
    this->D = m.D;
    this->ele_num = m.ele_num;
    this->data = m.data;
    m.data = NULL;

    return *this;
}

/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::ones(const int N, const int D)
{
    Matrix2<T> ret(N,D);

    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 1;

    return std::move(ret); // return a right value so that moving construct called instead of memory copy
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::ones(const int N)
{
    Matrix2<T> ret(N);

    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 1;

    return std::move(ret);
}


/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::zeros(int N, int D)
{
    Matrix2<T> ret(N,D);

    for(long i = 0; i < ret.ele_num; i++)
        ret.data[i] = 0;

    return std::move(ret);
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

    return std::move(ret);
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

    cout << "[ " <<endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < D; j++, pos++)
            cout<< data[pos] << ", ";
        cout<<endl;
    }
    cout << "] " <<endl;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
void Matrix2<T>::free()
{
    delete [] data;
    data = NULL;
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::dot(const Matrix2<T>& m)
{
    const int N = this->N;
    const int D = this->D;
    const int C = m.N;
    const int M = m.D;

    Matrix2<T> res(N,M);

    // check if two matrices match in shape
    if(D != C)
    {
        cout<< __FILE__<<":"<<__LINE__<<"ERROR: shape of two matrices should match to each other"<<endl;
        exit(1);
    }

    // scenario where this and m are vectors
    if(D == 1)
        cblas_dger(CblasRowMajor, N, M, 1, this->data, 1, m.data, 1, res.data, M);
    //scenario where a and b are vectors, and, by shape, inner product is computed
    else if(N == 1 && M == 1)
        *res.data = cblas_ddot(D, this->data, 1, m.data, 1);
    // scenario where a is a h vector and b is a matrix
    else if(N == 1 && M != 1)
        cblas_dgemv(CblasRowMajor, CblasTrans, C, M, 1, m.data, M, this->data, 1, 0, res.data, 1);
    // scenario where a is matrix and b is vector
    else if(M == 1 && N != 1)
        cblas_dgemv(CblasRowMajor, CblasNoTrans, N, D, 1, this->data, D, m.data, 1, 0, res.data, 1);
    // scenario where a and b are matrices
    else
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, M, D, 1, this->data, D, m.data, M, 0, res.data, M);

    return std::move(res);
}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T> Matrix2<T>::dot(const Matrix2<T> &a, const Matrix2 &b) 
{
    const int N = a.N;
    const int D = a.D;
    const int C = b.N;
    const int M = b.D;

    // check if two matrices not match in shape
    if(D != C)
    {
        cout <<"ERROR: "<<  __FILE__ << ": " << __LINE__ << ": "<< "the two input matrices should match each other in their shapes" << endl;
        exit(0);
    }

    Matrix2<T> res = Matrix2<T>::zeros(N,M);

    // scenario where a and b are vectors, compute their outer product
    if(D == 1)
        cblas_dger(CblasRowMajor, N, M, 1.0, a.data, 1, b.data, 1, res.data, M);
    
    // scenario where a and b are vectors, and inner product computed
    else if(N == 1 && M == 1)
        res.data[0] = cblas_ddot(D, a.data, 1, b.data, 1);

    // scenario where a is vector and b is matrix
    else if(N == 1 && M != 1)
        cblas_dgemv(CblasRowMajor, CblasTrans, C, M, 1, b.data, M, a.data, 1, 0, res.data, 1);

    // scenario where a is matrix and b is vector
    else if(M == 1 && N != 1)
        cblas_dgemv(CblasRowMajor, CblasNoTrans, N, D, 1, a.data, D, b.data, 1, 0, res.data, 1);

    // scenario where a and b are matrices
    else
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, M, D, 1, a.data, D, b.data, M, 0, res.data, M);

    return std::move(res);
}





/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>& Matrix2<T>::operator*(const Matrix2& m)
{

}



/* function:
 * instruction: 
 * input:
 * return:
 *  */
template<class T>
Matrix2<T>& Matrix2<T>::operator*(const T m)
{
    for(long i = 0; i < ele_num; i++)
        data[i] *= m;

    Matrix2<T>&& res = std::move(*this);

    return res;
}

//////////////////////////

class A
{
    public:
        double *data;
        int N;
        int D;

        A();
        A(const A& a);
        A(A&& a);
        ~A();
        void print();
        A& operator=(A &a);
        A& operator=(A&& a);
        A* copy();
};


A& A::operator=(A& a)
{
    cout << "operator = called" <<endl;
    this->N = a.N;
    this->D = a.D;
    free(this->data);
    this->data = (double*)malloc(sizeof(double)*D*N);
    memcpy(this->data, a.data, a.N*a.D*sizeof(double));
    return *this;
}


A& A::operator=(A&& a)
{
    cout << "moving operator = called" <<endl;
    this->N = a.N;
    this->D = a.D;
    free(this->data);
    this->data = a.data;
    a.data = NULL;
    return *this;
}


// A& A::operator=(A& a)
// {
//     cout << "moving operator = called" <<endl;
//     this->N = a.N;
//     this->D = a.D;
//     this->data = a.data;
//     a.data = NULL;
//     return *this;
// }


A::A()
{
    N = 5;
    D = 4;
    data = (double*)malloc(sizeof(double)*N*D);
    cout << "A() called" <<endl;
}

A::A(const A& a)
{
    N = a.N;
    D = a.D;
    cout << "A(A& ) called" <<endl;
    this->data = (double*)malloc(D*N*sizeof(double));
    memcpy(this->data, a.data, D*N);
}


A::A(A&& a)
{
    N = a.N;
    D = a.D;
    data = a.data;
    a.data = NULL;
    cout << "A(A&& ) called" <<endl;
}

A::~A()
{
    cout << "destroying A" <<endl;
    free(data);
}

// A* A::copy()
// {
//     A res;
//     cout << "copying object " << endl;
//     return &res;
// }


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
