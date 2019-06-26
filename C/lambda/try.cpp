#include<iostream>
#include<algorithm>
#include<memory>
#include<vector>
#include<map>
#include<functional>

using std::cout;
using std::endl;
using std::vector;

void try_function(void);
void try_vec();
void try_idx_sort();


int main(void)
{
    int a = 100;
    int b = 100;
    cout << a << endl;
    auto la = [&]{a++;};
    // [&]{a++;};
    la();
    cout << a << endl;

    auto la2 = [&a, b]{return a+b;};
    auto re = la2();
    cout << re << endl;
    cout << a << endl;

    auto la3 = [&](int m){return m+a;};
    cout << la3(10) << endl;


    int arr[10];
    int i = 0;

    // std::for_each(std::begin(arr), std::end(arr), [&](auto x){*(long long)x = i++;})
    std::for_each(std::begin(arr), std::end(arr), [&](auto x){cout << typeid(x).name();});
    cout << "here: " << arr[3] << endl;

    for(int i = 0; i < 10; i++){arr[i]=i;}
    for(auto it:arr)
    {
        it = i++;
        cout << it << endl;
    }

    std::shared_ptr<int> sp(new int[10]);

    std::vector<int> vi = {1,2,3,4,5};
    for(auto& el:vi)
    {
        el = 888;
    }
    cout << "here" << endl;
    cout << vi[3] << endl;

    std::map<int, std::string> mymap = {{1,"first"}, {2, "second"}};
    for(auto el:mymap)
    {
        cout << el.first << endl;
        cout << el.second << endl;
    }

    cout << arr[2] << endl;
    i = 0;
    std::for_each(std::begin(arr), std::end(arr), [&](int& n){n=i++;});
    for(auto num:arr)cout << num << endl;

    ///////
    //type
    int j = 10;
    auto val_ = [=]()mutable{j++;std::cout << j << std::endl;};

    val_();
    // j++;
    val_();
    cout << j << endl;

    try_function();
    try_vec();
    try_idx_sort();

    return 0;

}


void try_vec() {
    using namespace std;
    auto f0 = [] {cout << "first" << endl;};
    // decltype(f0) f1;
    // decltype(f0) f1 = [] {cout << "second" << endl;};
    // decltype(f0) f2 = [] {cout << "third" << endl;};


    f0();
    string str("fuck you asshole");
    auto t2= str.end();
    for (auto t1{str.begin()}; t1 != t2; ++t1) cout << *t1;
    cout << endl << *(t2 - 5) << endl;
    auto t1{str.begin()};
    cout << endl << *(t2 - 5) << endl;
    cout << t1[2] << endl;
    int a[10];
    auto ta = std::begin(a);
    ta[2] = 4;
    cout << ta[2] << endl;
    // f1();
    // f2();


    // vector<decltype(f0)> fv{f0, f1};
    // fv.push_back(f0);
    // fv.push_back(f1);
    // fv.push_back(f2);

    // for (auto &f : fv) f();
}


void try_function(void)
{
    std::function<int(int)> ld = [](int val){return val+1;};
}


void try_idx_sort() {
    vector<int> v{4, 5, 2, 7, 1, 9, 8};
    vector<int> indices(v.size());
    for (int i{0}; i < v.size(); ++i) {
        indices[i] = i;
    }
    std::sort(
        indices.begin(),
        indices.end(),
        [&v](int id1, int id2) {return v[id1] > v[id2];}
    );

    for(int i{0}; i < v.size(); ++i) {
        cout << v[i] << ", ";
    }
    cout << endl;
    for(int i{0}; i < v.size(); ++i) {
        cout << indices[i] << ", ";
    }
    cout << endl;
}
