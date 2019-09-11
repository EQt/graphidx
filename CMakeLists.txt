cmake_minimum_required(VERSION 3.12)
project(graphidx)


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mlzcnt")
endif()


set(TESTS
    test_children.cpp
    test_partition.cpp
    test_biadjacent.cpp
    test_grid.cpp
    test_timer.cpp
    test_stack.cpp
    test_queue.cpp
    test_unionfind.cpp
    test_kruskal_mst.cpp
    test_postorder.cpp
    test_prufer.cpp
    test_hex.cpp
    test_bitstring.cpp
    test_shift.cpp
    test_clz.cpp
    test_vecalloc.cpp
    test_inorder.cpp
    test_van_emde_boas.cpp
    test_csc.cpp
    test_neg.cpp
    test_weights.cpp
    test_deque.cpp
)
list(TRANSFORM TESTS PREPEND "cxx/test/")


add_executable(tests
    cxx/test/tests.cpp
    ${TESTS}
)

add_subdirectory(deps/googletest)
target_include_directories(tests PUBLIC deps/googletest/googletest/include)
target_compile_definitions(tests PUBLIC _STACK_DEBUG=1)
target_link_libraries(tests gtest_main "${CMAKE_THREAD_LIBS_INIT}")
