from io import StringIO
from graphidx.graphviz import print_tree


mini_dot =  """digraph tree {
   rankdir = BT
   1 -> 0
   2 -> 1
   3 -> 0
   4 -> 1
   5 -> 2
}
"""

def test_import():
    from graphidx.graphviz import print_dot
    assert print_dot


def test_print_tree():
    parent = [0, 0, 1, 0, 1, 2]
    buf = StringIO()
    print_tree(parent, out=buf)
    assert buf.getvalue() == mini_dot
