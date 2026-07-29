from __future__ import annotations
import numpy as np
from dolfinx.fem.function import Function
def setf(field:Function):
    field.x.array[:]=np.arange(field.x.array.size)
