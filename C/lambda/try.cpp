#include<iostream>
#include<algorithm>
#include<memory>
#include<vector>
#include<map>
#include<functional>

using std::cout;
using std::endl;

void try_function(void);


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

    return 0;

}



void try_function(void)
{
    std::function<int(int)> ld = [](int val){return val+1;};
}
