using Documenter
import GraphIdx

DocMeta.setdocmeta!(GraphIdx, :DocTestSetup, :(import GraphIdx);
                    recursive=false, warn=true)
DocMeta.setdocmeta!(GraphIdx.Tree, :DocTestSetup, :(import GraphIdx.Tree);
                    recursive=false, warn=true)
doctest(GraphIdx; manual=false)
