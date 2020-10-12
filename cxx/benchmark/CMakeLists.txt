message("-- Build benchmark programs")

add_executable(spantree spantree.cxx)
target_link_libraries(spantree PRIVATE graphidx)
