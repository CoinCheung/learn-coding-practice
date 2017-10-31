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

    cout << "before function called " <<endl;

    A&& b = test_construct();

    for(int i = 0; i < 20; i++)
        cout << "b.data[i] is: "<< b.data[i] <<endl;

    // tryMatrix2();


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
    cout << "Matrix m is: " <<endl;
    m.print();
    m.free();
    n = Matrix2<double>::zeros(1,4);
    cout << "Matrix n is: " <<endl;
    n.print();
    n.free();

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
    // res = (m*2.0);
    // m = m * 2.0;
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


}
