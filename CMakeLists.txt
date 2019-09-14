cmake_minimum_required(VERSION 3.11)
project(graphidx)

option(BUILD_PYEXT "Build python extension module"     ON)
option(PYBIND_DIR  "Directory where pybind is located"
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/pybind11")


set(CMAKE_CXX_STANDARD 14)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mlzcnt")
endif()

if(CMAKE_PROJECT_NAME STREQUAL "graphidx")
    add_executable(tests
        cxx/test/tests.cpp
        cxx/test/test_clz.cpp
        cxx/test/test_children.cpp
        cxx/test/test_partition.cpp
        cxx/test/test_biadjacent.cpp
        cxx/test/test_grid.cpp
        cxx/test/test_timer.cpp
        cxx/test/test_stack.cpp
        cxx/test/test_queue.cpp
        cxx/test/test_unionfind.cpp
        cxx/test/test_kruskal_mst.cpp
        cxx/test/test_postorder.cpp
        cxx/test/test_prufer.cpp
        cxx/test/test_hex.cpp
        cxx/test/test_bitstring.cpp
        cxx/test/test_shift.cpp
        cxx/test/test_vecalloc.cpp
        cxx/test/test_inorder.cpp
        cxx/test/test_van_emde_boas.cpp
        cxx/test/test_csc.cpp
        cxx/test/test_neg.cpp
        cxx/test/test_weights.cpp
        cxx/test/test_deque.cpp
    )

    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/googletest/CMakeLists.txt")
        message("git submodule update")
        execute_process(COMMAND git submodule update --init deps/googletest
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll")
    set(GTEST_LANG_CXX11 ON CACHE BOOL "turn on c++11 for gtest")
    add_subdirectory(deps/googletest)
    target_include_directories(tests PUBLIC deps/googletest/googletest/include)
    target_compile_definitions(tests PUBLIC _STACK_DEBUG=1)
    target_link_libraries(tests gtest_main "${CMAKE_THREAD_LIBS_INIT}")
endif()

# Local Variables:
# cmake-tab-width: 4
# End:
