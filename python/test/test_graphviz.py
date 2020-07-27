from io import StringIO


mini_dot =  """digraph tree {
   rankdir = BT
   1 -> 0
   2 -> 1
   3 -> 0
   4 -> 1
   5 -> 2
}
"""

grid2x3_dot = """
digraph {
    rankdir=LR
    edge [dir=none]
    node [width=0.3 height=0.3]

    { rank=same
        0 [pos="0,-0!"]
        1 [pos="0,-1!"]
        2 [pos="0,-2!"]
    }
    { rank=same
        3 [pos="1,-0!"]
        4 [pos="1,-1!"]
        5 [pos="1,-2!"]
    }
    0 -> 3 [style=invis]
}
""".strip()


def test_import():
    from graphidx.graphviz import print_dot
    assert print_dot


def test_print_tree():
    from graphidx.graphviz import print_tree

    parent = [0, 0, 1, 0, 1, 2]
    buf = StringIO()
    print_tree(parent, out=buf)
    assert buf.getvalue() == mini_dot


def test_print_grid():
    from graphidx.graphviz import print_grid
    from graphidx import GridGraph

    g = GridGraph(2, 3)
    
