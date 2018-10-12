#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>


void try_algorithm();


int main() {
    try_algorithm();
    return 0;
}


void try_algorithm() {
    using namespace std;

    vector<int> vi(10);
    vector<int> res(10);

    for (int i{0}; i < 10; ++i) vi[i] = i;
    transform(vi.begin(), vi.end(), res.begin(), [](int i)->int {return i << 1;});  // 没有安全检查，res不够长了就都舍弃了。
    // for (auto &el : res) cout << el << endl;

    ///
    vector<int>::iterator vp;
    vp = remove_if(vi.begin(), vi.end(), [](int i)->bool {return i % 2 == 1;});
    // for (auto p{vi.begin()}; p != vp; ++p) cout << *p << endl;

    ///
    for (int i{0}; i < 10; ++i) vi[i] = i;
    fill(res.begin(), res.end(), 0);
    vp = remove_copy_if(vi.begin(), vi.end(), res.begin(), [](int i)->bool {return i % 2 == 1;});
    // for (auto p{res.begin()}; p != vp; ++p) cout << *p << endl;
    for_each(res.begin(), vp, [](int v){cout << v << endl;});

    ///
    // for (int i{0}; i < 10; ++i) vi[i] = i;
    int i = 0;
    for_each(vi.begin(), vi.end(), [&](int& el) {el = i; ++i;});
    int rv = std::accumulate(vi.begin(), vi.end(), 0, [](int a, int b)->int {return a + b;});
    cout << "res is: " << rv << endl;


}

