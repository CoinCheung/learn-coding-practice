#include<fstream>
#include<iostream>
#include<assert.h>


class A
{
    public:
        A()
        {
            std::cout << "construction called" << std::endl;
        }

        ~A()
        {
            std::cout << "deconstruction called" << std::endl;
        }
};

int main()
{
    using namespace std;

    A a;
    fstream f;

    f.open("file.txt", ios::in);
    // assert(fstream f("file.txt", ios::in));
    // assert(f);
    if(!f)
    {
        cout << "open file failed!" << endl;
    }
    else
        cout << "open file successful" << endl;

    int m;
    f >> m;
    f.close();
    cout << "file closed" << endl;


    return 0;
}

