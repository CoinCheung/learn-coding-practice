#include<iostream>
#include<array>
#include<vector>
#include<map>



void array_example();
void copy_or_not();

int main(void)
{

    // array_example();

    copy_or_not();

    return 0;
}


void array_example()
{
    using namespace std;

    array<array<int, 3>, 3> a{{{1,2,2},{4,5,6},{7,8,9}}};

    for(auto arr:a)
    {
        for(auto val:arr)
            cout << "number is: " << val << endl;

    }
}



void copy_or_not() {
    using namespace std;

    // vector
    cout << "assign directly\n";
    vector<int> vi;
    vi.resize(10);
    int i = 0;
    for (auto& el : vi) el = i ++;

    vector<int> v2;
    v2 = vi;
    v2[4] = 888;
    cout << vi[4] << endl;
    cout << v2[4] << endl;
    cout << &vi << endl;
    cout << &v2 << endl;

    cout << "assign std::move()\n";
    vector<int>().swap(v2);
    v2 = std::move(vi);
    std::move(vi);
    cout << &vi << endl;
    cout << vi.size() << endl;
    // v2[4] = 888;
    // cout << vi[4] << endl;
    // cout << v2[4] << endl;
    // cout << &vi << endl;
    // cout << &v2 << endl;



    // map
    cout << "maps \n";
    map<int, int> mp;
    for (int i{0}; i < 10; i ++) mp[i] = i << 1;
    map<int, int> mp2;

    mp2 = mp;
    cout << "assign directly\n";
    for (auto& el : mp2)  el.second = el.second << 1;
    cout << &mp << endl;
    cout << &mp2 << endl;
    cout << mp[3] << endl;
    cout << mp2[3] << endl;
    cout << "assign by moved\n";
    mp2.clear();
    mp2 = std::move(mp);
    cout << &mp << endl;
    cout << &mp2 << endl;
    cout << mp.count(4) << endl;
    cout << mp2.count(4) << endl;


}

