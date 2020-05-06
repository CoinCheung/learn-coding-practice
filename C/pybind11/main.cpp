#include"pybind11/pybind11.h"
#include"pybind11/numpy.h"
#include<iostream>
#include<string>
#include <numeric>
#include<vector>
#include"fun.h"
#include"play.h"

namespace py = pybind11;

using std::vector;
using std::cout;
using std::endl;

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

//
// py::array_t<double> max(py::array_t<double, py::array::c_style> arr) {
//     using namespace std;
//     auto r = arr.unchecked<2>();
//     size_t h = r.shape(0);
//     size_t w = r.shape(1);
//
//     auto res = py::array_t<double>({h, 1});
//     double max;
//     for (size_t i{0}; i < h; ++i) {
//         max = r(h, 0);
//         for (size_t j{0}; j < w; ++j) {
//             if (max < r(i, j)) max = r(i, j);
//         }
//         res(i, 0) = max;  // problem seems to be here
//     }
//     return res;
// }

py::array_t<double> get_array(py::array a) {
    // vector<int> size{4, 5};
    // py::array_t<double> res(size);

    // vector<double> buf(10);
    // std::iota(buf.begin(), buf.end(), 1);
    // py::array res = py::array({3, 4}, buf.data());
    // buf[0] = 4444;

    py::buffer_info abuf = a.request();
    double* ptr = (double*)abuf.ptr;
    ptr[0] = 333;

    vector<double>*  buf = new vector<double>(12);
    std::iota(buf->begin(), buf->end(), 1);
    py::capsule cap = py::capsule(buf, [](void *p) {delete reinterpret_cast<vector<double>*>(p);});
    py::array res = py::array({3, 4}, buf->data(), cap);
    buf->data()[0] = 4444;

    return res;
}


PYBIND11_MODULE(main, m) {
    m.doc() = "some description of this module";

    m.def("print_list", &print_list, "print some numbers");
    // m.def("add", &add, "print some numbers");
    // m.def("getDict", &get_dict, "print some numbers");
    // m.def("print", &print, "print some numbers");
    // m.def("print_fuck", &print_fuck, "print some numbers");
    // m.def("get_array", &get_array, "get an array");
}

