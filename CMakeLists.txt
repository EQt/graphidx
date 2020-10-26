cmake_minimum_required(VERSION 3.11)
project(graphidx
    DESCRIPTION   "Simple Algorithms on Indexed Graphs"
    HOMEPAGE_URL  "https://github.com/EQt/graphidx")

set(_MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(_MASTER_PROJECT ON)
endif()

set(PYBIND_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/deps/pybind11"
    CACHE PATH     "Which PyBind11 to be used")
set(DOCTEST_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/deps/doctest"
    CACHE PATH     "Which DOCTEST to be used")
option(BUILD_PYEXT "Build python extension module"     ON)
option(BUILD_TEST  "Compile unit tests"                ${_MASTER_PROJECT})
option(BENCHMARK   "Compile benchmarks"                ${_MASTER_PROJECT})
option(ASAN        "Use Address SANitizer"             OFF)
option(TUNE_NATIVE "Optimize for this CPU"             OFF)
option(WITH_LEMON  "Include algorithms using LEMON"    OFF)

set(CMAKE_CXX_STANDARD 17)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_definitions(-pedantic -ansi -Wall -Wextra -Wsign-conversion)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mlzcnt")
    if (TUNE_NATIVE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native")
    endif()
    if (ASAN)
        message("-- Enable Address Sanitizer")
        set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")
    endif()
endif()


if (WITH_LEMON)
    add_subdirectory(deps/lemon)
endif()

add_library(graphidx INTERFACE)
target_include_directories(graphidx INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/cxx)
target_compile_features(graphidx INTERFACE cxx_std_17)

find_package(Python3 COMPONENTS Interpreter Development)
if (MSVC AND PYTHON3__Development_FOUND)
    find_package(BZip2 HINTS "${PYTHON_INCLUDE_DIRS}/../Library/lib")
    find_package(ZLIB  HINTS "${PYTHON_INCLUDE_DIRS}/../Library/lib")
else()
    find_package(BZip2)
    find_package(ZLIB)
endif()
if (BZIP2_FOUND)
    add_library(bz2io INTERFACE)
    target_include_directories(bz2io INTERFACE ${BZIP2_INCLUDE_DIR})
    target_link_libraries(bz2io INTERFACE ${BZIP2_LIBRARIES})
    target_link_libraries(graphidx INTERFACE bz2io)
endif()

if (ZLIB_FOUND)
    add_library(gzio INTERFACE)
    target_include_directories(gzio INTERFACE ${ZLIB_INCLUDE_DIR})
    target_link_libraries(gzio INTERFACE ${ZLIB_LIBRARIES})
    target_link_libraries(graphidx INTERFACE gzio)
endif()


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
        cxx/test/test_parse.cpp
        cxx/test/test_dimacs10.cpp
        cxx/test/test_snap.cpp
        cxx/test/test_biadjacent.cpp
        cxx/test/test_bitstring.cpp
        cxx/test/test_children.cpp
        cxx/test/test_clz.cpp
        cxx/test/test_csc.cpp
        cxx/test/test_deque.cpp
        cxx/test/test_grid.cpp
        cxx/test/test_grididx.cpp
        cxx/test/test_gridincidence.cpp
        cxx/test/test_hex.cpp
        cxx/test/test_inorder.cpp
        cxx/test/test_kruskal_mst.cpp
        cxx/test/test_lina.cpp
        cxx/test/test_neg.cpp
        cxx/test/test_partition.cpp
        cxx/test/test_postorder.cpp
        cxx/test/test_bfs.cpp
        cxx/test/test_dfs.cpp
        cxx/test/test_prufer.cpp
        cxx/test/test_queue.cpp
        cxx/test/test_shift.cpp
        cxx/test/test_stack.cpp
        cxx/test/test_timer.cpp
        cxx/test/test_unionfind.cpp
        cxx/test/test_connected.cpp
        cxx/test/test_string.cpp
        cxx/test/test_van_emde_boas.cpp
        cxx/test/test_vecalloc.cpp
        cxx/test/test_viostream.cpp
        cxx/test/test_weights.cpp
        cxx/test/test_bz2.cpp
        cxx/test/test_gz.cpp
        cxx/test/test_min_cut.cpp
        cxx/test/test_lemon_fib.cpp
    )
    target_link_libraries(doctests PRIVATE doctest::doctest graphidx)
    target_compile_definitions(doctests PUBLIC _STACK_DEBUG=1)
    if (WITH_LEMON)
        target_link_libraries(doctests PRIVATE lemon)
    endif()
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
        python/io.cpp
    )
    target_include_directories(_graphidx PRIVATE
        "${PYTHON_INCLUDE_DIRS}/../Library/include")
    
    target_link_libraries(_graphidx PRIVATE graphidx)
    if (_MASTER_PROJECT)
        set(_P "")
    else()
        set(_P "graphidx_")
    endif()
    set(PYDIR ${CMAKE_CURRENT_SOURCE_DIR}/python)
    add_custom_target(${_P}pysetup DEPENDS _graphidx
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:_graphidx> ${PYDIR}/graphidx)
    if (NOT ASAN)
        add_custom_target(${_P}pytest DEPENDS pysetup
            COMMAND ${LD_PRELOAD} py.test ${PYDIR}/test
            VERBATIM)
    endif()
    export(TARGETS _graphidx NAMESPACE graphidx:: FILE graphidxConfig.cmake)
endif()

if (BENCHMARK)
    add_subdirectory(cxx/benchmark)
endif()


# Local Variables:
# cmake-tab-width: 4
# End:
