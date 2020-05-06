#include<random>
#include<time.h>
#include<iostream>

using namespace std;


void print_rand();
void try_org();
void try_seed();


int main() {
    cout << "try seed: " << endl;
    try_seed();


    return 0;
}

void try_org() {
    default_random_engine e;
    e.seed(10);
    cout << "random min: " << e.min() << endl;
    cout << "random max: " << e.max() << endl;
    cout << e() << endl;

    uniform_int_distribution<int> ui(0, 3);
    for (int i{0}; i < 20; ++i) {
        cout << ui(e) << endl;
    }

    cout << endl << endl << endl;
    uniform_real_distribution<double> ur(0, 9.0);
    for (int i{0}; i < 20; ++i) {
        cout << ur(e) << endl;
    }
    
    cout << endl << endl << endl;
    normal_distribution<double> n(0, 10);
    for (int i{0}; i < 20; ++i) {
        cout << n(e) << endl;
    }

    cout << endl << endl << endl;
    for (int i{0}; i < 20; ++i) {
        print_rand();
    }
}

void print_rand() {
    // std::random_device rd;
    // std::mt19937 e(rd());
    static default_random_engine e(time(0));
    uniform_real_distribution<> u(0, 1);

    cout << u(e) << endl;
}


void try_seed() {
    random_device rd;
    mt19937 e(rd());

    e.seed(123);
    uniform_real_distribution<double> u(0, 1);
    cout << u(e) << endl;
    e.seed(123);
    cout << u(e) << endl;

}
