message("-- Build benchmark programs")

add_executable(spantree spantree.cxx)
target_link_libraries(spantree PRIVATE graphidx)

add_executable(grididx grididx.cxx)
target_link_libraries(grididx PRIVATE graphidx)
