#include<tuple>
#include<iostream>
#include<string>
#include<cxxabi.h>


class Obj {
    public:
        int a;
};


void try_tuple();

int main() {
    try_tuple();
    return 0;
}


void try_tuple() {
    using namespace std;

    // tuple<int, double> t = make_tuple(1,2.3);
    // auto t = make_tuple(1,2.3);
    auto t = make_tuple("name", "Coin");
    cout << std::get<0>(t) << ", " << std::get<1>(t) << endl;
    // cout << typeid(t).name() << endl;
    
    string name = abi::__cxa_demangle(typeid(t).name(), nullptr, nullptr, nullptr);
    cout << name << endl;

    string key;
    string val;
    std::tie(key, val) = t;
    cout << key 
        << ", " 
        << val 
        << endl;
    get<0>(t) = "fffff";
    cout << key 
        << ", " 
        << val 
        << endl;

    auto lam = []{return Obj();};
    auto t2 = make_tuple(1, lam());
    cout << std::get<0>(t2) 
        << std::get<1>(t2).a 
        << endl;

    auto t_cat = std::tuple_cat(t2, t);
    cout << std::get<0>(t_cat) 
        << std::get<1>(t_cat).a 
        << std::get<2>(t_cat) 
        << std::get<3>(t_cat) 
        << endl;
    get<2>(t_cat) = "hello";
    cout << std::get<0>(t_cat) 
        << std::get<1>(t_cat).a 
        << std::get<2>(t_cat) 
        << std::get<3>(t_cat) 
        << endl;
    cout << key << endl;
    cout << std::get<0>(t) << endl; 

    std::tuple_element<0, decltype(t_cat)>::type mm = 40;
    cout << mm << endl;

    cout << std::tuple_size<decltype(t_cat)>::value << endl;

}

