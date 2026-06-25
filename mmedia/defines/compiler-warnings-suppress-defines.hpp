#pragma once
/**
\file       compiler-warnings-suppress-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       04.04.2026
\project    u3_defines
*/

#ifdef U3_COMPILER_MSC
// #pragma warning(disable : 4996)
#elif defined(U3_COMPILER_GNUC)
#elif defined(U3_COMPILER_CLANG)

#  if __clang_major__ >= 21
// boost serilization polymorph virtual destructor vs finall word
#    pragma GCC diagnostic ignored "-Wunnecessary-virtual-specifier"
#  endif

#else
#endif
