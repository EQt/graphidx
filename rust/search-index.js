var N=null,E="",T="t",U="u",searchIndex={};
var R=["option","usize","from_parent","graphidx","graphidx::tree","result","try_from","try_into","borrow_mut","borrow","graphidx::weights","type_id","childrenindex","constantweights","arrayweights","formatter","ChildrenIndex","ConstantWeights","ArrayWeights"];

searchIndex["graphidx"]={"doc":"GraphIdx","i":[[0,"tree",R[3],"Functions regarding (rooted) tree graphs.",N,N],[3,R[16],R[4],"Find all children of a node in constant time.",N,N],[3,"Tree",E,"A tree represented by a `parent` array that tells the…",N,N],[5,"find_root",E,"Find the root node of a tree given its `parent` vector.",N,[[],[[R[0],[R[1]]],[R[1]]]]],[11,"from_tree",E,"Build a new `Children Index`.",0,[[[R[1]]],["self"]]],[11,R[2],E,"Construct a new `ChildrenIndex` by first finding the…",0,[[],[R[0]]]],[11,"root_node",E,"The root node of the underlying tree.",0,[[["self"]],[R[1]]]],[11,"len",E,"Number of nodes in the underlying tree.",0,[[["self"]],[R[1]]]],[11,R[2],E,"Compute the `root` node by `find_root`.",1,[[[R[1]],["vec",[R[1]]]],[R[0]]]],[0,"weights",R[3],"Weight parameters associated to a collection, e.g. nodes…",N,N],[3,R[17],R[10],"Same weight for every element.",N,N],[3,R[18],E,"Weights stored in an array.",N,N],[8,"Weights",E,E,N,N],[10,"len",E,E,2,[[["self"]],[R[1]]]],[11,"new",E,E,3,[[[T]],["self"]]],[11,"from",R[4],E,0,[[[T]],[T]]],[11,"into",E,E,0,[[],[U]]],[11,R[6],E,E,0,[[[U]],[R[5]]]],[11,R[7],E,E,0,[[],[R[5]]]],[11,R[8],E,E,0,[[["self"]],[T]]],[11,R[9],E,E,0,[[["self"]],[T]]],[11,R[11],E,E,0,[[["self"]],["typeid"]]],[11,"from",E,E,1,[[[T]],[T]]],[11,"into",E,E,1,[[],[U]]],[11,R[6],E,E,1,[[[U]],[R[5]]]],[11,R[7],E,E,1,[[],[R[5]]]],[11,R[8],E,E,1,[[["self"]],[T]]],[11,R[9],E,E,1,[[["self"]],[T]]],[11,R[11],E,E,1,[[["self"]],["typeid"]]],[11,"from",R[10],E,3,[[[T]],[T]]],[11,"into",E,E,3,[[],[U]]],[11,R[6],E,E,3,[[[U]],[R[5]]]],[11,R[7],E,E,3,[[],[R[5]]]],[11,R[8],E,E,3,[[["self"]],[T]]],[11,R[9],E,E,3,[[["self"]],[T]]],[11,R[11],E,E,3,[[["self"]],["typeid"]]],[11,"from",E,E,4,[[[T]],[T]]],[11,"into",E,E,4,[[],[U]]],[11,R[6],E,E,4,[[[U]],[R[5]]]],[11,R[7],E,E,4,[[],[R[5]]]],[11,R[8],E,E,4,[[["self"]],[T]]],[11,R[9],E,E,4,[[["self"]],[T]]],[11,R[11],E,E,4,[[["self"]],["typeid"]]],[11,"len",E,E,3,[[["self"]],[R[1]]]],[11,"len",E,E,4,[[["self"]],[R[1]]]],[11,"eq",R[4],E,0,[[["self"],[R[12]]],["bool"]]],[11,"ne",E,E,0,[[["self"],[R[12]]],["bool"]]],[11,"eq",R[10],E,3,[[["self"],[R[13]]],["bool"]]],[11,"ne",E,E,3,[[["self"],[R[13]]],["bool"]]],[11,"eq",E,E,4,[[["self"],[R[14]]],["bool"]]],[11,"ne",E,E,4,[[["self"],[R[14]]],["bool"]]],[11,"fmt",R[4],E,0,[[["self"],[R[15]]],[R[5]]]],[11,"fmt",R[10],E,3,[[["self"],[R[15]]],[R[5]]]],[11,"fmt",E,E,4,[[["self"],[R[15]]],[R[5]]]],[11,"index",R[4],E,0,[[["self"],[R[1]]]]],[11,"index",R[10],E,3,[[["self"],[R[1]]]]],[11,"index",E,E,4,[[["self"],[R[1]]]]]],"p":[[3,R[16]],[3,"Tree"],[8,"Weights"],[3,R[17]],[3,R[18]]]};
initSearch(searchIndex);addSearchOptions(searchIndex);