#include<sstream>
#include<stdio.h>
#include<iostream>


void tryTrap()
{
    using namespace std;


    stringstream ss("fjfjfjjfjfjf");
    stringstream ss_t("1111111");
    string str1(ss.str());

    const char* cstr1 = ss.str().c_str();
    const char* cstr2 = ss.str().c_str();
    const char* cstr3 = ss.str().c_str();

    cout << str1.c_str() << endl;
    cout << cstr1 << endl;
    cout << cstr2 << endl;
    cout << cstr3 << endl;

    cout << "here at 20180127" << endl;
    ss.str("");
    ss << "good morning";
    ss >> str1 >> str1;
    ss >> str1;
    cout << "before clear, str1 is: " << str1 << endl;
    ss.clear();
    // ss.seekg(0, ios::beg);
    ss >> str1;
    cout << "after clear, str1 is: " << str1 << endl;

    int mmm[3]{1, 300, 44};
    cout << "mmm is: " << mmm << endl;

    int nnn(88);
    cout << "nnn is: " << typeid(nnn).name() << endl;
}

int main()
{
    using namespace std;


    stringstream ss;
    ss << "good morning";
    ss << "fuck you bitch";

    string str;

    ss >> str;
    cout << str << endl;

    str = ss.str();
    cout << str << endl;

    ss >> str;
    cout << str << endl;

    ss >> str;
    cout << str << endl;

    ss >> str;
    cout << str << endl;

    cout << "here" << endl;
    ss.clear();
    ss >> str;
    cout << str << endl;

    ss >> str;
    cout << ss.str() << endl;

    ss.clear();
    cout << "here" << endl;
    ss.str("fuck you pussy");
    while(ss >> str)
        cout << str;
    // cout << res << endl;
    //
    cout << endl;
    const char* cp = ss.str().c_str();
    cout << cp << endl;

    cout << "here" << endl;
    ss.str("");
    int n = 12345;
    string sss;
    ss.clear();
    ss << n;
    ss >> str; 
    // str = ss.str();
    cout << str << endl;

    str = "2345";
    ss.str("");
    ss.clear();
    ss << str;
    ss >> n;
    cout << n << endl;

    str = "fuck";
    cout << str << endl;
    char ccp[200];
    ss.str("");
    ss.clear();
    ss << str;
    ss >> ccp;
    cout << ccp[5];
    // fprintf(stdout, "%c\n", ccp[1]);

    ss.str("");
    ss.clear();
    ccp[4] = 'm';
    ss << ccp;
    ss >> str;
    cout << str << endl;



    str = "11234";
    ss.str("");
    ss << str;
    ss >> str;
    cout << str << endl;
    ss >> str;
    cout << str;

    bool b; 
    if(ss>>str);
    cout << b << endl;
    
    cout << "here" << endl;
    str = "11111111";
    string str_t = "fjfjfjfjfj";
    ss.str("");
    ss.clear();
    ss << str;

    str = "";
    ss >> str;
    // str = ss.str();
    cout << str << endl;

    cp = ss.str().c_str();
    cout << ss.str().c_str() << endl;
    cout << cp << endl;

    tryTrap();

    return 0;
}
