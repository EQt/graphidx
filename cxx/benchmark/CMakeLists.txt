message("-- Build benchmark programs")

add_executable(spantree spantree.cxx)
target_link_libraries(spantree PRIVATE graphidx)
if (WITH_LEMON)
    target_link_libraries(spantree PRIVATE lemon)
endif()

add_executable(grididx grididx.cxx)
target_link_libraries(grididx PRIVATE graphidx)
