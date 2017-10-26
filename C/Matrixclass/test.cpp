#include"Matrix.h"



void tryMatrix2();



int main(void)
{
    cout<< "long time no see c++" <<endl;

    //
    Matrix2<double> m(3,3);

    Matrix2<double> mm = Matrix2<double>::ones(3,3);
    mm.print();

    // A a;
    // a.print();


    tryMatrix2();

    printlines();


    return 0;
}



void tryMatrix2()
{
    cout << "ones(4)"<<endl;
    Matrix2<double> m = Matrix2<double>::ones(4);
    m.print();

    Matrix2<double> n = Matrix2<double>::ones(1,4);
    m.dot(n);
    m.print();

}
