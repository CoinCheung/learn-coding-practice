#include<iostream>
#include<array>
#include<vector>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <set>
#include <unordered_set>
#include<map>
#include <algorithm>



void array_example();
void copy_or_not();
void equal();
void copy();
void insection();


int main(void)
{

    // array_example();

    // copy_or_not();

    // equal();

    // copy();
    
    insection();

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

    cout << "here\n";
    cout << mp2[6] << endl;
    cout << mp2.count(6) << endl;
    mp2.insert(make_pair<int, int>(666, 7));
    cout << mp2[666] << endl;
}


void equal() {
    using namespace std;
    vector<int> v1{1,2,2,4,5};
    vector<int> v2{1,2,3,4,5};
    if (std::equal(std::begin(v1), std::end(v1), std::begin(v2))) {
        cout << "same \n";
    } else {
        cout << "not same \n";
    }
}

void copy() {
    using namespace std;
    vector<unsigned char> v{3, 13, 23, 83};
    stringstream ss;
    for (auto &el : v)
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(el);
    cout << ss.str() << endl;

    ss.str("");
    ss.clear();
    std::copy(
        std::begin(v),
        std::end(v),
        std::ostream_iterator<int>(ss << std::hex << std::setw(2) << std::setfill('0'))
    );
    cout << ss.str() << endl;
    cout << std::hex << std::setw(2) << std::setfill('0');
    cout << 3 << endl;
    cout << 3 << endl;
}


template<typename T>
std::set<T> intersection_of(std::set<T>& a, std::set<T>& b) {
    using namespace std;
    unordered_set<T> dict;
    set<T> res;
    std::for_each(a.begin(), a.end(), [&](const T& n) {dict.insert(n);});
    std::for_each(
        b.begin(), 
        b.end(),
        [&](const T& n){if (dict.count(n) > 0) {res.insert(n);}
    });
    return res;
}


template<typename T1, typename T2>
std::vector<T1> map_common_keys(std::map<T1, T2>& m1, std::map<T1, T2>& m2) {
    using namespace std;
    vector<T1> res;

    auto it1 = m1.begin();
    auto it2 = m2.begin();
    auto m1_end = m1.end();
    auto m2_end = m2.end();
    while (it1 != m1_end && it2 != m2_end) {
        if (it1->first < it2->first) {
            ++it1;
        } else if (it1->first > it2->first) {
            ++it2;
        } else {
            res.emplace_back(it1->first);
            ++it1;
            ++it2;
        }
    }
    return res;
}

void insection() {
    using namespace std;
    set<int> s1{1, 3, 4, 5, 2}; // 自动排好的  
    set<int> s2{3, 2, 4, 5};
    // set<int> res; // 或者vector<int>
    vector<int> res; // 或者vector<int>  
    std::set_intersection(
        s1.begin(), s1.end(),
        s2.begin(), s2.end(), 
        std::inserter(res, res.begin()));

    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(cout, ", "));
    cout << endl;

    set<int> common = intersection_of<int>(s1, s2);
    std::copy(common.begin(), common.end(), std::ostream_iterator<int>(cout, ", "));
    cout << endl;

    map<string, int> m1{{"n3", 234}, {"n2", 190}, {"n5", 999}};
    map<string, int> m2{{"n8", 34}, {"n2", 2190}, {"n5", 799}};

    vector<string> res2 = map_common_keys<string, int>(m1, m2);
    std::copy(res2.begin(), res2.end(), std::ostream_iterator<string>(cout, ", "));
    cout << endl;

    set<int> s_emp;
    std::copy(
        std::begin(res), 
        std::end(res),
        std::inserter(s_emp, s_emp.begin())
    );
    cout << s_emp.count(4) << endl;
    std::copy(
            s_emp.begin(), s_emp.end(), ostream_iterator<int>(cout, ", ")
    );

}
