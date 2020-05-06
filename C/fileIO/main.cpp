
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


int main() {
    int len = 10240;
    vector<char> buf(len);
    for (int i{0}; i < len; ++i) {
        buf[i] = static_cast<char>('a' + i);
    }

    ofstream fout("temp.log", ios::out | ios::binary);
    fout.write(&buf[0], len);

    ifstream fin("temp.log", ios::in | ios::binary);
    fin.seekg(0, ios::end);
    int size = fin.tellg();
    fin.clear();
    fin.seekg(0, ios::beg);

    cout << size << endl;


    return 0;
}
