#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

using namespace std;

vector<int> get_ball() {
    return vector<int> {288, 366, 5};
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("get_ball", &get_ball, "getter");
}