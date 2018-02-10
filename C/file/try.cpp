#include<fstream>
#include<assert.h>
#include<iostream>
#include<string>


int main(void)
{
    using namespace std;

    // create a file
    fstream f;
    f.open("file.txt", ios::out);
    assert(f);
    f << "fuck you";
    f.close();


    // open the same file for several times
    fstream fin1;
    fstream fin2;
    fstream fin3;

    fin1.open("file.txt", ios::in);
    assert(fin1);
    fin2.open("file.txt", ios::out|ios::in);
    assert(fin2);
    fin3.open("file.txt", ios::in);
    assert(fin3);


    string all;
    string str;
    fin1 >> all;
    fin1 >> str;
    all = all + str;
    cout << "read from fin1 is:" << all << endl; // 啥也没有，因为之前ios::out 打开时都给清了。
    
    str = "good morning, bitch";
    fin2 << str;
    fin2.flush();
    // cout << "read from fin2 is:" << str << endl;

    all = "";
    while(fin3 >> str)
    {
        all += str;
    }

    cout << "read from fin3 is:" << all << endl;


    return 1;
}
