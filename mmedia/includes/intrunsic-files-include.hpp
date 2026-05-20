#pragma once
/**
\file       intrunsic-files-include.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_includes
*/

#if defined(U3_COMPILER_MSC)

/* Microsoft C/C++-compatible compiler */
#  include <intrin.h>
#  include <mmintrin.h>

#elif (defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)) && defined(U3_CPU_X86)

/* GCC-compatible compiler, targeting x86/x86-64 */
#  include <x86intrin.h>
#  include <immintrin.h>
#  include <mmintrin.h>
#  include <cpuid.h>

#elif (defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)) && defined(U3_CPU_ARM)

#  ifndef __ARM_NEON__
#    define __ARM_NEON__
#  endif

#  ifndef __ARM_NEON
#    define __ARM_NEON
#  endif

/* GCC-compatible compiler, targeting ARM with NEON */
#  include <arm_neon.h>

#elif (defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)) && defined(U3_CPU_ARM) && defined(__IWMMXT__)

/* GCC-compatible compiler, targeting ARM with WMMX */
#  include <mmintrin.h>

#elif (defined(U3_COMPILER_GNUC) || defined(__xlC__) || defined(U3_COMPILER_CLANG)) && defined(U3_CPU_POWERPC) && (defined(__VEC__) || defined(__ALTIVEC__))

/* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
#  include <altivec.h>

#elif (defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)) && defined(U3_CPU_POWERPC) && defined(__SPE__)

/* GCC-compatible compiler, targeting PowerPC with SPE */
#  include <spe.h>

#endif
