#include "dolfinx.h"
#include "dolfinx/fem/Function.h"

#pragma once

double foo(const std::shared_ptr<dolfinx::fem::Function<double>> field);

