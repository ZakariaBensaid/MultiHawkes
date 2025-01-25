#include "hawkes.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;
namespace py = pybind11;

PYBIND11_MODULE(hawkes, m) {
    m.doc() = "Hawkes process simulation module";

    m.def("simulate_hawkes", &SimulateHawkes, "Function to simulate Hawkes processes",
        py::arg("nbSimulations"), py::arg("nbThreads"), py::arg("mu"),
        py::arg("alpha"), py::arg("beta"), py::arg("T"));
}