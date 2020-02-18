#pragma once
#if defined(__GNUC__) && __GNUC__ >= 6
#  define __dispatch__                                                  \
    __attribute__((target_clones("arch=knl", "arch=broadwell", "arch=haswell", "avx", "sse4.1", "avx2", "default")))
#else
#  define __dispatch__
#endif
