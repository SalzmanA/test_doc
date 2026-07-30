#include <nanobind/nanobind.h>
#include <nanobind/stl/shared_ptr.h>
#include "dolfinx/fem/Function.h"
#include "bar/foo.h"
namespace nb = nanobind;

NB_MODULE(bar_cpp, m)
{
   m.attr("__version__") = BAR_VERSION;
   m.def("foo", [](std::shared_ptr<dolfinx::fem::Function<double>> field) -> double {
      return foo(field);
   });
}


