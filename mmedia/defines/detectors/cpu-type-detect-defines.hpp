#pragma once
/**
\file       cpu-type-detect-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
\brief      Определения типа процессора, под который компилируется система
*/

#if defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(_M_IX86) || defined(_X86_) || defined(__I86__)
#  ifndef U3_CPU_X86_32
#    define U3_CPU_X86_32
#  endif
#endif


#if defined(_M_X64) || defined(__x86_64__)
#  ifndef U3_CPU_X86_64
#    define U3_CPU_X86_64
#  endif
#endif


#if defined(U3_CPU_X86_32) || defined(U3_CPU_X86_64)
#  ifndef U3_CPU_X86
#    define U3_CPU_X86
#  endif
#endif


#if !defined(U3_CPU_X86)

#  if defined(__ARM_ARCH_5__) || defined(__ARM_ARCH_5E__) || defined(__ARM_ARCH_5T__) || defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__)
#    ifndef U3_CPU_ARM_5
#      define U3_CPU_ARM_5
#    endif
#  endif

#  if defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__)
#    ifndef U3_CPU_ARM_6
#      define U3_CPU_ARM_6
#    endif
#  endif

#  if defined(__arm__) || defined(__thumb__) || defined(_M_ARM) || defined(M_ARMT) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__)
#    ifndef U3_CPU_ARM_7
#      define U3_CPU_ARM_7
#    endif
#  endif

#  if !defined(U3_CPU_ARM_7)
#    if defined(__ARM_ARCH_8__) || defined(__ARM_ARCH_8A__) || defined(__ARM_ARCH_8R__) || defined(__ARM_ARCH_8M__) || defined(__aarch64__)
#      ifndef U3_CPU_ARM_8
#        define U3_CPU_ARM_8
#      endif
#    endif
#  endif

#endif


#if defined(U3_CPU_ARM_5) || defined(U3_CPU_ARM_6) || defined(U3_CPU_ARM_7) || defined(U3_CPU_ARM_8)
#  if !defined(U3_CPU_ARM)
#    define U3_CPU_ARM
#  endif
#endif
