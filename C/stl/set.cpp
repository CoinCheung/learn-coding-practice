#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

void try_set();

int main() {
    try_set();
    return 0;
}

void try_set() {
    set<int> ss{1, 2, 3, 3, 3, 3, 4};
    for (auto &el : ss) {
        cout << el << ", ";
    }
    cout << endl;

    multiset<int> mss{1, 2, 3, 3, 3, 3, 3, 4, 5};
    for (auto &el : mss) {
        cout << el << ", ";
    }
    cout << endl;

    auto lo = mss.lower_bound(3);
    auto up = mss.upper_bound(3);
    cout << *lo << endl;
    cout << *up << endl;
    int diff = distance(lo, up);
    advance(lo, diff);
    cout << *lo << endl;

    // cout << distance(lo, up) << endl;

}
