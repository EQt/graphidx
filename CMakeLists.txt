cmake_minimum_required(VERSION 3.11)
project(graphidx)

option(BUILD_PYEXT "Build python extension module"     ON)
set(PYBIND_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/pybind11" CACHE STRING
    "Which pybind to be used")

set(CMAKE_CXX_STANDARD 14)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mlzcnt")
endif()

if(CMAKE_PROJECT_NAME STREQUAL "graphidx")
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/doctest/CMakeLists.txt")
        message("git submodule update")
        execute_process(COMMAND git submodule update --init deps/doctest
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
    add_subdirectory(deps/doctest)
    add_executable(doctests
        cxx/test/doctests.cpp
        cxx/test/test_neg.cpp
        cxx/test/test_bitstring.cpp
        cxx/test/test_csc.cpp
        cxx/test/test_children.cpp
        cxx/test/test_clz.cpp
        cxx/test/test_biadjacent.cpp
        cxx/test/test_partition.cpp
        cxx/test/test_grid.cpp
        cxx/test/test_timer.cpp
        cxx/test/test_stack.cpp
        cxx/test/test_inorder.cpp
        cxx/test/test_queue.cpp
        cxx/test/test_van_emde_boas.cpp
        cxx/test/test_shift.cpp
        cxx/test/test_vecalloc.cpp
        cxx/test/test_hex.cpp
        cxx/test/test_deque.cpp
        cxx/test/test_unionfind.cpp
        cxx/test/test_weights.cpp
        cxx/test/test_postorder.cpp
        cxx/test/test_kruskal_mst.cpp
        cxx/test/test_prufer.cpp
    )
    target_link_libraries(doctests PRIVATE doctest::doctest)
    target_compile_definitions(doctests PUBLIC _STACK_DEBUG=1)
    # target_compile_features(doctests PRIVATE cxx_std_14)
endif()


if (BUILD_PYEXT)
    # download as submodule?
    if (NOT EXISTS "${PYBIND_DIR}/CMakeLists.txt")
        execute_process(COMMAND git submodule update --init ${PYBIND_DIR})
    endif()
    add_subdirectory(${PYBIND_DIR})
    pybind11_add_module(_graphidx
        python/_graphidx.cpp
        python/order.cpp
        python/idx.cpp
        python/spanning.cpp
    )
    add_custom_target(pysetup  DEPENDS _graphidx
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE_NAME:_graphidx> ${CMAKE_SOURCE_DIR}/python/graphidx)
    add_custom_target(pytest DEPENDS pysetup
        COMMAND py.test ${CMAKE_SOURCE_DIR}/python/test VERBATIM)

endif()


# Local Variables:
# cmake-tab-width: 4
# End:
