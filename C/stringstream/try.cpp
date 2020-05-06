#include<sstream>
#include<string>
#include<stdio.h>
#include<iostream>
#include <fstream>


void try_string();
void try_startswith();
void try_binary();


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

    // tryTrap();


    // try_string();

    // try_startswith();

    try_binary();

    return 0;
}

void try_string()
{
    using namespace std;

    string str("I am coin cheung, nice to meet you");
    string token;
    // string res;

    token.assign("coin");
    cout << (str.find(token, 6) == string::npos) << endl;

    cout << str.rfind(token, 9) << endl;

    // res.assign(str);
    string res(str);
    // res.replace(2,2, "was");
    res.replace(res.begin()+2, res.end()-30, "was");
    cout << str << endl;
    cout << res << endl;

    cout << str[0] << endl;

    cout << "here we are" << endl;
    stringstream ss;
    ss << "123,456,789";
    ss.clear();
    int num;
    ss >> num;
    cout << num << endl;
    ss.seekg(1, ios::cur);
    ss.clear();
    ss >> num;
    cout << num << endl;
    ss.seekg(1, ios::cur);
    // ss.clear();
    ss >> num;
    cout << num << endl;

    string s1("fuck you all\n");
    string s2;
    cout << "before: \n";
    cout << s1.size() << endl;
    cout << s2.size() << endl;
    string(s1).swap(s2);
    cout << "after: \n";
    cout << s1.size() << endl;
    cout << s2.size() << endl;
    s1 = s2;
    cout << s1 << endl;
    cout << s2 << endl;
    s1[2] = 'd';
    cout << s1 << endl;
    cout << s2 << endl;

    cout << "start\n";
    cout << s2;
    string s3(std::move(s2));
    s2[2] = 'd';
    cout << "s2" << s2;
    cout << "s3" << s3;
    cout << "done\n";

    string& sref = s3;
    s3[2] = 'i';
    cout << s3;
    cout << sref;
    sref = s1;
    cout << sref;
    cout << s3;

    int a = 10;
    int& b = a;
    int c = 20;
    cout << a << endl;
    cout << b << endl;
    b = c;
    cout << b << endl;
    
    ss.str();
    ss.clear();
    ss << "hello     world";
    while(ss >> res) cout << res;

}

bool startswith(std::string str, std::string token) {
    using namespace std;
    int len = token.size();
    cout << len << endl;
    cout << str.size() << endl;
    cout << str.substr(0, len+100) << endl;
    return str.substr(0, len) == token;
}

bool endswith(std::string str, std::string token) {
    int pos = str.size() - token.size();
    if (pos < 0) return false;
    return str.substr(pos) == token;
}

void try_startswith() {
    using namespace std;
    cout << "========="; 
    cout << "=========\n"; 
    // string str("i am coin cheung fuck you");
    // // string str("i a");
    // string token("i am");
    // bool flag = startswith(str, token);
    // string str("i am coin cheung fuck you");
    string str("i a");
    string token("fuck you");
    bool flag = endswith(str, token);
    if (flag) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
}

void try_binary() {
    using namespace std;

    string pth("./xxx.pb");
    ifstream fin(pth, ios::in | ios::binary | ios::ate);
    int len = fin.tellg();
    fin.seekg(0);

    cout << "compare: \n";
    string s1(len, 0);
    fin.read(&s1[0], len);
    for (auto &el : s1)
        cout << (int)el << ", ";
    cout << endl;

    fin.clear();fin.seekg(0);
    stringstream ss;
    fin >> std::noskipws >> ss.rdbuf();
    for (auto &el : ss.str())
        cout << (int)el << ", ";
    cout << endl;

}
