from bar.util import setf

# to replace by simple version if scikit>1.0
from importlib.metadata import version, PackageNotFoundError

try:
    __version__ = version("bar")
#replacing version with  scikit>1.0
#try:
#    from ._version import __version__
except ImportError:
    __version__ = "0+unknown"

from bar.bar_cpp import foo
__all__ = [
        "foo",
        "setf",
        ]
