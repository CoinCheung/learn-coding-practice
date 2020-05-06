#include<fstream>
#include<vector>
#include<iostream>
#include<iterator>
#include<string>
#include<sstream>
#include<algorithm>


void try_iter_string();

int main() {
    try_iter_string();

    return 0;
}


void try_iter_string() {
    using namespace std;

    string str;
    ifstream fin("../CMakeLists.txt", ios_base::in | ios_base::binary);
    // stringstream fin;
    // fin.str("good afternoon");

    auto st = istreambuf_iterator<char>(fin);
    auto ed = istreambuf_iterator<char>();
    // str.assign(st, ed);
    // cout << str << endl;

    str.clear();
    cout << "after clear()" << str.size() << str << endl;

    // fin.str("good afternoon");
    fin.clear();
    fin.seekg(0);
    std::copy_n(st, 6, std::back_inserter(str));
    cout << str << endl;
    str.clear();
    str.resize(6);
    auto sst = istreambuf_iterator<char>(fin);
    ++sst;
    std::copy_n(sst, 6, std::begin(str));
    cout << str << endl;

    // str.clear();
    // fin >> str;
    // cout << str << endl;

// TODO: std::copy_n
// istreambuf_iter get current position
// back_inserter

    // fin.clear();
    // fin.seekg(0);
    // str.clear();
    // str.resize(10);
    // fin.read(&str[0], 10);
    // cout << str << endl;

    stringstream ss;
    ss.str("abcdefghij");
    str.clear();
    str.resize(10);
    std::copy_n(istreambuf_iterator<char>(ss), 5, str.begin());
    cout << str << endl;
    std::copy_n(istreambuf_iterator<char>(ss), 5, str.begin());
    cout << str << endl;
}
