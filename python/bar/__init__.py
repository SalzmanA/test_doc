from bar.util import setf
try:
    from ._version import __version__
except ImportError:
    __version__ = "0+unknown"

from bar.bar_cpp import foo
__all__ = [
        "foo",
        "setf",
        ]
