#pragma once
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#ifndef __has_feature
#  define __has_feature(x) false
#endif


/** information about compilation */
constexpr const char*
compiler_info()
{
    return "Compiled with "
#ifdef __clang__
    "Clang++ " __clang_version__
#elif defined __GNUC__
    "GCC (g++) " __VERSION__
#elif defined _MSC_VER
    "MSVC " STR(_MSC_VER)
#endif
     " on "  __DATE__  " " __TIME__
         ;
}


constexpr bool
asan_enabled()
{
#if __has_feature(address_sanitizer) || (defined(__SANITIZE_ADDRESS__) && __SANITIZE_ADDRESS__)
        return true;
#else
        return false;
#endif
}
