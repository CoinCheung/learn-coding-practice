#include"Matrix.h"



void tryMatrix2();
A test_construct();



int main(void)
{
    cout<< "long time no see c++" <<endl;

    //
    // Matrix2<double> m(3,3);

    // Matrix2<double> mm = Matrix2<double>::ones(3,3);
    // mm.print();

    // A a;
    // a.print();

    // printlines();

    // tryMatrix2();

    // A b;

    // cout << "before function called " <<endl;
    //
    // A&& b = test_construct();
    //
    // for(int i = 0; i < 20; i++)
    //     cout << "b.data[i] is: "<< b.data[i] <<endl;

    tryMatrix2();


    return 0;
}


A test_construct()
{
    A a;
    A b;

    a.N = 100;
    for(int i = 0; i < 20; i++)
        a.data[i] = 5555;

    cout << "before assign a to b"<<endl;
    b = a;
    cout << "after assign a to b"<<endl;

    // return a;
    return std::move(a);
}


void tryMatrix2()
{
    Matrix2<double> res;
    Matrix2<double> m;
    Matrix2<double> n;

    // cout << "zeros(4)"<<endl;
    // m = Matrix2<double>::zeros(4);
    // cout << "Matrix m is: " <<endl;
    // m.print();

    cout << "ones(4,5)"<<endl;
    m = Matrix2<double>::zeros(4,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::zeros(1,4);
    cout << "Matrix n is: " <<endl;n.print();
    m.free();n.free();

    m = Matrix2<double>::ones(5,4);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(4,1);
    cout << "Matrix n is: " <<endl;n.print();
    res = Matrix2<double>::dot(m,n);
    cout << "static dot result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,1);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(1,5);
    cout << "Matrix n is: " <<endl;n.print();
    res = Matrix2<double>::dot(m,n);
    cout << "static dot result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(1,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,1);
    cout << "Matrix n is: " <<endl;n.print();
    res = Matrix2<double>::dot(m,n);
    cout << "static dot result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(1,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,5);
    cout << "Matrix n is: " <<endl;n.print();
    res = Matrix2<double>::dot(m,n);
    cout << "static dot result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,1);
    cout << "Matrix n is: " <<endl;n.print();
    res = Matrix2<double>::dot(m,n);
    cout << "static dot result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,6);
    cout << "Matrix n is: " <<endl;n.print();
    res = Matrix2<double>::dot(m,n);
    cout << "static dot result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,1);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(1,6);
    cout << "Matrix n is: " <<endl;n.print();
    m.dot(n);
    cout << "m.dot(n) result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(1,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,3);
    cout << "Matrix n is: " <<endl;n.print();
    m.dot(n);
    cout << "m.dot(n) result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,1);
    cout << "Matrix n is: " <<endl;n.print();
    m.dot(n);
    cout << "m.dot(n) result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,6);
    cout << "Matrix n is: " <<endl;n.print();
    m.dot(n);
    cout << "m.dot(n) result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,6);
    cout << "Matrix n is: " <<endl;n.print();
    res = ((m*2.0).dot(n));
    // res = (2.0*m);
    m = m * 2.0;
    cout << "Matrix m*2.dot(n) is: " <<endl;res.print();
    // cout << "m*2.0 result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,6);
    cout << "Matrix n is: " <<endl;n.print();
    res =  Matrix2<double>::dot(m,n);
    cout << "dot(m,n) result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,6)*2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  Matrix2<double>::dot(m,n)*2.0;
    cout << "dot(m,n) result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,5)*2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m*n;
    cout << "m*n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(1,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,5)*2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m*n;
    cout << "m*n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,1);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,5)*2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m*n;
    cout << "m*n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(1,5)*2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m*n;
    cout << "m*n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(5,5);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(5,5)+2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m+n;
    cout << "m*n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(1,6);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(4,6)/2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m/n;
    cout << "m/n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,6);
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(1,1)*2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m*n;
    cout << "m*n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(1,1)+3;
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(1,1)+2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m+n;
    cout << "m+n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,6)-3;
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(4,6)-2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  m-n;
    cout << "m+n result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,6)-3;
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(4,6)-2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  2.0*m;
    cout << "2*m result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,6)+3;
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(4,6)+2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  2.0/m;
    cout << "2/m result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,6)+3;
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(4,6)+2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  2.0+m;
    cout << "2+m result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,6)+3;
    cout << "Matrix m is: " <<endl;m.print();
    n = Matrix2<double>::ones(4,6)+2;
    cout << "Matrix n is: " <<endl;n.print();
    res =  2.0-m;
    cout << "2-m result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,6)+3;
    cout << "Matrix m is: " <<endl;m.print();
    res = m.Trans();
    cout << "m.Trans() result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::ones(4,6)+3;
    cout << "Matrix m is: " <<endl;m.print();
    Matrix2<double>::Trans(m);
    cout << "Matrix2<T>.Trans(m) result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9)+3;
    cout << "Matrix m is: " <<endl;m.print();
    Matrix2<double>::Trans(m);
    cout << "Matrix2<T>.Trans(m) result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9,19);
    cout << "Matrix m is: " <<endl;m.print();
    Matrix2<double>::Trans(m);
    cout << "Matrix2<T>.Trans(m) result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9,19);
    cout << "Matrix m is: " <<endl;m.print();
    Matrix2<double>::reshape(m, 2, 5);
    cout << "Matrix2<T>.reshape(m, n, d) result is: " <<endl;m.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9,19);
    cout << "Matrix m is: " <<endl;m.print();
    res = m.reshape(2, 5);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    Matrix2<double>::Trans(res);
    cout << "Matrix2<T>.Trans(res) result is: " <<endl;res.print();
    m.free(); n.free(); res.free();

    m = Matrix2<double>::arange(9);
    cout << "Matrix m is: " <<endl;m.print();
    res = m.reshape(3, 3);
    cout << "m.reshape(n, d) result is: " <<endl;res.print();
    res = res.Trans();
    cout << "res.Trans(res) result is: " <<endl;res.print();
    m.free(); n.free(); res.free();
}
