#include "foo.h"

double foo(const std::shared_ptr<dolfinx::fem::Function<double>> field)
{
   auto r = field->x()->array();

   return std::accumulate(r.begin(), r.end(), 0.);
}
