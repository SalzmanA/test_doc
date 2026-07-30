from __future__ import annotations
import numpy as np
from dolfinx.fem.function import Function
def setf(field:Function):
    field.x.array[0:field.function_space.dofmap.index_map.size_local]= np.arange(*field.function_space.dofmap.index_map.local_range)
    field.x.scatter_forward()
