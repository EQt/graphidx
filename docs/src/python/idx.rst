Graph Indexes
=============

.. currentmodule:: graphidx.idx

The unique feature of this graph framework is to compute indices to be able to access certain elements in constant time.
The index computation is always based on counting sort to group certain elements together by an index.


Neighbor Index
--------------

.. autoclass:: BiAdjacent



Partition Index
---------------

.. autofunction:: cluster

.. autoclass:: PartitionIndex


Children Index
--------------

.. autoclass:: ChildrenIndex
               
