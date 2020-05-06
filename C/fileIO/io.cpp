#include<iostream>
#include<fstream>
#include<cmath>


void try_fstream();
void try_print_char();


int main() {
    using namespace std;

    int i = 100;
    const char *a = "yes";

    cout << "hello "
        "world" << endl;

    try_fstream();

    try_print_char();

    return 0;
}


void try_fstream() {
    using namespace std;

    ifstream fin("file.txt", ios_base::in | ios_base::binary);
    fin.seekg(0, fin.beg);
    cout << fin.tellg() << endl;

    int arr[10];
    for (auto &el : arr) el = 8;
    for (auto &el : arr) cout << el << endl;
}


void try_print_char() {
    unsigned char a;
    double b;
    a = 140;
    char c = static_cast<char>(a);
    b = static_cast<double>(static_cast<unsigned char>(c));
    std::cout << b << std::endl;

    // a = static_cast<char>(b);

    // std::cout << (doub)c << std::endl;
    // std::cout << (b + 127) / 255 << std::endl;

    // b = 2;
    // std::cout << static_cast<int>(sqrt(b)) << std::endl;

}
