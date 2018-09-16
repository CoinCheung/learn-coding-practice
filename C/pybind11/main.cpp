#include<pybind11/pybind11.h>
#include<iostream>
#include<string>
#include<vector>
// #include"fun.h"

namespace py = pybind11;

py::list print_list(py::list li) {
    using namespace std;
    // cout << string(py::str(li[0])) << endl;
    // // cout << string(li[0]) << endl;
    // cout << "whole" << endl;
    //
    // for (auto& el : li) cout << string(py::str(el)) << endl;
    //
    // cout << "add one" << endl;
    // // int num = li[0];
    // // cout << string(py::str(li[0] + 1)) << endl;
    // cout << li[0] << endl;

    int list_len = py::len(li);
    int i{0};
    for (auto& item : li) {
        cout << item.cast<int>() << ", ";
        // li[i] = item.cast<int>() * 2;
        ++i;
    }
    cout << endl;

    int len{py::len(li)};
    for (int i{0}; i < len; ++i) li[i] = li[i].cast<int>() * 2;

    py::list list_res;
    // list_res = py::cast();

    // vector<int> res;
    // res.reserve(py::len(li));
    // res.emplace(3);
    // res.emplace(4);
    // res.emplace(5);
    // list_res = py::cast(res);
    // list_res = py::cast({1, 2, 3});

    list_res.append(1);
    list_res.append(2);
    list_res.append(3);
    list_res.append("good");
    // list_res[4] = 33;



    cout << "list len: " << py::len(li) + 4 << endl;
    cout << "res list: " << endl;

    return list_res;

    // for (auto item& : li) {
    //     cout << item.cast<int>() << ", ";
    // }
}

int add(int a, int b) {
    return a + b;
}


py::dict get_dict() {
    py::dict res;
    py::list li;
    li.append(1);
    li.append(2);
    li.append(3);
    res["name"] = "fuck";
    res["age"] = 23;
    res[py::int_(1)] = li;
    // res["1"] = li;

    return res;
}


PYBIND11_MODULE(main, m) {
    m.doc() = "some description of this module";

    m.def("print_list", &print_list, "print some numbers");
    m.def("add", &add, "print some numbers");
    m.def("getDict", &get_dict, "print some numbers");
}

