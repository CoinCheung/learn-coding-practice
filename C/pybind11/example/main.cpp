#include<pybind11/pybind11.h>
#include"play.h"


PYBIND11_MODULE(main, m) {
    m.doc() = "";

    m.def("print", &print, "");
}

