#include "foo.h"

double foo(const std::shared_ptr<dolfinx::fem::Function<double>> field)
{
   auto r = field->x()->array();
   auto size_local=field->function_space()->dofmap()->index_map->size_local();

   return std::accumulate(r.begin(), r.begin()+size_local, Z30.);
}
