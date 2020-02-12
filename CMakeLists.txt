cmake_minimum_required(VERSION 3.11)
project(graphidx)

set(_MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(_MASTER_PROJECT ON)
endif()

option(BUILD_PYEXT "Build python extension module"     ON)
option(BUILD_TEST  "Compile unit tests"                ${_MASTER_PROJECT})
option(ASAN        "Use Address SANitizer"             OFF)
set(PYBIND_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/deps/pybind11"
    CACHE STRING "Which pybind to be used")
set(DOCTEST_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/deps/doctest"
    CACHE STRING "Which doctest to be used")

set(CMAKE_CXX_STANDARD 14)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_definitions(-pedantic -ansi -Wall)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mlzcnt")
    if (ASAN)
        message("-- Enable Address Sanitizer")
        set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")
    endif()
endif()


add_library(graphidx INTERFACE)
target_include_directories(graphidx INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/cxx/include)


if (BUILD_TEST)
    message("-- Enable unit tests")
    if (NOT EXISTS "${DOCTEST_DIR}/CMakeLists.txt")
        execute_process(
            COMMAND git submodule update --init ${DOCTEST_DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()
    add_subdirectory(${DOCTEST_DIR})
    add_executable(doctests
        cxx/test/doctests.cpp
        cxx/test/test_perm.cpp
        cxx/test/test_biadjacent.cpp
        cxx/test/test_bitstring.cpp
        cxx/test/test_children.cpp
        cxx/test/test_clz.cpp
        cxx/test/test_csc.cpp
        cxx/test/test_deque.cpp
        cxx/test/test_grid.cpp
        cxx/test/test_hex.cpp
        cxx/test/test_inorder.cpp
        cxx/test/test_kruskal_mst.cpp
        cxx/test/test_lina.cpp
        cxx/test/test_neg.cpp
        cxx/test/test_partition.cpp
        cxx/test/test_postorder.cpp
        cxx/test/test_bfs.cpp
        cxx/test/test_prufer.cpp
        cxx/test/test_queue.cpp
        cxx/test/test_shift.cpp
        cxx/test/test_stack.cpp
        cxx/test/test_timer.cpp
        cxx/test/test_unionfind.cpp
        cxx/test/test_connected.cpp
        cxx/test/test_van_emde_boas.cpp
        cxx/test/test_vecalloc.cpp
        cxx/test/test_viostream.cpp
        cxx/test/test_weights.cpp
    )
    target_link_libraries(doctests PRIVATE doctest::doctest)
    target_compile_definitions(doctests PUBLIC _STACK_DEBUG=1)
endif()


if (BUILD_PYEXT)
    message("-- Enable python extension")
    if (NOT EXISTS "${PYBIND_DIR}/CMakeLists.txt")
        execute_process(
            COMMAND git submodule update --init ${PYBIND_DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()
    add_subdirectory(${PYBIND_DIR})
    pybind11_add_module(_graphidx
        python/_graphidx.cpp
        python/order.cpp
        python/idx.cpp
        python/spanning.cpp
        python/timer.cpp
    )
    if (_MASTER_PROJECT)
        set(_P "")
    else()
        set(_P "graphidx_")
    endif()
    set(PYDIR ${CMAKE_CURRENT_SOURCE_DIR}/python)
    add_custom_target(${_P}pysetup DEPENDS _graphidx
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE_NAME:_graphidx> ${PYDIR}/graphidx)
    add_custom_target(${_P}pytest DEPENDS pysetup
        COMMAND py.test ${PYDIR}/test VERBATIM)
    export(TARGETS _graphidx NAMESPACE graphidx:: FILE graphidxConfig.cmake)
endif()


# Local Variables:
# cmake-tab-width: 4
# End:
